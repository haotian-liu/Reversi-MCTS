//
// Created by Haotian on 2018/3/27.
//

#include "Board.h"

bool Board::has_finished() const {
    auto finished = (p1 == 0 || p2 == 0 || (p1 | p2) == 0xffffffffffffffff);
    if (finished) { return true; }
    // both cannot continue, game ends
    return get_available_actions(1).empty() && get_available_actions(2).empty();
}

uint64_t Board::get(int player) const {
    if (player == 1) return p1;
    if (player == 2) return p2;
    fprintf(stderr, "Board::get_coord player is invalid.");
    return 0;
}
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif
void Board::putWith(const Action &action) {
#ifdef DEBUG
    {
        uint64_t mask = HIGHESTBIT;
        for (int i=0; i<64; i++) {
            if (i && i % 8 == 0) std::cout << std::endl;
            char c;
            if (p1 & mask) c = '1';
            else if (p2 & mask) c = '2';
            else c = ' ';
            std::cout << c << (action.get_coord() == i ? (action.get_player() == 1 ? 'x' : 'o') : ' ') << " ";
            mask >>= 1;
        }
        std::cout << std::endl << "------------------------" << std::endl;
    }
#endif
    if (action.is_dummy()) {
        switchPlayer();
        return;
    }
    uint64_t mask = HIGHESTBIT >> action.get_coord();
    // invalid position if already put.
    if (p1 & mask || p2 & mask) {
        fprintf(stderr, "Board::putWith: putting chess on invalid pos.");
        exit(-1);
    }
    // update chessboard
    if (action.get_player() == 1) { p1 |= mask; }
    else { p2 |= mask; }
    // update board with color switches for on-board chess.
    updateAfterPut(action);
    switchPlayer();
}

void Board::updateAfterPut(const Action &action) {
    static std::vector<int> SHIFT = {-9, -8, -7, -1, 1, 7, 8, 9};

    auto act_p1 = action.get_player() & 1 ? p1 : p2; // action player
    auto act_p2 = action.get_player() & 2 ? p1 : p2; // action rival
    uint64_t new_p1 = act_p1, new_p2 = act_p2;

    // test shifts on different directions
    for (auto shift : SHIFT) {
        auto act = action.get_coord() + shift;
        auto act_mask = action.get_coord() >> 3;
        bool flag = false;
        int shifts = 0;
        while (act >= 0 && act < 64
               && ((shift != 1 && shift != -1) || (act >> 3) == act_mask)
               && (shift != -7 || act % 8 != 0)
               && (shift != -9 || act % 8 != 7)
               && (shift !=  7 || act % 8 != 7)
               && (shift !=  9 || act % 8 != 0)) {
            // if available, continue, try to record the farthest way
            auto mask = HIGHESTBIT >> act;
            if (act_p2 & mask) {
                shifts++;
                flag = true;
            } else {
                break;
            }
            act += shift;
        }
        if (flag
            && act >= 0 && act < 64
            && ((shift != 1 && shift != -1) || (act >> 3) == act_mask)
            && (shift != -7 || act % 8 != 0)
            && (shift != -9 || act % 8 != 7)
            && (shift !=  7 || act % 8 != 7)
            && (shift !=  9 || act % 8 != 0)
            && (act_p1 & (HIGHESTBIT >> act))) {
            act = action.get_coord() + shift;
            while (shifts--) {
                // continue update until reaches the end
                auto mask = HIGHESTBIT >> act;

                new_p1 |= mask;
                new_p2 &= ~mask;

                act += shift;
            }
        }
    }
    // update to current players
    p1 = action.get_player() & 1 ? new_p1 : new_p2;
    p2 = action.get_player() & 2 ? new_p1 : new_p2;
#ifdef DEBUG
    {
        uint64_t mask = HIGHESTBIT;
        for (int i=0; i<64; i++) {
            if (i && i % 8 == 0) std::cout << std::endl;
            char c;
            if (p1 & mask) c = '1';
            else if (p2 & mask) c = '2';
            else c = ' ';
            std::cout << c << (action.get_coord() == i ? (action.get_player() == 1 ? 'x' : 'o') : ' ') << " ";
            mask >>= 1;
        }
        std::cout << std::endl << "------------------------" << std::endl;
    }
#endif
}

std::vector<Action> Board::get_available_actions(int player) const {
    std::vector<Action> actions;
    int actionPlayer = player == -1 ? currentPlayer : player;
    for (int i=0; i<64; i++) {
        Action action(i, actionPlayer);
        if (is_available(action)) {
            actions.push_back(action);
        }
    }
    return actions;
}

bool Board::operator==(const Board &board) const {
    return board.get(1) == p1 && board.get(2) == p2 && currentPlayer == board.get_player();
}

bool Board::is_available(const Action &action) const {
    static std::vector<int> SHIFT = {-9, -8, -7, -1, 1, 7, 8, 9};
    auto action_mask = HIGHESTBIT >> action.get_coord();
    if ((p1 & action_mask) || (p2 & action_mask)) {
#ifdef DEBUG
        fprintf(stderr, "Board::is_available invalid action, already put.\n");
#endif
        return false;
    } // if already

    auto act_p1 = action.get_player() & 1 ? p1 : p2; // action player
    auto act_p2 = action.get_player() & 2 ? p1 : p2; // action rival

    bool FLAG = false;

    for (auto shift : SHIFT) {
        auto act = action.get_coord() + shift;
        auto act_mask = action.get_coord() >> 3;
        bool flag = false;
        // same logic.
        while (act >= 0 && act < 64
               && ((shift != 1 && shift != -1) || (act >> 3) == act_mask)
               && (shift != -7 || act % 8 != 0)
               && (shift != -9 || act % 8 != 7)
               && (shift !=  7 || act % 8 != 7)
               && (shift !=  9 || act % 8 != 0)) {
            auto mask = HIGHESTBIT >> act;
            if (act_p2 & mask) {
                flag = true;
            } else {
                break;
            }
            act += shift;
        }
        if (flag && act >= 0 && act < 64 && (((shift != 1 && shift != -1) || (act >> 3) == act_mask)
                                             && (shift != -7 || act % 8 != 0)
                                             && (shift != -9 || act % 8 != 7)
                                             && (shift !=  7 || act % 8 != 7)
                                             && (shift !=  9 || act % 8 != 0)) && (act_p1 & (HIGHESTBIT >> act))) {
            FLAG = true;
            break;
        }
    }
    return FLAG;
}

Action Board::diff(const Board &other) const {
    uint64_t action_mask = (p1 | p2) ^ (other.get(1) | other.get(2));
    int action = 63 - bit2int(action_mask);
    if (action_mask & (p1 | other.get(1))) { return Action(action, 1); }
    else { return Action(action, 2); }
}

int Board::bit2int(uint64_t n) const {
    int k = 0;
    while (n && !(n & 1)) {
        n >>= 1;
        k++;
    }
    return k;
}

//#define DEBUG_PLAYOUT
#ifdef DEBUG_PLAYOUT
#include <iostream>
#endif
double Board::playout(int player) const {
    auto act_p1 = player & 1 ? p1 : p2; // action player
    auto act_p2 = player & 2 ? p1 : p2; // action rival
    if (player != 1 && player != 2) {
        fprintf(stderr, "Board::playout fails: player not specified.");
        exit(-1);
    }

#ifdef DEBUG_PLAYOUT
    std::cout << "Playout: " << bitcount(act_p1) - bitcount(act_p2) << std::endl;
#endif

    int v1 = bitcount(act_p1), v2 = bitcount(act_p2);
    return v1 > v2 ? 1.0 : (v1 == v2 ? 0.5 : 0.0);
}

int Board::bitcount(uint64_t n) const {
    int count = 0;
    while (n > 0) {
        count++;
        n &= n - 1;
    }
    return count;
}

//
// Created by Haotian on 2018/3/27.
//

#include "Board.h"

bool Board::has_finished() const {
    auto finished = (p1 == 0 || p2 == 0 || p1 | p2 == 0xffffffff);
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

std::vector<Action> Board::get_available_actions(int player=-1) const {
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
    return board.get(1) == p1 && board.get(2) == p2;
}

bool Board::is_available(const Action &action) const {
    static std::vector<int> SHIFT = {-9, -8, -7, -1, 1, 7, 8, 9};
    auto action_mask = 1 << action.get_coord();
    if ((p1 & action_mask) || (p2 & action_mask)) { return false; } // if already

    auto act_p1 = action.get_player() & 1 ? p1 : p2; // action player
    auto act_p2 = action.get_player() & 2 ? p1 : p2; // action rival

    bool FLAG = false;

    for (auto shift : SHIFT) {
        auto act = action.get_coord() + shift;
        bool flag = false;
        while (act >= 0 && act < 64) {
            auto mask = 1 << act;
            if (act_p2 & mask) {
                flag = true;
            }
            if (act_p1 & mask) {
                break;
            }
            act += shift;
        }
        if (flag && act >= 0 && act < 64 && (act_p1 & (1 << act))) {
            FLAG = true;
            break;
        }
    }
    return FLAG;
}

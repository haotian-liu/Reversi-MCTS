//
// Created by Haotian on 2018/3/27.
//

#include "Board.h"

bool Board::has_finished() const {
    return p1 == 0 || p2 == 0 || p1 | p2 == 0xffffffff ||
            (false); // both cannot continue
}

uint64_t Board::get(int player) const {
    if (player == 1) return p1;
    if (player == 2) return p2;
    fprintf(stderr, "Board::get player is invalid.");
    return 0;
}

std::vector<Action> Board::get_available_actions() const {
    return std::vector<Action>();
}

bool Board::operator==(const Board &board) const {
    return board.get(1) == p1 && board.get(2) == p2;
}

//
// Created by Haotian on 2018/3/27.
//

#include "Board.h"

bool Board::has_finished() const {
    return false;
}

std::vector<Action> Board::get_available_actions() const {
    return std::vector<Action>();
}

bool Board::operator==(const Board &board) const {
    return false;
}

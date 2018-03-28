//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_STATE_H
#define REVERSI_STATE_H

#include "Board.h"

struct State {
    explicit State(const Board &board) : board(board) {}
    bool operator==(const State &state) const {
        return board == state.board;
    }
    Board board{};
};


#endif //REVERSI_STATE_H

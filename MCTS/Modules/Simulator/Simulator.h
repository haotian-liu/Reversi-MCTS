//
// Created by Haotian on 2018/3/28.
//

#ifndef REVERSI_SIMULATOR_H
#define REVERSI_SIMULATOR_H

#include "../Board.h"

class Simulator {
public:
    explicit Simulator(const Board &board) : board(board) {
        //
    }
    virtual double run() {
        return 0;
    }

protected:
    Board board{};
};


#endif //REVERSI_SIMULATOR_H

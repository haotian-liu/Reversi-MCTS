//
// Created by Haotian on 2018/4/10.
//

#ifndef REVERSI_SIMULGREEDY_H
#define REVERSI_SIMULGREEDY_H

#include "Simulator.h"

class SimulGreedy : Simulator {
public:
    explicit SimulGreedy(const Board &board) : Simulator(board) {
        //
    }

    double run() override;

    static int evalTunned(Board &board);
};


#endif //REVERSI_SIMULGREEDY_H

//
// Created by Haotian on 2018/3/28.
//

#ifndef REVERSI_SIMULRAND_H
#define REVERSI_SIMULRAND_H

#include "Simulator.h"

class SimulRand : Simulator {
public:
    explicit SimulRand(const Board &board) : Simulator(board) {
        //
    }

    double run() override;
private:
};


#endif //REVERSI_SIMULRAND_H

//
// Created by Haotian on 2018/4/9.
//

#ifndef REVERSI_SIMULMINMAX_H
#define REVERSI_SIMULMINMAX_H

#include "Simulator.h"
class SimulMinMax : Simulator {
public:
    explicit SimulMinMax(const Board &board) : Simulator(board) {
        //
    }

    double run() override;

private:
    int evalClassical(const Board &board) const;
    int min_max_search(Board &board, Action &best_action, int deep, int max_deep);
};


#endif //REVERSI_SIMULMINMAX_H

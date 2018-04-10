//
// Created by Haotian on 2018/4/10.
//

#include "SimulGreedy.h"

double SimulGreedy::run() {
    while (!board.has_finished()) {
        auto actions = board.get_available_actions();
        if (actions.empty()) {
            board.switchPlayer();
            continue;
        }
        auto bestAction = &actions[0];
        double bestValue = -9999999999;
        for (auto &action : actions) {
            auto b = board;
            b.putWith(action);
            auto v = evalTunned(b);
            if (v > bestValue) {
                bestAction = &action;
                bestValue = v;
            }
        }
        board.putWith(*bestAction);
    }
    return board.playout(2);
}

double SimulGreedy::evalTunned(Board &board) {
    static const double weight_map[8][8] ={
            {16.16, -3.03, 0.99, 0.43, 0.43, 0.99, -3.03, 16.16},
            {-4.12, -1.81, -0.08, -0.27, -0.27, -0.08, -1.81, -4.12},
            {1.33, -0.04, 0.51, 0.07, 0.07, 0.51, -0.04, 1.33},
            {0.63, -0.18, -0.04, 0.01, 0.01, -0.04, -0.18, 0.63},
            {0.63, -0.18, -0.04, 0.01, 0.01, -0.04, -0.18, 0.63},
            {1.33, -0.04, 0.51, 0.07, 0.07, 0.51, -0.04, 1.33},
            {-4.12, -1.81, -0.08, -0.27, -0.27, -0.08, -1.81, -4.12},
            {16.16, -3.03, 0.99, 0.43, 0.43, 0.99, -3.03, 16.16}
    };

    board.switchPlayer();

    double score = 0;
    for(int i = 0; i < 8; i ++){
        for(int j = 0 ; j < 8; j++){
            double weight = weight_map[i][j];

            int index = i * 8 + j;
            uint64_t mask = HIGHESTBIT >> index;
            int c = board.get_player(), r = !(c - 1) + 1;
            uint64_t p1 = board.get(r), p2 = board.get(c);
            int ch = p1 & mask ? -1 : (p2 & mask ? 1 : 0);

            score += weight * ch;
        }
    }

    board.switchPlayer();

    return score;
}

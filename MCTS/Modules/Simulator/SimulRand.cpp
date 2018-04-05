//
// Created by Haotian on 2018/3/28.
//

#include "SimulRand.h"
#include <random>

double SimulRand::run() {
    while (!board.has_finished()) {
        auto actions = board.get_available_actions();
        if (actions.empty()) {
            board.switchPlayer();
            continue;
        }
        static std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, actions.size());
        int id = distribution(generator) - 1;
        auto &action = actions[id];
        board.putWith(action);
    }
    return board.playout(2);
}

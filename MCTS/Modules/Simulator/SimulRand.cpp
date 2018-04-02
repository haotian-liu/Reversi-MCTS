//
// Created by Haotian on 2018/3/28.
//

#include "SimulRand.h"
#include <random>

double SimulRand::run() {
    int currentPlayer = board.get_player();
    while (!board.has_finished()) {
        auto actions = board.get_available_actions();
        if (actions.empty()) {
            fprintf(stderr, "SimulRand::run trys to simulate on a dead board.");
            exit(-1);
        }
        static std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, actions.size());
        int id = distribution(generator) - 1;
        auto &action = actions[id];
        board.putWith(action);
    }
    return board.playout(currentPlayer);
}

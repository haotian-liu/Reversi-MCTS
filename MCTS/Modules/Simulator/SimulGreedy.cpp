//
// Created by Haotian on 2018/4/10.
//

#include "SimulGreedy.h"

double SimulGreedy::run() {
    Board restore;
    while (!board.has_finished()) {
        auto actions = board.get_available_actions();
        if (actions.empty()) {
            board.switchPlayer();
            continue;
        }
        auto bestAction = &actions[0];
        int bestValue = -99999999;
        restore = board;
        for (auto &action : actions) {
            board.putWith(action);
            auto v = evalTunned(board);
            if (v > bestValue) {
                bestAction = &action;
                bestValue = v;
            }
            board = restore;
        }
        board.putWith(*bestAction);
    }
    return board.playout(2);
}

int SimulGreedy::evalTunned(Board &board) {
//    static const int weight_map[8][8] ={
//            {1616, -303, 99, 43, 43, 99, -303, 1616},
//            {-412, -181, -8, -27, -27, -8, -181, -412},
//            {133, -4, 51, 7, 7, 51, -4, 133},
//            {63, -18, -4, 1, 1, -4, -18, 63},
//            {63, -18, -4, 1, 1, -4, -18, 63},
//            {133, -4, 51, 7, 7, 51, -4, 133},
//            {-412, -181, -8, -27, -27, -8, -181, -412},
//            {1616, -303, 99, 43, 43, 99, -303, 1616}
//    };

    static const int weights[] = {
            1616, -303, 99, 43, 43, 99, -303, 1616,
            -412, -181, -8, -27, -27, -8, -181, -412,
            133, -4, 51, 7, 7, 51, -4, 133,
            63, -18, -4, 1, 1, -4, -18, 63,
            63, -18, -4, 1, 1, -4, -18, 63,
            133, -4, 51, 7, 7, 51, -4, 133,
            -412, -181, -8, -27, -27, -8, -181, -412,
            1616, -303, 99, 43, 43, 99, -303, 1616
    };

    board.switchPlayer();


    int c = board.get_player(), r = !(c - 1) + 1;
    uint64_t p1 = board.get(r), p2 = board.get(c);
    uint64_t mask = HIGHESTBIT;

    int score = 0;
    for (int weight : weights) {
        int ch = p1 & mask ? -1 : (p2 & mask ? 1 : 0);
        score += weight * ch;

        mask >>= 1;
    }

    board.switchPlayer();

    return score;
}

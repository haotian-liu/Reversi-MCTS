//
// Created by Haotian on 2018/4/9.
//

#include "SimulMinMax.h"


double SimulMinMax::run() {
    while (!board.has_finished()) {
        auto actions = board.get_available_actions();
        if (actions.empty()) {
            board.switchPlayer();
            continue;
        }
        Action bestAction(-1, 1);
        auto b = board;
        min_max_search(b, bestAction, 1, 4);
        board.putWith(bestAction);
    }
    return board.playout(2);
}

int SimulMinMax::evalClassical(const Board &board) const {
    const int CORNER = 100;
    const int DEAD = -25;
    const int PEDGE = 25;
    const int EDGE = 4;
    const int POINT = 1;
    static const int weight_map[8][8] ={
            {CORNER, DEAD, PEDGE, EDGE, EDGE, PEDGE, DEAD, CORNER},
            {DEAD, DEAD, POINT, POINT, POINT, POINT, DEAD, DEAD},
            {PEDGE, POINT, POINT, POINT, POINT, POINT, POINT, PEDGE},
            {EDGE, POINT, POINT, POINT, POINT, POINT, POINT, EDGE},
            {EDGE, POINT, POINT, POINT, POINT, POINT, POINT, EDGE},
            {PEDGE, POINT, POINT, POINT, POINT, POINT, POINT, PEDGE},
            {DEAD,DEAD, POINT, POINT, POINT, POINT, DEAD, DEAD},
            {CORNER, DEAD, PEDGE, EDGE, EDGE, PEDGE, DEAD, CORNER}
    };


    int score = 0;
    for(int i = 0; i < 8; i ++){
        for(int j = 0 ; j < 8; j++){
            int weight = weight_map[i][j];

            int index = i * 8 + j;
            uint64_t mask = HIGHESTBIT >> index;
            int c = board.get_player(), r = !(c - 1) + 1;
            uint64_t p1 = board.get(r), p2 = board.get(c);
            int ch = p1 & mask ? -1 : (p2 & mask ? 1 : 0);

            score += weight * ch;
        }
    }
    return score;
}

int SimulMinMax::min_max_search(Board &board, Action &best_action, int deep, int max_deep) {
    bool is_max = deep % 2 == 1;
    int score;
    auto actions = board.get_available_actions();

    Action new_action(-1, 1);
    if (actions.empty()){
        if(deep == max_deep) {
            best_action = Action(-1, board.get_player());
            return evalClassical(board);
        }
        else {
            best_action = Action(-1, board.get_player());
            board.switchPlayer();
            return min_max_search(board, best_action, deep + 1, max_deep);
        }
    }
    int max_or_min = is_max ? -100000 : 100000;
    Action *max_or_min_ord = &actions[0];
    for (auto action : actions){
        auto b = board;
        b.putWith(action);
        if (deep == max_deep) score = evalClassical(b);
        else score = min_max_search(b, new_action, deep + 1, max_deep);
        if((is_max && score > max_or_min) || (!is_max && score < max_or_min)){
            max_or_min = score;
            max_or_min_ord = &action;
        }
    }
    best_action = *max_or_min_ord;
//    printf("mmsearch[%d], score=%d, (%d, %d)\n", deep, max_or_min,
//           max_or_min_ord / 8, max_or_min_ord % 8);
    return max_or_min;
}


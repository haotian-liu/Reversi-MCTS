//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_ACTION_H
#define REVERSI_ACTION_H


struct Action {
    int coord;

    bool operator==(const Action &action) {
        return coord == action.coord;
    }
};


#endif //REVERSI_ACTION_H

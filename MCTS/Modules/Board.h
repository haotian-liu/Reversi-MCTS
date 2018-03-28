//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

#include "Action.h"

class Board {
public:
    bool has_finished() const;
    bool operator==(const Board &board);
};


#endif //REVERSI_GENERALBOARD_H

//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

#include "Action.h"
#include <vector>

static const uint64_t P1Initial = 0b1000000001000 << 24;
static const uint64_t P2Initial = 0b0100000010000 << 24;

class Board {
public:
    Board() : p1(P1Initial), p2(P2Initial) {}
    Board(uint64_t p1, uint64_t p2) : p1(p1), p2(p2) {}
    bool has_finished() const;
    std::vector<Action> get_available_actions() const;
    bool operator==(const Board &board) const;
    uint64_t get(int player) const;

private:
    uint64_t p1, p2;
};


#endif //REVERSI_GENERALBOARD_H

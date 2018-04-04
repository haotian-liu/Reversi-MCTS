//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

#include "Action.h"
#include <vector>

/*
 *
 * Action order
 *   0,  1,  2,  3,  4,  5,  6,  7
 *   8,  9, 10, 11, 12, 13, 14, 15
 *
 * binary representation:
 * from higher to lower bit === Action 0 ~ 63
 *
 * Black is the first to go === black ~ P1, white ~ P2
 *
 */

static const uint64_t P1Initial = static_cast<uint64_t>(0b0000100000010000) << 24;
static const uint64_t P2Initial = static_cast<uint64_t>(0b0001000000001000) << 24;
static const uint64_t HIGHESTBIT = static_cast<uint64_t>(1) << 63;

class Board {
public:
    Board() : p1(P1Initial), p2(P2Initial) {}
    Board(uint64_t p1, uint64_t p2) : p1(p1), p2(p2) {}
    Board(uint64_t p1, uint64_t p2, int currentPlayer) : p1(p1), p2(p2), currentPlayer(currentPlayer) {}
    Board(const Board &board) : p1(board.get(1)), p2(board.get(2)), currentPlayer(board.get_player()) {}
    bool has_finished() const;
    std::vector<Action> get_available_actions(int player=-1) const;
    bool operator==(const Board &board) const;
    uint64_t get(int player) const;
    void setPlayer(int player) { currentPlayer = player; }
    void switchPlayer() { currentPlayer = !(currentPlayer - 1) + 1; }
    void putWith(const Action &action);
    double playout(int player) const;
    int get_player() const { return currentPlayer; }
    Action diff(const Board &other) const;

private:
    bool is_available(const Action &action) const;
    int bitcount(uint64_t n) const;
    int bit2int(uint64_t n) const;
    void updateAfterPut(const Action &action);
    int currentPlayer = 1;
    uint64_t p1, p2;
};


#endif //REVERSI_GENERALBOARD_H

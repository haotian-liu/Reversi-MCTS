//
// Created by Haotian on 2018/4/1.
//

#ifndef REVERSI_MCTSPLAYER_H
#define REVERSI_MCTSPLAYER_H

#include "MCTS/MCTS.h"

class MCTSPlayer {
public:
    MCTSPlayer() : lastBoard(), state(lastBoard) {
        auto node = TreeNode(state);
        mcts = new MCTS(node);
    }
    int move(const Board &newBoard, int step) {
        int simulCount = (15 * (step * 1.0 / 60) * (step * 1.0 / 60) + 1.0) * MaxMCTSSim;
        printf("Simul count: %d\n", simulCount);

        auto action = newBoard.diff(lastBoard);
        if (newBoard == lastBoard) {
            printf("MCTSPlayer::move other player fails to move, skipping...\n");
            action = Action(-1, 1);
        }
        auto lastNode = TreeNode(State(lastBoard));
        auto node = mcts->find(&lastNode);
        if (node == nullptr) {
            fprintf(stderr, "MCTSPlayer::move fails, nullptr!");
            exit(-1);
        }
        auto children = node->get_children();
        auto actionExpand = children.find(action);
        if (actionExpand == children.end()) {
            node = node->expand(action);
        } else {
            node = actionExpand->second;
        }
        mcts->execute(node, simulCount);

        auto newNode = TreeNode(State(newBoard));
        node = mcts->find(&newNode);
        if (node == nullptr) {
            fprintf(stderr, "MCTSPlayer::move fails, weird board situation!");
            exit(-1);
        }

        auto bestAction = node->best_action();
        if (bestAction == nullptr) {
            printf("MCTSPlayer::move finds no action available, skipping...\n");
            return -1; // skip action
        } else {
            lastBoard = newBoard;
            lastBoard.putWith(*bestAction);
            return bestAction->get_coord();
        }
    }
private:
    Board lastBoard;
    State state;
    MCTS *mcts;
};

#endif //REVERSI_MCTSPLAYER_H

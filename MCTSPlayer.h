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
    int move(const Board &newBoard) {
        if (newBoard == lastBoard) {
            exit(-1);
        }
        auto action = newBoard.diff(lastBoard);
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
        mcts->execute(node);

        auto newNode = TreeNode(State(newBoard));
        node = mcts->find(&newNode);
        if (node == nullptr) {
            fprintf(stderr, "MCTSPlayer::move fails, nullptr after expand!");
            exit(-1);
        }
        fprintf(stderr, "test");
        return 20;
    }
private:
    Board lastBoard;
    State state;
    MCTS *mcts;
};

#endif //REVERSI_MCTSPLAYER_H

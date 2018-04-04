//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_MCTS_H
#define REVERSI_MCTS_H

#include "Modules/TreeNode.h"

const int MaxMCTSSim = 5000;

class MCTS {
public:
    explicit MCTS(TreeNode &root) : root(root) {}
    void execute(TreeNode *target);
    TreeNode *find(TreeNode *target);

private:
    TreeNode root;
};


#endif //REVERSI_MCTS_H

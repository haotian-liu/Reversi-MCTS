//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_MCTS_H
#define REVERSI_MCTS_H

#include "Modules/TreeNode.h"

const int MaxMCTSSim = 50;

class MCTS {
public:
    void execute(TreeNode *target);
private:

    TreeNode *find(TreeNode *target);
    TreeNode root;
    TreeNode *current;
};


#endif //REVERSI_MCTS_H

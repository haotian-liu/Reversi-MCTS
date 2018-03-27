//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_TREENODE_H
#define REVERSI_TREENODE_H

#include <vector>

class TreeNode {
public:
    bool has_finished() const;
    bool is_expanded() const;
    TreeNode *expand();
    TreeNode *select() const;
    int simulate() const;
    void bp();
private:
};


#endif //REVERSI_TREENODE_H

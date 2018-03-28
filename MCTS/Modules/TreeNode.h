//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_TREENODE_H
#define REVERSI_TREENODE_H

#include <vector>
#include <map>
#include "Board.h"
#include "State.h"

class TreeNode {
public:
    explicit TreeNode(const State &state, TreeNode *parent = nullptr) : state(state), parent(parent) {
        //
    }
    bool has_finished() const;
    bool is_expanded() const;
    TreeNode *expand(Action action);
    TreeNode *select() const;
    int simulate() const;
    void bp(double value);
private:
    State state;
    TreeNode *parent;
    std::vector<Action> get_available_actions() const;
    std::map<Action, TreeNode *> children;
    double playout;
    static int total_simul;
    int simuls;

    double ucb() const;
};


#endif //REVERSI_TREENODE_H

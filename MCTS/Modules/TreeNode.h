//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_TREENODE_H
#define REVERSI_TREENODE_H

#include <vector>
#include <unordered_map>
#include "Board.h"
#include "State.h"

static const auto actionHasher = [](const Action &action) {
    return action.get_coord();
};

class TreeNode {
public:
    explicit TreeNode(const State &state, TreeNode *parent = nullptr) : state(state), parent(parent), children(10, actionHasher) {
        //
    }
    bool has_finished() const;
    bool is_expanded() const;
    Action random_expand() const;
    TreeNode *expand(Action action);
    TreeNode *select() const;
    TreeNode *find(TreeNode *target) const;
    double simulate() const;
    void bp(double value);
private:
    State state;
    TreeNode *parent;
    std::vector<Action> get_available_actions() const;

    std::unordered_map<Action, TreeNode *, decltype(actionHasher)> children;
    double playout;
    static int total_simul;
    int simuls;

    double ucb() const;
};


#endif //REVERSI_TREENODE_H

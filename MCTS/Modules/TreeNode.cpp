//
// Created by Haotian on 2018/3/27.
//

#include "TreeNode.h"
#include <cmath>

int TreeNode::total_simul = 0;

bool TreeNode::has_finished() const {
    return state.board.has_finished();
}

bool TreeNode::is_expanded() const {
    return get_available_actions().size() == children.size();
}

TreeNode *TreeNode::expand(Action action) {
    auto actions = get_available_actions();
    if (actions.empty()) {
        return nullptr;
    }
    if (std::find(actions.begin(), actions.end(), action) == actions.end()) {
        fprintf(stderr, "TreeNode::expand action invalid.");
        return nullptr;
    }
    auto state = this->state;
    auto child = new TreeNode(state, this);
}

double TreeNode::ucb() const {
    return playout + sqrt(2.0 * log(TreeNode::total_simul) / simuls);
}

TreeNode *TreeNode::select() const {
    if (children.empty()) {
        return nullptr;
    } else {
        using children_map_type = decltype(children);
        return std::max_element(children.begin(), children.end(),
            [](const children_map_type::value_type &p1, const children_map_type::value_type &p2) {
                return p1.second->ucb() < p2.second->ucb();
            }
        )->second;
    }
}

int TreeNode::simulate() const {
    return 0;
}

void TreeNode::bp(double value) {
    this->playout += value;
    simuls++;
    TreeNode::total_simul++;
    if (parent != nullptr) {
        parent->bp(value);
    }
}

std::vector<Action> TreeNode::get_available_actions() const {
    return std::vector<Action>();
}

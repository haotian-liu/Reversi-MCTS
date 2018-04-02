//
// Created by Haotian on 2018/3/27.
//

#include "TreeNode.h"
#include "Simulator/SimulRand.h"
#include <random>

int TreeNode::total_simul = 0;

bool TreeNode::has_finished() const {
    return state.board.has_finished();
}

bool TreeNode::is_expanded() const {
    return get_available_actions().size() == children.size();
}

Action TreeNode::random_expand() const {
    auto actions = get_available_actions();
    if (actions.empty() || actions.size() == children.size()) {
        fprintf(stderr, "TreeNode::random_expand fails: fully expanded.");
        exit(-1);
    }
    for (const auto &child : children) {
        auto action = std::find(actions.begin(), actions.end(), child.first);
        if (action == actions.end()) {
            fprintf(stderr, "TreeNode::random_expand found invalid operation in children.");
            exit(-1);
        }
        actions.erase(action);
    }
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, actions.size());
    int id = distribution(generator) - 1;
    return actions[id];
}

TreeNode *TreeNode::expand(Action action) {
    auto actions = get_available_actions();
    if (actions.empty()) {
        return nullptr;
    }
    if (std::find(actions.begin(), actions.end(), action) == actions.end()) {
        fprintf(stderr, "TreeNode::expand action invalid.");
        exit(-1);
    }
    auto state = this->state;
    auto child = new TreeNode(state, this);
    child->state.board.putWith(action);
    using children_map_type = decltype(children);
    children.insert(children_map_type::value_type(action, child));
    return child;
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

const Action * TreeNode::best_action() const {
    if (children.empty()) {
        return nullptr;
    } else {
        const Action *bestAction = &children.begin()->first;
        auto bestValue = children.begin()->second->ucb();
        for (const auto &child : children) {
            auto bValue = child.second->ucb();
            if (bValue > bestValue) {
                bestAction = &child.first;
                bestValue = bValue;
            }
        }
        return bestAction;
    }
}

TreeNode *TreeNode::find(TreeNode *target) const {
    if (state == target->state) {
        return const_cast<TreeNode *>(this);
    }
    if (children.empty()) {
        return nullptr;
    }
    for (const auto &child : children) {
        auto result = child.second->find(target);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}

double TreeNode::simulate() const {
    auto sim = SimulRand(state.board);
    return sim.run();
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
    return state.board.get_available_actions(-1);
}

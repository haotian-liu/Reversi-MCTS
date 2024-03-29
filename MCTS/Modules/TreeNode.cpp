//
// Created by Haotian on 2018/3/27.
//

#include "TreeNode.h"
#include "Simulator/SimulGreedy.h"
#include "Simulator/SimulRand.h"
#include <random>
#include <algorithm>

int TreeNode::total_simul = 0;
std::unordered_map<Board, TreeNodeStatistic, decltype(boardStateHasher)> TreeNode::recorder(10, boardStateHasher);

bool TreeNode::has_finished() const {
    return state.board.has_finished();
}

bool TreeNode::is_expanded() const {
    return get_available_actions().size() == children.size() || get_available_actions().empty();
}

Action TreeNode::random_expand() const {
    auto actions = get_available_actions(); // get all actions
    if (actions.empty() || actions.size() == children.size()) {
        fprintf(stderr, "TreeNode::random_expand fails: fully expanded.");
        exit(-1);
    }
    // erase already present actions
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
    // return randomly selected one
    return actions[id];
}

TreeNode *TreeNode::expand(Action action) {
    auto actions = get_available_actions();
    // determine whether valid expansion
    if (!action.is_dummy() && actions.empty()) {
        return nullptr;
    }
    if (!action.is_dummy() && std::find(actions.begin(), actions.end(), action) == actions.end()) {
        fprintf(stderr, "TreeNode::expand action invalid.");
        exit(-1);
    }
    auto state = this->state;
    auto child = new TreeNode(state, this);
    // update current board of the state
    child->state.board.putWith(action);
    using children_map_type = decltype(children);
    // insert to the children list
    children.insert(children_map_type::value_type(action, child));
    return child;
}
//#define DEBUG_UCB
#ifdef DEBUG_UCB
#include <iostream>
#endif
double TreeNode::ucb() const {
    int total_simul = parent == nullptr ? TreeNode::total_simul : parent->simuls;
    return playout / simuls + sqrt(2.0 * log(total_simul) / simuls);
//    auto node = TreeNode::recorder.find(state.board);
//    if (node == TreeNode::recorder.end()) {
//        fprintf(stderr, "TreeNode::ucb attempts to estimate an unvisited node.");
//        exit(-1);
//    } else {
//#ifdef DEBUG_UCB
//        std::cout << node->second.playout / node->second.simuls + sqrt(2.0 * log(TreeNode::total_simul) / node->second.simuls) << std::endl;
//#endif
////        return node->second.playout / node->second.simuls + sqrt(2.0 * log(TreeNode::total_simul) / node->second.simuls);
////        printf("%f, %d, %d\n", playout, simuls, total_simul);
//        return playout / simuls + sqrt(2.0 * log(total_simul) / simuls);
//    }
}

//#define DEBUG_VALUE
#ifdef DEBUG_VALUE
#include <iostream>
#endif
double TreeNode::value() const {
    return ucb();
//    auto node = TreeNode::recorder.find(state.board);
//    if (node == TreeNode::recorder.end()) {
//        fprintf(stderr, "TreeNode::ucb attempts to estimate an unvisited node.");
//        exit(-1);
//    } else {
////        double retValue = node->second.playout / node->second.simuls;
////        double retValue = simuls;
//        double retValue = ucb();
//#ifdef DEBUG_VALUE
//        std::cout << retValue << std::endl;
//#endif
//        return retValue;
//    }
}

TreeNode *TreeNode::select() const {
    if (children.empty()) {
        return nullptr;
    } else {
        using children_map_type = decltype(children);
        // using closure to find the best ucb.
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
        // find the best action iteratively
        const Action *bestAction = &children.begin()->first;
        auto bestValue = children.begin()->second->value();
        for (const auto &child : children) {
            auto bValue = child.second->value();
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
    // using different method to simulate: greedy, minmax, random.
    auto sim = SimulGreedy(state.board);
    return sim.run();
}

void TreeNode::bp(double value) {
    /*this->playout += value;
    simuls++;
    sync_global_recorder(value); // AMAF policy

    if (parent != nullptr) {
        parent->bp(value);
    }*/
    auto node = this;
    while (node != nullptr) {
        node->playout += value;
        node->simuls++;
        node->sync_global_recorder(value); // AMAF policy

        node = node->parent;
    }
}

void TreeNode::sync_global_recorder(double value) {
    auto node = TreeNode::recorder.find(state.board);
    if (node == TreeNode::recorder.end()) {
        TreeNode::recorder.insert({state.board, TreeNodeStatistic(1, value)});
    } else {
        node->second.playout += value;
        node->second.simuls++;
    }
}

std::vector<Action> TreeNode::get_available_actions() const {
    return state.board.get_available_actions(-1);
}

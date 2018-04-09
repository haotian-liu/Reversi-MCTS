//
// Created by Haotian on 2018/3/27.
//

#include "MCTS.h"

void MCTS::execute(TreeNode *target) {
    auto base = find(target);

    for (int i=0; i<MaxMCTSSim; i++) {
        auto node = base;
        if (node == nullptr) {
            fprintf(stderr, "MCTS::execute base node nullptr.");
            break;
        }

        while (!node->has_finished()) {
            if (node->is_expanded() && !node->get_children().empty()) {
                node = node->select();
                if (node == nullptr) {
                    fprintf(stderr, "MCTS::execute expand nullptr.");
                    exit(-1);
                }
            } else {
                auto action = node->is_expanded() && node->get_children().empty() ?
                              Action(-1, node->get_current_player()) : node->random_expand();
                node = node->expand(action);
                if (node == nullptr) {
                    fprintf(stderr, "MCTS::execute expand nullptr.");
                    exit(-1);
                }
                break;
            }
        }

        auto playout = node->simulate();
        TreeNode::total_simul++;
        node->bp(playout);
    }

    base->select()->debug();
}

TreeNode *MCTS::find(TreeNode *target) {
    return root.find(target);
}

//
// Created by Haotian on 2018/3/27.
//

#include "MCTS.h"
#include <omp.h>

void MCTS::execute(TreeNode *target, int simulCount) {
    auto base = find(target);

#pragma omp parallel for
    for (int i=0; i<simulCount; i++) {
        auto node = base;
        if (node == nullptr) {
            fprintf(stderr, "MCTS::execute base node nullptr.");
        }

        bool cont = true;

        while (!node->has_finished() && cont) {
#pragma omp critical
{
            // select best if node has been expanded
            if (node->is_expanded() && !node->get_children().empty()) {
                node = node->select();
                if (node == nullptr) {
                    fprintf(stderr, "MCTS::execute expand nullptr.");
                }
            } else {
                // find an action to expand
                auto action = node->is_expanded() && node->get_children().empty() ?
                              Action(-1, node->get_current_player()) : node->random_expand();
                node = node->expand(action);
                if (node == nullptr) {
                    fprintf(stderr, "MCTS::execute expand nullptr.");
                }
                cont = false;
            }
}
        }

        // simulate
        auto playout = node->simulate();
        TreeNode::total_simul++;
        // back propagation
        node->bp(playout);
    }

    base->select()->debug();
}

TreeNode *MCTS::find(TreeNode *target) {
    return root.find(target);
}

//
// Created by Haotian on 2018/3/27.
//

#include "TreeNode.h"

bool TreeNode::has_finished() const {
    return false;
}

bool TreeNode::is_expanded() const {
    return false;
}

TreeNode *TreeNode::expand() {
    return nullptr;
}

TreeNode *TreeNode::select() const {
    return nullptr;
}

int TreeNode::simulate() const {
    return 0;
}

void TreeNode::bp() {

}

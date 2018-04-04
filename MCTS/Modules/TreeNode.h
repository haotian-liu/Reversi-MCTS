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
static const auto boardStateHasher = [](const Board &board) {
    return board.get(1) | board.get(2);
};

struct TreeNodeStatistic {
    explicit TreeNodeStatistic(int simuls, double playout) : simuls(simuls), playout(playout) {}
    int simuls = 0;
    double playout = 0.0;
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
    const Action * best_action() const;
    TreeNode *find(TreeNode *target) const;
    double simulate() const;
    void bp(double value);
    int get_current_player() const { return state.board.get_player(); }

private:
    State state;
    TreeNode *parent;
    std::vector<Action> get_available_actions() const;

    std::unordered_map<Action, TreeNode *, decltype(actionHasher)> children;
    static std::unordered_map<Board, TreeNodeStatistic, decltype(boardStateHasher)> recorder;
    double playout;
    static int total_simul;
    int simuls;

    double ucb() const;
    void sync_global_recorder(double value);

public:
    auto get_children() const -> const decltype(children) {
        return children;
    }
};


#endif //REVERSI_TREENODE_H

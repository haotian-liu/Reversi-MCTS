//
// Created by Haotian on 2018/3/27.
//

#ifndef REVERSI_ACTION_H
#define REVERSI_ACTION_H

#include <unordered_map>

class Action {
public:
    explicit Action(int coord, int player) : coord(63 - coord), player(player) {
        //
    }
    int get_coord() const {
        return 63 - coord;
    }
    int get_player() const {
        return player;
    }
    bool operator==(const Action &action) const {
        return this->get_coord() == action.get_coord();
    }

private:
    int coord;
    int player;
};


#endif //REVERSI_ACTION_H

#pragma once
// Standard headers
#include <cassert>
#include <string>
#include <vector>

// My headers
#include "cell_type.h"

class Character {
private:
    const std::string name;

public:
    int loc_x;
    int loc_y;
    cell_type player_icon;

    Character(const std::string& name_ = "Jim") :
        name(name_)
    {
        player_icon.icon = '@';
        loc_x = 1;
        loc_y = 1;
    }

    std::string get_name() {
        return name;
    }

    std::vector<int> get_location() {
        return { loc_x, loc_y };
    }

    cell_type get_icon() {
        return player_icon;
    }

    void change_location(const int& move_x, const int& move_y) {
        loc_x += move_x;
        loc_y += move_y;
    }
};

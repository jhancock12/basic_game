#pragma once
// Standard headers
#include <utility>

// My headers
#include "cell_type.h"

class Alien {
private:

public:
    Cell alien_icon;
    int loc_x;
    int loc_y;
    int direction_x;
    int direction_y;
    int health;
    int value;

    Alien(int loc_x_, int loc_y_) :
        loc_x(loc_x_),
        loc_y(loc_y_)
    {
        alien_icon.icon = 'J';
        alien_icon.walkable = false;
        direction_x = 0;
        direction_y = 1;
        health = 1;
        value = 1;
    }

    std::pair<int, int> get_location() {
        return { loc_x, loc_y };
    }

    std::pair<int, int> get_direction() {
        return { direction_x, direction_y };
    }

    Cell get_icon() {
        return alien_icon;
    }

    int get_health() {
        return health;
    }

    int get_value() {
        return value;
    }

    void set_location(int new_x, int new_y) {
        loc_x = new_x;
        loc_y = new_y;
    }

    void set_direction(int new_direction_x, int new_direction_y) {
        direction_x = new_direction_x;
        direction_y = new_direction_y;
    }

    void change_location(int move_x, int move_y) {
        loc_x += move_x;
        loc_y += move_y;
    }

    void remove_health(int amount) {
        health -= amount;
    }
};


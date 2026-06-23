#pragma once
// Standard headers
#include <utility>

// My headers
#include "config.h"
#include "cell_type.h"

class Alien {
private:

public:
    Cell alien_icon;
    float position_x;
    float position_y;
    float velocity_x;
    float velocity_y;
    int health;
    int value;

    Alien(float position_x_, float position_y_) :
        position_x(position_x_),
        position_y(position_y_)
    {
        alien_icon.icon = ALIEN_ICON;
        alien_icon.walkable = false;
        velocity_x = ALIEN_VELOCITY_X;
        velocity_y = ALIEN_VELOCITY_Y;
        health = ALIEN_HEALTH;
        value = ALIEN_VALUE;
    }

    std::pair<float, float> get_position() {
        return { position_x, position_y };
    }

    std::pair<float, float> get_velocity() {
        return { velocity_x, velocity_y };
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

    void set_position(float new_x, float new_y) {
        position_x = new_x;
        position_y = new_y;
    }

    void set_velocity(float new_velocity_x, float new_velocity_y) {
        velocity_x = new_velocity_x;
        velocity_y = new_velocity_y;
    }

    void change_position(float move_x, float move_y) {
        position_x += move_x;
        position_y += move_y;
    }

    void remove_health(int amount) {
        health -= amount;
    }
};


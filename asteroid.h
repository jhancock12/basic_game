#pragma once
// Standard headers
#include <utility>
#include <vector>

// My headers
#include "config.h"
#include "cell_type.h"

class Asteroid {
private:

public:
    Cell asteroid_icon;
    float position_x;
    float position_y;
    float velocity_x;
    float velocity_y;
    int health;
    int value;

    Asteroid(float position_x_, float position_y_, float velocity_x_, float velocity_y_) :
        position_x(position_x_),
        position_y(position_y_),
        velocity_x(velocity_x_),
        velocity_y(velocity_y_)
    {
        asteroid_icon.icon = ASTEROID_ICON;
        asteroid_icon.walkable = false;
        health = ASTEROID_HEALTH;
        value = ASTEROID_VALUE;
    }

    std::pair<float, float> get_position() {
        return { position_x, position_y };
    }

    std::pair<float, float> get_velocity() {
        return { velocity_x, velocity_y };
    }

    Cell get_icon() {
        return asteroid_icon;
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

struct AsteroidGroup {
    std::vector<Asteroid> asteroid_list;
    int health = 1;
};


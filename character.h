#pragma once
// Standard headers
#include <cassert>
#include <string>
#include <vector>
#include <utility>

// My headers
#include "config.h"
#include "cell_type.h"

class Character {
private:
    std::string name;

public:
    Cell player_icon;
    float position_x;
    float position_y;
    int health;
    int score;
    
    Character(const std::string& name_) :
        name(name_)
    {
        player_icon.icon = PLAYER_ICON;
        player_icon.walkable = false;
        health = PLAYER_HEALTH;
        score = 0;
        position_x = 1.0;
        position_y = 1.0;
    }

    std::string get_name() {
        return name;
    }

    std::pair<float, float> get_position() {
        return { position_x, position_y };
    }

    Cell get_icon() {
        return player_icon;
    }

    int get_health() {
        return health;
    }

    int get_score() {
        return score;
    }

    void set_position(float new_x, float new_y) {
        position_x = new_x;
        position_y = new_y;
    }

    void change_position(float move_x, float move_y) {
        position_x += move_x;
        position_y += move_y;
    }

    void change_score(int score_) {
        score += score_;
    }

    void remove_health(int amount) {
        health -= amount;
    }
};

#pragma once
// Standard headers
#include <cassert>
#include <string>
#include <vector>

// My headers
#include "map.h"
#include "character.h"

class GameEngine {
private:
    std::string player_name;
    Map map;

public:
    Character character;

    GameEngine(const std::string& name_ = "Jim") :
        player_name(name_),
        map(),
        character(name_)
    {
        // Initialization
    }
    void display() {
        std::vector<int> character_location = character.get_location();
        cell_type icon = character.get_icon();
        map.display(character_location, icon);
    }

    void update_player_position(const int& move_x, const int& move_y) {
        std::vector<int> character_location = character.get_location();
        int character_loc_x = character_location[0];
        int character_loc_y = character_location[1];

        if (map.is_walkable(character_loc_x + move_x, character_loc_y + move_y)) {
            character.change_location(move_x, move_y);
        }
    }

};
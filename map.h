#pragma once
// Standard headers
#include <iostream>
#include <cassert>
#include <vector>
#include <utility>

// My headers
#include "cell_type.h"
#include "entity_type.h"

class Map {
private:
    typedef std::vector<Cell> map_type;

    const Cell WALL = { '#', false };
    const Cell FLOOR = { ' ', true };

    const int n_x;
    const int n_y;

    map_type map;
    std::vector<char> map_print;

    int index(int x, int y) {
        return x * n_y + y;
    }

    map_type initialize_map() {
        map_type map(n_x * n_y);
        for (int x = 0; x < n_x; ++x) {
            for (int y = 0; y < n_y; ++y) {
                if ((x == 0) or (x == n_x - 1) or (y == 0) or (y == n_y - 1)) {
                    map[index(x, y)] = WALL;
                }
                else {
                    map[index(x, y)] = FLOOR;
                }

            }
        }
        return map;
    }

    std::vector<char> initialize_map_print() {
        std::vector<char> map_print(n_x * n_y);
        for (int x = 0; x < n_x; ++x) {
            for (int y = 0; y < n_y; ++y) {
                map_print[index(x, y)] = map[index(x, y)].icon;
            }
        }
        return map_print;
    }

   
public:
    Map(int n_x_ = 20, int n_y_ = 100) :
        n_x(n_x_),
        n_y(n_y_)
    {
        assert((n_x_ > 0) && "n_x must be positive [class Map]");
        assert((n_y_ > 0) && "n_y must be positive [class Map]");

        map = initialize_map();
        map_print = initialize_map_print();
    }

    std::pair<int, int> get_dimensions() {
        return { n_x, n_y };
    }

    bool is_walkable(int x, int y) {
        assert((x < n_x) && "Site for checking must be in the map [class Map; function is_walkable]");
        assert((y < n_y) && "Site for checking must be in the map [class Map; function is_walkable]");

        return map[index(x, y)].walkable;
    }

    std::string display(const std::vector<Entity>& entities) {

        std::vector<char> map_print_ = map_print;

        for (int entity_index = 0; entity_index < entities.size(); ++entity_index) {
            map_print_[index(entities[entity_index].loc_x, entities[entity_index].loc_y)] = entities[entity_index].icon;
        }

        std::string frame = "";
        for (int x = 0; x < n_x; ++x) {
            for (int y = 0; y < n_y; ++y) {    
                frame.push_back(map_print_[index(x, y)]);
            }
            frame.append("\n");
        }
        return frame;
    }
};
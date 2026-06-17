#pragma once
// Standard headers
#include <iostream>
#include <cassert>
#include <vector>

// My headers
#include "cell_type.h"

class Map {
private:
    typedef std::vector<std::vector<cell_type>> map_type;

    const cell_type WALL = { '#', false };
    const cell_type FLOOR = { '.', true };

    const int n_x;
    const int n_y;

    map_type map;

    map_type initialize_map() {
        map_type map;
        for (int x = 0; x < n_x; ++x) {
            std::vector<cell_type> map_temp;
            for (int y = 0; y < n_y; ++y) {
                if ((x == 0) or (x == n_x - 1) or (y == 0) or (y == n_y - 1)) {
                    map_temp.push_back(WALL);
                }
                else {
                    map_temp.push_back(FLOOR);
                }

            }
            map.push_back(map_temp);
        }
        return map;
    }

public:
    Map(const int& n_x_ = 25, const int& n_y_ = 100) :
        n_x(n_x_),
        n_y(n_y_)
    {
        assert((n_x_ > 0) && "n_x must be positive [class Map]");
        assert((n_y_ > 0) && "n_y must be positive [class Map]");

        map = initialize_map();
    }

    bool is_walkable(const int& x, const int& y) {
        return map[x][y].walkable;
    }

    void display(const std::vector<int>& character_location, const cell_type& character_icon) {
        int character_loc_x = character_location[0];
        int character_loc_y = character_location[1];
        for (int x = 0; x < n_x; ++x) {
            for (int y = 0; y < n_y; ++y) {
                if ((x == character_loc_x) and (y == character_loc_y)) {
                    std::cout << character_icon.icon;
                }
                else {
                    std::cout << map[x][y].icon;
                }
            }
            std::cout << "\n";
        }
    }
};
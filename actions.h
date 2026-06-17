#pragma once

// Standard headers
#include <conio.h>

// My headers

struct PlayerAction {
	int move_x = 0;
	int move_y = 0;
	bool quit = false;
};

PlayerAction action_function(const char& key_pressed) {
    PlayerAction player_action{
        0, 0, false
    };

    const char FORWARD = 'w';
    const char BACKWARD = 's';
    const char LEFT = 'a';
    const char RIGHT = 'd';
    const char QUIT = 'q';


    switch (key_pressed) {
        case FORWARD:
            player_action.move_x = -1;
            break;
        case LEFT:
            player_action.move_y = -1;
            break;
        case RIGHT:
            player_action.move_y = 1;
            break;
        case BACKWARD:
            player_action.move_x = 1;
            break;
        case QUIT:
            player_action.quit = true;
            break;
        }
    return player_action;
}
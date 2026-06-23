#pragma once

// Standard headers
#include <conio.h>

// My headers
#include "config.h"

struct PlayerAction {
    bool quit = false;
    bool pause = false;
    bool confirm = false;
    bool shoot_forward = false;
    bool shoot_backward = false;
    bool shoot_left = false;
    bool shoot_right = false;
	float move_x = 0.0;
	float move_y = 0.0;
    
};

PlayerAction action_function(char key_pressed, bool pause) {
    PlayerAction player_action;

    switch (key_pressed) {
        case FORWARD:
            player_action.move_x = -1.0;
            break;
        case LEFT:
            player_action.move_y = -1.0;
            break;
        case RIGHT:
            player_action.move_y = 1.0;
            break;
        case BACKWARD:
            player_action.move_x = 1.0;
            break;
        case SHOOT_FORWARD:
            player_action.shoot_forward = true;
            break;
        case SHOOT_BACKWARD:
            player_action.shoot_backward = true;
            break;
        case SHOOT_LEFT:
            player_action.shoot_left = true;
            break;
        case SHOOT_RIGHT:
            player_action.shoot_right = true;
            break;
        case PAUSE:
            player_action.pause = true;
            break;
        case CONFIRM:
            player_action.confirm = true;
            break;
        case QUIT:
            player_action.quit = true;
            break;
        }
    if (pause) {
        player_action.pause = pause;
    }
    return player_action;
}
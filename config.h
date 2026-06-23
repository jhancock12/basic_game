#pragma once
// Standard headers
#include <string>

// menu
const char MENU_TOP = '-';
const char MENU_SIDE = '|';

// game settings
const int ALIEN_MAX_N = 0;
const int MAXIMUM_CYLES = 10000;

// map 
const int MAP_N_X = 50;
const int MAP_N_Y = 100;

// game_engine
const float POSITION_TOL = 1.0;

// alien
const char ALIEN_ICON = 'J';
const float ALIEN_VELOCITY_X = 0.0;
const float ALIEN_VELOCITY_Y = 2.0;
const int ALIEN_HEALTH = 1;
const int ALIEN_VALUE = 1;

// asteroid
const char	ASTEROID_ICON = '@';
const float ASTEROID_VELOCITY_X = 0.1;
const float ASTEROID_VELOCITY_Y = 0.1;
const int ASTEROID_HEALTH = 1;
const int ASTEROID_VALUE = 1;

// actions
const char FORWARD = 'w';
const char BACKWARD = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const char SHOOT_FORWARD = 'i';
const char SHOOT_BACKWARD = 'k';
const char SHOOT_LEFT = 'j';
const char SHOOT_RIGHT = 'l';
const char PAUSE = 'p'; 
const char CONFIRM = 'b';
const char QUIT = 'q';

// character
const std::string PLAYER_NAME = "Jim";
const char PLAYER_ICON = 'K';
const int PLAYER_HEALTH = 1000;

// cell_type
const char CELL_ICON = ' ';

// bullet_type
const char BULLET_ICON = '*';
const int BULLET_DAMAGE = 1;

// entity_type 
const char ENTITY_ICON = '.';


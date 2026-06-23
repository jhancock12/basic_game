#pragma once
// Standard headers

// My headers
#include "config.h"

struct Bullet {
    // Defaults to upwards moving
    char icon = BULLET_ICON;
    int damage = BULLET_DAMAGE;
    float velocity_x;
    float velocity_y;
    float position_x;
    float position_y;
    bool friendly;
};

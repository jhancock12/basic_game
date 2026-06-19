#pragma once
// Standard headers

// My headers

struct Bullet {
    // Defaults to upwards moving
    char icon = '*';
    int loc_x = 0;
    int loc_y = 0;
    int direction_x = -1;
    int direction_y = 0;

    int damage = 1;
};

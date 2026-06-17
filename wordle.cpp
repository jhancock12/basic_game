#include <conio.h>

#include "actions.h"
#include "game_engine.h"

int main()
{
    std::cout << "Running \n";
    GameEngine game_engine("James");

    int MAXIMUM_CYLES = 1000;
    int cycle = 0;
    bool stop = false;

    int move_x = 0;
    int move_y = 0;

    while (!(stop) and (cycle < MAXIMUM_CYLES)) {
        cycle += 1;

        move_x = 0;
        move_y = 0;

        system("cls");

        game_engine.display();

        char key_pressed = _getch();

        PlayerAction player_action = action_function(key_pressed);

        stop = player_action.quit;

        game_engine.update_player_position(player_action.move_x, player_action.move_y);

    }
}


#include <conio.h>
#include <thread>
#include <chrono>

#include "actions.h"
#include "game_engine.h"

int main()
{
    std::cout << "Running \n";
    GameEngine game_engine("James");

    int MAXIMUM_CYLES = 10000;
    int cycle = 0;
    bool stop = false;

    int ALIEN_MAX_N = 10;

    int aliens_n = game_engine.get_n_aliens();

    while (!(stop) and (cycle < MAXIMUM_CYLES)) {
        aliens_n = game_engine.get_n_aliens();
        if (aliens_n < ALIEN_MAX_N) {
            game_engine.add_alien(1, 1);
            aliens_n = game_engine.get_n_aliens();
        }

        // Initialization
        PlayerAction player_action;

        // Display
        game_engine.display();

        // Player dynamics
        if (_kbhit()) {
            char key_pressed = _getch();
            player_action = action_function(key_pressed);
        }
        stop = player_action.quit;
        game_engine.update_player_position(player_action.move_x, player_action.move_y);

        // Alien dynamics
        if (cycle % 2 == 0) {
            game_engine.update_aliens_position();
            game_engine.update_aliens_direction();
        }
        
        aliens_n = game_engine.get_n_aliens();

        // Bomber
        for (int n = 0; n < aliens_n; ++n) {
            if (cycle % 7 == n % 2) {
                game_engine.add_alien_bullet(n);
            }

        }

        // Bullet dynamics
        game_engine.add_character_bullet(player_action.shoot);
        game_engine.update_bullets();

        // Checking healths
        game_engine.check_health_remove_dead_aliens();
        if (!game_engine.check_character_alive()) {
            system("cls");
            std::cout << "!!!YOU DIED GAME OVER!!!";
            stop = true;
        }

        // Book keeping
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        cycle += 1;

    }
}


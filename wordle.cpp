#include <conio.h>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

#include "config.h"
#include "actions.h"
#include "game_engine.h"

// Things to do:
// Pause menu - Maybe change settings from there?
// Make prettier stuff w/ more pixels, and zoom out

int main()
{
    std::string name_;
    std::cout << "Enter your name:" << std::endl;
    std::cin >> name_;

    std::ifstream in("highscore.txt");
    int high_score = 0;
    in >> high_score;
    in.close();

    GameEngine game_engine(name_, high_score);

    int cycle = 0;
    bool stop = false;


    int aliens_n = game_engine.get_n_aliens();
    std::pair<int, int> dimensions = game_engine.get_dimensions();

    while (!(stop) and (cycle < MAXIMUM_CYLES)) {
        // Initialization
        PlayerAction player_action;

        if (cycle % 2 == 0) {
            aliens_n = game_engine.get_n_aliens();
            if ((aliens_n < ALIEN_MAX_N) and (cycle % 5 == 0)) {
                game_engine.add_alien((cycle + 10) % (dimensions.first - 2) + 1, (cycle + 10) % (dimensions.second - 2) + 1);
                aliens_n = game_engine.get_n_aliens();
            }

            // Display
            game_engine.display();

            // Alien dynamics
            game_engine.update_aliens_position();
            game_engine.update_aliens_velocity();

            // Player dynamics
            char key_pressed = 0;
            while (_kbhit()) {
                key_pressed = _getch();
            }
            if (key_pressed != 0) {
                player_action = action_function(key_pressed);
            }
            stop = player_action.quit;
            game_engine.update_player_position(player_action.move_x, player_action.move_y);

            aliens_n = game_engine.get_n_aliens();

            // Bomber
            for (int n = 0; n < aliens_n; ++n) {
                if (((cycle / 2) % 7 == n % 2) and ((cycle / 2) % 5 == 0)) {
                    game_engine.add_alien_bullet(n);
                }
            }
        }

        // Bullet dynamics
        game_engine.add_character_bullet(player_action.shoot_forward, player_action.shoot_backward, player_action.shoot_left, player_action.shoot_right);
        game_engine.update_bullets();

        // Checking healths
        game_engine.check_health_remove_dead_aliens();
        if (!game_engine.check_character_alive()) {
            system("cls");
            std::cout << "!!!YOU DIED GAME OVER!!!";
            stop = true;
        }

        // Book keeping
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        cycle += 1;

    }
    int score = game_engine.get_score();
    if (score > high_score) {
        std::ofstream out("highscore.txt");
        out << score;
        out.close();
    }

}


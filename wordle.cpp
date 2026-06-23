#include <conio.h>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

#include "config.h"
#include "pause_menu.h"
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

    GameEngine game_engine(name_);
    std::pair<int, int> dimensions = game_engine.get_dimensions();

    PauseMenu pause_menu(dimensions.first, dimensions.second);
    game_engine.set_high_score(high_score);

    int cycle = 0;
    bool stop = false;
    char key_pressed = 0;

    int aliens_n = game_engine.get_n_aliens();
    
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    int start_cycle = 0;
    bool pause = false;

    while (!(stop) and (cycle < MAXIMUM_CYLES)) {
        PlayerAction player_action;
        player_action.pause = pause;
        while (_kbhit()) {
            key_pressed = _getch();
        }
        if (key_pressed != 0) {
            player_action = action_function(key_pressed, pause);
        }

        if ((player_action.pause) and (cycle != 0)) {
            std::string background = game_engine.get_display();
            std::string frame = pause_menu.display(background);
            game_engine.display_pause(frame);
            pause_menu.update_pause(player_action);
            if (player_action.pause) {
                pause = true;
            }
            else {
                pause = false;
            }
            key_pressed = 0;

            stop = player_action.quit;
        }
        else {
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
                stop = player_action.quit;
                game_engine.update_player_position(player_action.move_x, player_action.move_y);

                key_pressed = 0;

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
            std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Tick rate
            cycle += 1;
            if (cycle % 10 == 0) {
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                int end_cycle = cycle;

                std::chrono::duration<float> elapsed = end - start;
                float time_taken = elapsed.count();
                float cycles_taken = end_cycle - start_cycle;

                float fps = cycles_taken / time_taken;
                game_engine.set_fps(fps);

                start = std::chrono::steady_clock::now();
                start_cycle = cycle;

            }
            pause = false;
        }

        

    }
    int score = game_engine.get_score();
    if (score > high_score) {
        std::ofstream out("highscore.txt");
        out << score;
        out.close();
    }

}


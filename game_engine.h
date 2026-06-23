#pragma once
// Standard headers
#include <cassert>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

// Windows headers
#include <windows.h>

// My headers
#include "config.h"
#include "map.h"
// #include "pause_menu.h"
#include "entity_type.h"
#include "bullet_type.h"

#include "alien.h"
#include "character.h"

class GameEngine {
private:
    std::string player_name;
    Map map;

public:
    int high_score;
    float fps;
    std::pair<int, int> dimensions;
    Character character;
    std::vector<Alien> aliens;
    std::vector<Bullet> bullets;
    
    GameEngine(const std::string& name_ = "Jim") :
        player_name(name_),
        map(),
        character(name_)
    {
        high_score = 0;
        fps = 0.0;
        dimensions = map.get_dimensions();
        character.set_position(dimensions.first - 2, dimensions.second - 2);
    }

    int get_n_aliens() {
        return aliens.size();
    }

    int get_score() {
        return character.get_score();
    }

    void set_high_score(int high_score_) {
        high_score = high_score_;
    }

    void set_fps(float fps_) {
        fps = fps_;
    }

    void clear_screen() {
        COORD coord = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void display() {
        // This is when everything should be int'd
        clear_screen();
        std::pair<float, float> character_position = character.get_position();

        Entity character_entity{ character.get_icon().icon, static_cast<int>(std::round(character_position.first)), static_cast<int>(std::round(character_position.second)) };

        std::vector<Entity> entities;
        entities.push_back(character_entity);

        for (const Bullet& bullet : bullets) {
            Entity bullet_entity{ bullet.icon, static_cast<int>(std::round(bullet.position_x)), static_cast<int>(std::round(bullet.position_y)) };
            entities.push_back(bullet_entity);
        }

        for (Alien& alien : aliens) {
            std::pair<float, float> alien_position = alien.get_position();
            Entity alien_entity{ alien.get_icon().icon, static_cast<int>(std::round(alien_position.first)), static_cast<int>(std::round(alien_position.second)) };
            entities.push_back(alien_entity);
        }

        std::string frame = map.display(entities);
        std::cout << frame << std::endl;
        std::cout << player_name << " health: " << character.get_health() << " | " << player_name << " score: " << character.get_score() << std::endl;
        std::cout << "Highscore: " << high_score << std::endl;
        std::cout << "FPS: " << fps << std::endl;
    }

    std::string get_display() {
        std::pair<float, float> character_position = character.get_position();

        Entity character_entity{ character.get_icon().icon, static_cast<int>(std::round(character_position.first)), static_cast<int>(std::round(character_position.second)) };

        std::vector<Entity> entities;
        entities.push_back(character_entity);

        for (const Bullet& bullet : bullets) {
            Entity bullet_entity{ bullet.icon, static_cast<int>(std::round(bullet.position_x)), static_cast<int>(std::round(bullet.position_y)) };
            entities.push_back(bullet_entity);
        }

        for (Alien& alien : aliens) {
            std::pair<float, float> alien_position = alien.get_position();
            Entity alien_entity{ alien.get_icon().icon, static_cast<int>(std::round(alien_position.first)), static_cast<int>(std::round(alien_position.second)) };
            entities.push_back(alien_entity);
        }

        std::string frame = map.display(entities);
        frame = frame + "\n" + player_name + " health: " + std::to_string(character.get_health()) + " | " + player_name + " score: " + std::to_string(character.get_score());
        frame = frame + "\n" + "Highscore: " + std::to_string(high_score);
        frame = frame + "\n" + "FPS: " + std::to_string(fps);

        return frame;
    }

    void display_pause(std::string frame) {
        clear_screen();
        std::cout << frame << std::endl;
    }

    void update_player_position(float move_x, float move_y) {
        std::pair<float, float> character_position = character.get_position();

        if (map.is_walkable(static_cast<int>(std::round(character_position.first + move_x)), static_cast<int>(std::round(character_position.second + move_y)))) {
            character.change_position(move_x, move_y);
        }
    }

    std::pair<int, int> get_dimensions() {
        return dimensions;
    }

    void add_alien(float position_x, float position_y) {
        aliens.push_back(Alien(position_x, position_y));
    }

    void update_aliens_position() {
        for (int j = 0; j < aliens.size(); ++j) {
            std::pair<float, float> alien_position = aliens[j].get_position();
            std::pair<float, float> alien_velocity = aliens[j].get_velocity();
            if (map.is_walkable(static_cast<int>(std::round(alien_position.first + alien_velocity.first)), static_cast<int>(std::round(alien_position.second + alien_velocity.second)))) {
                aliens[j].change_position(alien_velocity.first, alien_velocity.second);
            }
            if (static_cast<int>(std::round(alien_position.first + alien_velocity.first)) > dimensions.first - 2) {
                aliens[j].set_position(dimensions.first - 2, alien_position.second);
                aliens[j].set_velocity(-alien_velocity.first, alien_velocity.second);
            }
            if (static_cast<int>(std::round(alien_position.second + alien_velocity.second)) > dimensions.second - 2) {
                aliens[j].set_position(alien_position.first, dimensions.second - 2);
                aliens[j].set_velocity(alien_velocity.first, -alien_velocity.second);
            }
            if (static_cast<int>(std::round(alien_position.first + alien_velocity.first)) < 1) {
                aliens[j].set_position(1, alien_position.second);
                aliens[j].set_velocity(-alien_velocity.first, alien_velocity.second);
            }
            if (static_cast<int>(std::round(alien_position.second + alien_velocity.second)) < 1) {
                aliens[j].set_position(alien_position.first, 1);
                aliens[j].set_velocity(alien_velocity.first, -alien_velocity.second);
            }
        }
    }

    void update_aliens_velocity() {
        for (int j = 0; j < aliens.size(); ++j) {
            std::pair<float, float> alien_position = aliens[j].get_position();
            std::pair<float, float> alien_velocity = aliens[j].get_velocity();

            std::pair<int, int> alien_position_ints = { static_cast<int>(std::round(alien_position.first)), static_cast<int>(std::round(alien_position.second)) };

            if ((alien_position_ints.second == dimensions.second - 2) and (alien_velocity.first != 1.0)) {
                aliens[j].set_velocity(1.0, 0.0);
            }
            else if ((alien_position_ints.second == 1) and (alien_position_ints.first != 1) and (alien_velocity.first != 1.0)) {
                aliens[j].set_velocity(1.0, 0.0);
            }
            else if (alien_position_ints.second == dimensions.second - 2) {
                aliens[j].set_velocity(0.0, -ALIEN_VELOCITY_Y);
            }
            else if ((alien_position_ints.second == 1) and (alien_position_ints.first != 1)) {
                aliens[j].set_velocity(0.0, ALIEN_VELOCITY_Y);
            }
        }
        
    }

    void add_character_bullet(bool shoot_forward, bool shoot_backward, bool shoot_left, bool shoot_right) {
        if (shoot_forward or shoot_backward or shoot_left or shoot_right) {
            std::pair<float, float> character_position = character.get_position();
            Bullet bullet;
            if (shoot_forward) {
                bullet.position_x = character_position.first - 0.5;
                bullet.position_y = character_position.second;
                bullet.velocity_x = -0.8;
                bullet.velocity_y = 0.0;
            }
            else if (shoot_backward) {
                bullet.position_x = character_position.first + 0.5;
                bullet.position_y = character_position.second;
                bullet.velocity_x = 0.8;
                bullet.velocity_y = 0.0;
            }
            else if (shoot_left) {
                bullet.position_x = character_position.first;
                bullet.position_y = character_position.second - 1;
                bullet.velocity_x = 0.0;
                bullet.velocity_y = -0.8;
            }
            else if (shoot_right) {
                bullet.position_x = character_position.first;
                bullet.position_y = character_position.second + 1;
                bullet.velocity_x = 0.0;
                bullet.velocity_y = 0.8;
            }
            bullet.friendly = true;
            bullets.push_back(bullet);
        }
    }

    void add_alien_bullet(int alien_index) {
        std::pair<float, float> alien_position = aliens[alien_index].get_position();
        Bullet bullet;
        bullet.position_x = alien_position.first;
        bullet.position_y = alien_position.second;
        bullet.velocity_x = 1;
        bullet.velocity_y = 0;
        bullet.friendly = false;
        bullets.push_back(bullet);
    }

    void update_bullets() {
        std::pair<float, float> character_position = character.get_position();
        std::vector<Bullet> new_bullets;
        for (int bullet_index = 0; bullet_index < bullets.size(); ++bullet_index) {
            bool hit = false;
            if ((abs(bullets[bullet_index].position_x + bullets[bullet_index].velocity_x - character_position.first) < POSITION_TOL) and (abs(bullets[bullet_index].position_y + bullets[bullet_index].velocity_y - character_position.second) < POSITION_TOL)) {
                if (!bullets[bullet_index].friendly) {
                    character.remove_health(bullets[bullet_index].damage);
                    hit = true;
                }
                
            }

            for (int alien_index = 0; alien_index < aliens.size(); ++alien_index) {
                std::pair<float, float> alien_position = aliens[alien_index].get_position();
                if ((abs(bullets[bullet_index].position_x + bullets[bullet_index].velocity_x - alien_position.first) < POSITION_TOL) and (abs(bullets[bullet_index].position_y + bullets[bullet_index].velocity_y - alien_position.second) < POSITION_TOL)) {
                    if (bullets[bullet_index].friendly) {
                        aliens[alien_index].remove_health(bullets[bullet_index].damage);
                        hit = true;
                    }
                }
            }

            if (!hit) {
                if (map.is_walkable(static_cast<int>(std::round(bullets[bullet_index].position_x + bullets[bullet_index].velocity_x)), static_cast<int>(std::round(bullets[bullet_index].position_y + bullets[bullet_index].velocity_y)))) {
                    bullets[bullet_index].position_x += bullets[bullet_index].velocity_x;
                    bullets[bullet_index].position_y += bullets[bullet_index].velocity_y;
                    new_bullets.push_back(bullets[bullet_index]);
                }
            }
        }
        bullets = new_bullets;
    }

    void check_health_remove_dead_aliens() {
        std::vector<Alien> left_overs;
        int score_ = 0;
        for (int j = 0; j < aliens.size(); ++j) {
            Alien alien = aliens[j];
            if (alien.get_health() > 0) {
                left_overs.push_back(alien);
            }
            else {
                score_ += alien.get_value();
            }
        }
        character.change_score(score_);
        aliens = left_overs;
    }

    bool check_character_alive() {
        if (character.get_health() > 0) {
            return true;
        }
        else {
            return false;
        }
    }

};
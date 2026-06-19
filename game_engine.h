#pragma once
// Standard headers
#include <cassert>
#include <string>
#include <vector>
#include <utility>

// Windows headers
#include <windows.h>

// My headers
#include "map.h"
#include "entity_type.h"
#include "bullet_type.h"

#include "alien.h"
#include "character.h"

class GameEngine {
private:
    std::string player_name;
    Map map;

public:
    std::pair<int, int> dimensions;
    Character character;
    std::vector<Alien> aliens;
    std::vector<Bullet> bullets;

    GameEngine(const std::string& name_ = "Jim") :
        player_name(name_),
        map(),
        character(name_)
    {
        dimensions = map.get_dimensions();
        character.set_location(dimensions.first - 2, dimensions.second - 2);
    }

    int get_n_aliens() {
        return aliens.size();
    }

    void clear_screen() {
        COORD coord = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void display() {
        clear_screen();
        std::pair<int, int> character_location = character.get_location();

        Entity character_entity{ character.get_icon().icon, character_location.first, character_location.second };

        std::vector<Entity> entities;
        entities.push_back(character_entity);

        for (const Bullet& bullet : bullets) {
            Entity bullet_entity{ bullet.icon, bullet.loc_x, bullet.loc_y };
            entities.push_back(bullet_entity);
        }

        for (Alien& alien : aliens) {
            std::pair<int, int> alien_location = alien.get_location();
            Entity alien_entity{ alien.get_icon().icon, alien_location.first, alien_location.second };
            entities.push_back(alien_entity);
        }

        std::string frame = map.display(entities);
        std::cout << frame << std::endl;
        std::cout << "Health: " << character.get_health() << " | Score: " << character.get_score() << std::endl;
    }

    void update_player_position(int move_x, int move_y) {
        std::pair<int, int> character_location = character.get_location();

        if (map.is_walkable(character_location.first + move_x, character_location.second + move_y)) {
            character.change_location(move_x, move_y);
        }
    }

    void add_alien(int loc_x, int loc_y) {
        aliens.push_back(Alien(loc_x, loc_y));
    }

    void update_aliens_position() {
        for (int j = 0; j < aliens.size(); ++j) {
            std::pair<int, int> alien_location = aliens[j].get_location();
            std::pair<int, int> alien_direction = aliens[j].get_direction();

            if (map.is_walkable(alien_location.first + alien_direction.first, alien_location.second + alien_direction.second)) {
                aliens[j].change_location(alien_direction.first, alien_direction.second);
            }
        }
    }

    void update_aliens_direction() {
        for (int j = 0; j < aliens.size(); ++j) {
            std::pair<int, int> alien_location = aliens[j].get_location();
            std::pair<int, int> alien_direction = aliens[j].get_direction();

            if ((alien_location.second == dimensions.second - 2) and (alien_direction.first != 1)) {
                aliens[j].set_direction(1, 0);
            }
            else if ((alien_location.second == 1) and (alien_location.first != 1) and (alien_direction.first != 1)) {
                aliens[j].set_direction(1, 0);
            }
            else if (alien_location.second == dimensions.second - 2) {
                aliens[j].set_direction(0, -1);
            }
            else if ((alien_location.second == 1) and (alien_location.first != 1)) {
                aliens[j].set_direction(0, 1);
            }
        }
        
    }

    void add_character_bullet(bool shoot) {
        if (shoot) {
            std::pair<int, int> character_location = character.get_location();
            Bullet bullet;
            bullet.loc_x = character_location.first;
            bullet.loc_y = character_location.second;
            bullets.push_back(bullet);
        }
    }

    void add_alien_bullet(int alien_index) {
        std::pair<int, int> alien_location = aliens[alien_index].get_location();
        Bullet bullet;
        bullet.loc_x = alien_location.first;
        bullet.loc_y = alien_location.second;
        bullet.direction_x = 1;
        bullets.push_back(bullet);
    }

    void update_bullets() {
        std::pair<int, int> character_location = character.get_location();
        std::vector<Bullet> new_bullets;
        for (int bullet_index = 0; bullet_index < bullets.size(); ++bullet_index) {
            bool hit = false;
            if ((bullets[bullet_index].loc_x + bullets[bullet_index].direction_x == character_location.first) and (bullets[bullet_index].loc_y + bullets[bullet_index].direction_y == character_location.second)) {
                character.remove_health(bullets[bullet_index].damage);
                hit = true;
            }

            for (int alien_index = 0; alien_index < aliens.size(); ++alien_index) {
                std::pair<int, int> alien_location = aliens[alien_index].get_location();
                if ((bullets[bullet_index].loc_x + bullets[bullet_index].direction_x == alien_location.first) and (bullets[bullet_index].loc_y + bullets[bullet_index].direction_y == alien_location.second)) {
                    aliens[alien_index].remove_health(bullets[bullet_index].damage);
                    hit = true;
                }
            }

            if (!hit) {
                if (map.is_walkable(bullets[bullet_index].loc_x + bullets[bullet_index].direction_x, bullets[bullet_index].loc_y + bullets[bullet_index].direction_y)) {
                    bullets[bullet_index].loc_x += bullets[bullet_index].direction_x;
                    bullets[bullet_index].loc_y += bullets[bullet_index].direction_y;
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
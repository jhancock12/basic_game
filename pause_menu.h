#pragma once
// Standard headers
#include <cassert>
#include <string>
#include <vector>

// My headers
#include "config.h"
#include "actions.h"

// Need to remember at some point that it will be flattened

class PauseMenu {
private:
    typedef std::vector<std::vector<char>> menu_vector;
    const int n_x; // height
    const int n_y; // width
    menu_vector menu_blank;
    menu_vector menu_quit;
    menu_vector menu_continue;
    std::vector<menu_vector> menus;
    int height = 9;
    int width = 18;

    const char top = MENU_TOP;
    const char sid = MENU_SIDE;
    const char bla = ' ';

    int menu_length = 0;

    int pause_index = 0;

public:
    int offset_height;
    int offset_width;
    menu_vector menu;

    PauseMenu(const int n_x_, const int n_y_) :
        n_x(n_x_),
        n_y(n_y_)
    {

        offset_height = (n_x - height) / 2;
        offset_width = (n_y - width) / 2;
        menu_blank = {
        { top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top },
        { sid, bla, bla, bla, bla, bla, bla, 'Q', 'U', 'I', 'T', bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, 'C', 'O', 'N', 'T', 'I', 'N', 'U', 'E', bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top }
        };
        menu_quit = {
        { top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top },
        { sid, bla, bla, bla, '-', '>', bla, 'Q', 'U', 'I', 'T', bla, '<', '-', bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, 'C', 'O', 'N', 'T', 'I', 'N', 'U', 'E', bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top }
        };
        menu_continue = {
        { top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top },
        { sid, bla, bla, bla, bla, bla, bla, 'Q', 'U', 'I', 'T', bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, '-', '>', bla, 'C', 'O', 'N', 'T', 'I', 'N', 'U', 'E', bla, '<', '-', bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { sid, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, bla, sid },
        { top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top, top }
        };

        menus = { menu_quit, menu_continue };
        menu = menus[pause_index];
        menu_length = menus.size();
    }

    int index(int x, int y) {
        return x * (n_y + 1) + y; // Acounts for the "\n"'s
    }

    void update_pause(PlayerAction& player_action) {
        int sign = (player_action.move_x > 0) - (player_action.move_x < 0);
        pause_index += sign;
        pause_index = (pause_index + menu_length) % menu_length;

        if (pause_index == 0) {
            player_action.quit = player_action.confirm;
        }
        else if (pause_index == 1) {
            player_action.pause = !(player_action.confirm);
        }
    }

    std::string display(const std::string& background) {
        menu = menus[pause_index];
        std::string frame = "";
        for (int x = 0; x < n_x; ++x) {
            for (int y = 0; y < n_y; ++y) {
                if ((x >= offset_height) and (x < offset_height + height) and (y >= offset_width) and (y < offset_width + width)) {
                    frame.push_back(menu[x - offset_height][y - offset_width]);
                }
                else {
                    frame.push_back(background[index(x, y)]);
                }
            }
            frame.append("\n");
        }
        return frame;
    }
};

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "includes/main_menu.h"
#include "includes/drawing.h"
#include "includes/game_grid.h"
#include "includes/magic_numbers.h"
#include "includes/ships.h"

int main(int argc, char **argv)
{
    checkScreenSize();
    //window declarations
    WINDOW *main_window = create_main_window(MAIN_SCREEN_H,MAIN_SCREEN_W,MAIN_SCREEN_Y,MAIN_SCREEN_X);
    //main menu related
    WINDOW *options[OPTION_COUNT];
    WINDOW *title;
    //game map/ship placement related
    WINDOW *inventory[2];
    WINDOW *game_maps[2];

    initscr();
    //setting up input options
    //characters are being sent to the buffer without the need for '\n'
    cbreak();
    //characters typed on the kboard are not displayed on the screen
    noecho();
    //enables "arrow keys" support
    keypad(stdscr, TRUE);
    //hides the cursor
    curs_set(0);
    //refreshes terminal so changes can take effect
    wrefresh(stdscr);
    start_color();
    // variable to determine which portion of the game should be displayed
    // (eg. if the user is currently in the main menu)
    // GAMESTATE = 0 <- QUIT *Done
    // GAMESTATE = 1 <- MAIN MENU *Done 
    // GAMESTATE = 2 <- SHIP PLACEMENT *WIP
    // GAMESTATE = 3 <- GAMEPLAY *WIP
    // GAMESTATE = 4 <- REVEAL SHIPS @ GAME END *WIP
    // GAMESTATE = 5 <- END OF GAME STATS *WIP
    int GAMESTATE = 1;
    
    //initial gamestate will be @ main menu
    //starting game loop

    ship testShip;
    testShip.orientation = 2;
    testShip.modules = 4;
    testShip.Y = 5;
    testShip.X = 5;

    while(GAMESTATE)
    {
        switch (GAMESTATE)
            {
            case 1:
                draw_main_menu(title, options);
                menu_navigation(&GAMESTATE, options);
                break;
            case 2:
                draw_game_grid(game_maps);
                draw_inventory(inventory);
                draw_ship(game_maps[0], testShip);
                while(1)
                {

                }
                break;
            
            default:
                break;
            }

    }

    endwin();
    return 0;
}
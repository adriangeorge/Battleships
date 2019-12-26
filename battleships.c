#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "includes/color_pairs.h"
#include "includes/magic_numbers.h"
#include "includes/main_menu.h"
#include "includes/placement.h"

int main()
{
    initscr();   
    //window declarations
    WINDOW *background;

    //main menu window declarations
    WINDOW *options[OPTION_COUNT];
    WINDOW *title;
    
    //game map/ship placement related
    WINDOW *inventory[2];
    WINDOW *game_map[2];

    //setting up input options
    //characters are being sent to the buffer without the need for '\n'
    cbreak();
    //characters typed on the keyboard are not displayed on the screen
    noecho();
    //enables "arrow keys" support
    keypad(stdscr, TRUE);
    //hides the cursor
    curs_set(0);
    //refreshes terminal so changes can take effect
    wrefresh(stdscr);


    int GAMESTATE = 1;
    // variable to determine the current status of the game
    // (eg. if the user is currently in the main menu)
    // GAMESTATE = 0 <- QUIT/GAME END *Done
    // GAMESTATE = 1 <- MAIN MENU *Done 
    // GAMESTATE = 2 <- SHIP PLACEMENT *WIP
    // GAMESTATE = 3 <- GAMEPLAY *WIP
    // GAMESTATE = 4 <- REVEAL SHIPS @ GAME END *WIP
    // GAMESTATE = 5 <- END OF GAME STATS *WIP
   
    //initial GAMESTATE is will be at main menu (1)
    //but if the player gives args at runtime
    //game will skip to GAMESTATE 3

    //game loop which will stop at GAMESTATE 0
    while(GAMESTATE)
    {
        switch (GAMESTATE)
            {
            case 1:
                menu(&GAMESTATE, options, background,  title);
                break;
            case 2:
                placement(&GAMESTATE, game_map, inventory);
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
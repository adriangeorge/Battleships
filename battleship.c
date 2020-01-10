// CIOBAN GEORGE ADRIAN 314CC
// TEMA 02 - PROGRAMAREA CALCULATOARELOR
// BATTLESHIPS
// FIRST COMMIT 14 DEC 2019
// https://github.com/adriangeorge/Tema-PC-02.git

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#ifndef __COLOR__
#define __COLOR__
#include "color_pairs.h"
#endif

#ifndef __MAGIC__
#define __MAGIC__
#include "magic_numbers.h"
#endif

#ifndef __MENU__
#define __MENU__
#include "main_menu.h"
#endif

#ifndef __PLACEMENT__
#define __PLACEMENT__
#include "placement.h"
#endif

#ifndef __GAMEPLAY__
#define __GAMEPLAY__
#include "gameplay.h"
#endif

int main(int argc, char* argv[])
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
    //enables arrow keys navigation
    keypad(stdscr, TRUE);
    //hides the cursor
    curs_set(0);
    //refreshes terminal so changes can take effect
    wrefresh(stdscr);

    // variable to determine the current status of the game
    // (eg. if the user is currently in the main menu)
    // GAMESTATE = 0 <- QUIT/GAME END *Done
    // GAMESTATE = 1 <- MAIN MENU *Done 
    // GAMESTATE = 2 <- SHIP PLACEMENT *Done
    // GAMESTATE = 3 <- GAMEPLAY *Done
    // GAMESTATE = 4 <- REVEAL SHIPS @ GAME END *WIP//cut
    // GAMESTATE = 5 <- END OF GAME STATS *WIP //cut
   
    //initial GAMESTATE is will be at main menu (1)
    //but if the player gives args at runtime
    //game will skip to GAMESTATE 3
    
    int GAMESTATE;
    char* map = calloc(25, sizeof(char));
    
    
    if(argc > 1)
    {
        sprintf(map, "%s", argv[1]);
        GAMESTATE = 3;
    }
    else
    {
        sprintf(map, "playerMAP");
        GAMESTATE = 1;
    }
    
    
    while(GAMESTATE)
    {
        switch (GAMESTATE)
            {
            case 1:
                menu(&GAMESTATE, options, background,  title);
                break;
            case 2:
                placement(&GAMESTATE, game_map, inventory);
                break;
            case 3:
                gameplay(&GAMESTATE, game_map, background, map);
                break;
            default:
                break;
            }
    }  
    
    endwin();
    return 1;
}
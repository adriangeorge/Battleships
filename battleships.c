#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "includes/main_menu.h"
#include "includes/drawing.h"



int main(int argc, char **argv)
{
    //window declarations
    WINDOW *main_window;
    //will support multiple options 
    WINDOW *options[OPTION_COUNT];
    WINDOW *title;

    initscr();

    //setting up input options
    //characters are being sent to the buffer without the need for '\n'
    //cbreak();
    //characters typed on the kboard are not displayed on the screen
    noecho();
    //enables "arrow keys" support
    keypad(stdscr, TRUE);
    //hides the cursor
    curs_set(0);
    //refreshes terminal so changes can take effect
    refresh();
    start_color();
    //variable to determine which portion of the game should be displayed
    //(eg. if the user is currently in the main menu)
    // GAMESTATE = 0 <- QUIT
    // GAMESTATE = 1 <- MAIN MENU
    // GAMESTATE = 2 <- SHIP PLACEMENT
    // GAMESTATE = 3 <- GAMEPLAY
    // GAMESTATE = 4 <- REVEAL SHIPS @ GAME END
    // GAMESTATE = 5 <- END OF GAME STATS

    int GAMESTATE;
    
    //initial gamestate will be @ main menu
    while(GAMESTATE)
    {
        switch (GAMESTATE)
            {
            case 1:
                draw_main_menu(main_window,title,options);
                menu_navigation(options);
                break;
            
            case 2:
                
            }
    }
    

    
    
    
    endwin();
    return 0;
}
#include <ncurses.h>
#include "window.h"

#define Y_PADDING_POS   5
#define BUTTON_Y        SCR_H/2 + SCR_Y + (option_count + 1)*iterator 
#define BUTTON_X        SCR_W/2 - 20/2

WINDOW *create_window(int height, int width, int starty, int startx)
{
    WINDOW *local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    start_color();
    init_pair(2, COLOR_BLACK,COLOR_WHITE);
    wbkgd(local_win, COLOR_PAIR(2));
    wrefresh(local_win);

    return local_win;
}

void draw_title(WINDOW* splash, int SCR_Y, int SCR_H, int SCR_W)
{
    start_color();
    init_pair(1, COLOR_WHITE,COLOR_BLUE);

    
    splash = newwin(13, 124, 2, 2);
    box(splash, 0, 0);
    wbkgd(splash,COLOR_PAIR(1));
    mvwprintw(splash, 13/2 , 124/2 - 42/2 ,  "BATTLESHIPS [PLACEHOLDER TITLE SCREEN :( ]");
    wrefresh(splash);
}

void draw_buttons(WINDOW **options, int option_count, int SCR_Y, int SCR_H, int SCR_W)
{
    start_color();
    int iterator;
    init_pair(1, COLOR_WHITE,COLOR_BLUE);
    for(iterator = 0 ; iterator < 3 ; iterator++)
        {   
            
            options[iterator] = create_window(3, 20, BUTTON_Y , BUTTON_X);
            wbkgd(options[iterator],COLOR_PAIR(1));
            mvwprintw(options[iterator], 1 , 1,  "OPTION %d " , iterator);
            wrefresh(options[iterator]);
        }
}

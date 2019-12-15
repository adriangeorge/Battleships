#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "includes/window.h"

#define OPTION_COUNT    3
#define SCREEN_Y        0
#define SCREEN_X        0
#define SCREEN_H        32
#define SCREEN_W        128

int main(int argc, char **argv)
{
    WINDOW *my_win;
    WINDOW **options = malloc(3 * sizeof(WINDOW*));
    WINDOW *splashScreen;
    initscr();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
    
    my_win = create_window(SCREEN_H, SCREEN_W, SCREEN_X, SCREEN_Y);
    
    
    int iterator;

    draw_buttons(options , 3 , 0 , 32, 128);
    draw_title(splashScreen, SCREEN_Y,SCREEN_H,SCREEN_W);

    iterator = getch();
    wrefresh(my_win);
    
    endwin();
    return 0;
}
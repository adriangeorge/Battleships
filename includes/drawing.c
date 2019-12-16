#include <ncurses.h>
#include "drawing.h"

//creating a default window with white background and black writing
WINDOW* create_main_window(int SCR_H, int SCR_W, int SCR_Y, int SCR_X)
{
    start_color();
    WINDOW *local_win = newwin(SCR_H, SCR_W, SCR_Y, SCR_X);
    box(local_win, 0, 0);
    init_pair(2, COLOR_BLACK,COLOR_WHITE);
    wbkgd(local_win,COLOR_PAIR(2));
    wrefresh(local_win);
    return local_win;
}

WINDOW* create_window(int SCR_H, int SCR_W, int SCR_Y, int SCR_X)
{
    WINDOW *local_win = newwin(SCR_H, SCR_W, SCR_Y, SCR_X);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}

//check if the terminal screen is too small to display the entire gamescreen
//and display a prompt
void checkScreenSize()
{
    int x,y;
    int flag;
    initscr();
    if(y < 32 || x < 128)
        flag = 1;
    while (flag)
    {
        wmove(stdscr, 1, 1);
        getmaxyx(stdscr, y,x);
        mvwprintw(stdscr, 1, 1, "WINDOW IS TOO SMALL MIN 32x128 (%d x %d)", y, x);
        if(y > 32 && x > 128)
            {
                flag = 0;
                endwin();
            }
        refresh();
    
    }   

}

#include <ncurses.h>
#include "drawing.h"

WINDOW* create_window(int SCR_H, int SCR_W, int SCR_Y, int SCR_X)
{
    WINDOW *local_win = newwin(SCR_H, SCR_W, SCR_Y, SCR_X);
    box(local_win, 0, 0);
    wrefresh(local_win);

    return local_win;
}
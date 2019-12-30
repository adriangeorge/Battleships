#include <ncurses.h>
#include "color_pairs.h"

void color_init()
{
    //enable colors in terminal
    start_color();

    //color pair definitions
    init_pair(BACKGROUND_COLOR, COLOR_BLACK,COLOR_WHITE);
    init_pair(MENU_BUTTONS,     COLOR_WHITE,COLOR_BLUE);
    init_pair(SELECTED_TEXT,    COLOR_RED,COLOR_BLUE);
    init_pair(GAMEGRID_BLUE,    COLOR_BLACK,COLOR_BLUE);
    init_pair(GAMEGRID_CYAN,    COLOR_BLACK,COLOR_CYAN);
    init_pair(INVENTORY,        COLOR_BLACK,COLOR_RED);
    init_pair(TITLE_BOX,        COLOR_WHITE,COLOR_CYAN);
    init_pair(SHIP_DRAW,        COLOR_WHITE,COLOR_BLUE);
    init_pair(PLACE_VALID,      COLOR_WHITE,COLOR_GREEN);
    init_pair(PLACE_INVALID,    COLOR_WHITE,COLOR_RED);
}
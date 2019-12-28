#include <ncurses.h>
#include "color_pairs.h"

void color_init()
{
    start_color();
    use_default_colors();
    init_pair(BACKGROUND_COLOR, COLOR_WHITE,COLOR_WHITE);
    init_pair(MENU_BUTTONS,     COLOR_WHITE,COLOR_BLUE);
    init_pair(SELECTED_TEXT,    COLOR_RED,COLOR_BLUE);
    init_pair(GAMEGRID_BLUE,    COLOR_BLACK,COLOR_BLUE);
    init_pair(GAMEGRID_CYAN,    COLOR_BLACK,COLOR_CYAN);
    init_pair(INVENTORY,        COLOR_BLACK,COLOR_RED);
    init_pair(TITLE_BOX,        COLOR_WHITE,COLOR_CYAN);
    init_pair(SHIP_DRAW,        COLOR_WHITE,COLOR_BLUE);
}
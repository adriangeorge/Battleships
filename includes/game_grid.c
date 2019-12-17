#include <ncurses.h>
#include "ships.h"
#include "drawing.h"
#include "game_grid.h"


typedef struct inv
{
    int shipTypesDeployed[4];
    int shipTypesDestroyed[4];
}inv;

void draw_game_grid(WINDOW** game_maps)
{
    start_color();
    init_pair(1, COLOR_BLACK,COLOR_BLUE);
    game_maps[0] = create_window(22, 32, 2, 28);
    game_maps[1] = create_window(22, 32, 2, 67);
    box(game_maps[0],0,0);
    box(game_maps[1],0,0);
    wbkgd(game_maps[0],COLOR_PAIR(1));
    wbkgd(game_maps[1],COLOR_PAIR(1));
    mvwprintw(game_maps[0],0, 13 , "GEORGE");
    mvwprintw(game_maps[1],0, 7 , "COMPUTER PLAYER");

    int i;
    for(i = 0 ; i < 2 ; i++)
        wrefresh(game_maps[i]);
    refresh();
}


void draw_inventory(WINDOW** inventory)
{
    start_color();
    init_pair(3, COLOR_BLACK,COLOR_RED);
    inventory[0] = create_window(26, 22, 2, 3);
    inventory[1] = create_window(26, 22, 2, 102);
    int i;
    for(i = 0; i<2; i++)
    {
        box(inventory[i],0,0);
        wbkgd(inventory[i],COLOR_PAIR(3)); 
        wrefresh(inventory[i]);
    }
}



int validity_check()
{

}

void computer_placement()
{

}
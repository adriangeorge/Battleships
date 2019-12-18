#include <ncurses.h>
#include "drawing.h"
#include "ships.h"
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
    init_pair(5, COLOR_BLACK,COLOR_CYAN);
    game_maps[0] = create_window(22, 32, 2, 28);
    game_maps[1] = create_window(22, 32, 2, 67);
    box(game_maps[0],0,0);
    box(game_maps[1],0,0);
    wbkgd(game_maps[0],COLOR_PAIR(1));
    wbkgd(game_maps[1],COLOR_PAIR(1));
    int x,y;
    int flag = 0;
    for(y = 1; y < 21; y++)
    {
        for(x = 1; x < 31; x++)
        {     
            if(flag)
            {
                wattron(game_maps[0], COLOR_PAIR(5));
                mvwprintw(game_maps[0], y , x, " ");
                wattroff(game_maps[0], COLOR_PAIR(5));
            }
            else
                mvwprintw(game_maps[0], y , x , " ");

            if(x % 3 == 0)
                flag = !flag;
        }    
        if(y % 2 == 0)
            flag = !flag;      
    }
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

void ship_placement(WINDOW** game_maps, ship selectedShip)
{
    int keyPRESS;
    draw_ship(game_maps[0], selectedShip);
    int orientFactor_h, orientFactor_v;

   

    while(1)
    {
         if(selectedShip.orientation == 1)
        {
            orientFactor_h = selectedShip.modules * 3; 
            orientFactor_v = 2;
        }
        else
        {
            orientFactor_h = 3;
            orientFactor_v = selectedShip.modules * 2;
        }

        keyPRESS = getch();
        switch (keyPRESS)
        {
        case KEY_UP:
            if(selectedShip.Y > 2)
                selectedShip.Y -= 2;
            else
            {
                selectedShip.Y = 1;
            }
            break;
        case KEY_DOWN:
            if(selectedShip.Y + orientFactor_v < getmaxy(game_maps[0]) - 2)
                selectedShip.Y += 2;
            else
                selectedShip.Y = getmaxy(game_maps[0]) - 1 - orientFactor_v;
            break;
        case KEY_RIGHT:
            if(selectedShip.X + orientFactor_h < getmaxx(game_maps[0]) - 2)
                selectedShip.X+= 3;
            else
                selectedShip.X = getmaxx(game_maps[0]) - 1 - orientFactor_h;
            break;
        case KEY_LEFT:
            if(selectedShip.X > 2)
                selectedShip.X-= 3;
            else
                selectedShip.X = 1;
            break;
        case ' ':
            {
                if(selectedShip.orientation == 1)
                    selectedShip.orientation = 2;
                else
                    selectedShip.orientation = 1;
            }
            break;
            
        }
        draw_game_grid(game_maps);
        draw_ship(game_maps[0], selectedShip);
    }

      
        
}

int validity_check()
{

}

void computer_placement()
{

}
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ships.h"

void init_ships(ship* ships)
{
    //ship index interval 0-9 belongs to player
    //ship index interval 10-19 belongs to computer
    int i;
    for(i = 0 ; i < 10; i++)
    {
        ships[i].Y = 1;
        ships[i].X = 1;
        if(i < 4)
            ships[i].modules = 1;
        else if(i < 7 && i >= 4)
            ships[i].modules = 2;
        else if(i < 9 && i >= 7)
            ships[i].modules = 3;
        else if(i == 9)
            ships[i].modules = 4;

        ships[i].orientation = 1;
    }

}
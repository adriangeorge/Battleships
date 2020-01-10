#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __SHIPS__
#define __SHIPS__
#include "ships.h"
#endif

void init_ships(ship* ships)
{
    //ship index interval 0-9 belongs to player
    //ship index interval 10-19 belongs to computer
    int i,j;
    for(i = 0 ; i < 10; i++)
    {
        ships[i].Y = 1;
        ships[i].X = 1;

        
        if(i < 4)
            ships[i].size = 1;
        else if(i < 7 && i >= 4)
            ships[i].size = 2;
        else if(i < 9 && i >= 7)
            ships[i].size = 3;
        else if(i == 9)
            ships[i].size = 4;

        ships[i].orientation = 1;

        for(j = 0;j <= 4; j++)
        {
            ships[i].hitModules[j] = 0;
        }
        for(j = 0;j < ships[i].size; j++)
        {
            ships[i].hitModules[j] = 'O';
        }
    }
}

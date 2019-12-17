#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ships.h"


void draw_ship(WINDOW* PARENT, struct ship SHIP)
{
/*
    SHIP.Y = Y;
    SHIP.X = X;
    SHIP.orientation = ORIENTATION ;
    SHIP.modules = MODULES;
*/
    FILE *shipModel;
    char shipModel_path[18];
    char line[100];
    int i;
    sprintf(shipModel_path,"./res/ships/%d.%d", SHIP.modules, SHIP.orientation);
    shipModel = fopen(shipModel_path, "r");

    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    if(shipModel == NULL)
        mvwprintw(PARENT, 1,1, "ERROR READING FILE");
    else
    {
        i = 0;
        while(fgets(line , 100 , shipModel))
        {
            wattron(PARENT, COLOR_PAIR(4));
            strtok(line, "\n");
            mvwprintw(PARENT, SHIP.Y + i, SHIP.X , line);
            wattroff(PARENT, COLOR_PAIR(4));
            i++;
        }
        
    }
    
    
    wrefresh(PARENT);
}
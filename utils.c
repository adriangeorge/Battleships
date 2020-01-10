#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef __MAGIC__
#define __MAGIC__
#include "magic_numbers.h"
#endif

#ifndef __COLOR__
#define __COLOR__
#include "color_pairs.h"
#endif

#ifndef __SHIPS__
#define __SHIPS__
#include "ships.h"
#endif

#ifndef __DRAW__
#define __DRAW__
#include "draw.h"
#endif

#ifndef __UTILS__
#define __UTILS__
#include "utils.h"
#endif

//stores all ship data in a file
void file_storage(ship* ships, char* filename)
{
    FILE *shipCONFIG;
    int i;
    shipCONFIG = fopen(filename, "w+");
    if(shipCONFIG == NULL)
        mvprintw(1 ,1 ,"File could not be opened");
    else
    {
        for(i = 0 ; i < 10; i++)
        {
            fprintf(shipCONFIG, "%d %d %d %d %s\n", ships[i].Y, ships[i].X , ships[i].size, ships[i].orientation, ships[i].hitModules);
        }
        fprintf(shipCONFIG, "\n");
    }
    
    
    fclose(shipCONFIG);
}

void random_placement(WINDOW* game_map, ship* SHIP, int* deployedCount)
{
    
    __time_t t;
    srand((unsigned) time(&t));
    int mapArray[15][15] = {0};
    int y;
    int x;
    int i,j;
    int validPlacement;

    for(i = 9; i >= 0 ; i--)
    {   
        
        if(i < 4)
        {
            deployedCount[0]++;
        }
        if(i < 7 && i >= 4)
        {
            deployedCount[1]++;
        }
        if(i < 9 && i >= 7)
        {
            deployedCount[2]++;
        }
        if(i == 9)
        {    
            deployedCount[3]++;
        }

        validPlacement = 0;

        //initialising coords
        //generating random number in range
        //using formula : (rand() % (upper - lower + 1)) + lower;
        y = (rand() % 10 - 0 + 1) + 0;
        x = (rand() % 10 - 0 + 1) + 0;

       
        //Search for a suitable placement position until one is found
        while(!validPlacement)
                {
                    y = (rand() % 10 - 0 + 1) + 0;
                    x = (rand() % 10 - 0 + 1) + 0;
                    SHIP[i].orientation = y % 2 + 1;
                    for(j = 0 ; j <= SHIP[i].size; j++)
                    {
                        if(SHIP[i].orientation == 1)
                        {
                            if(mapArray[y][x + j] == 0 && x + SHIP[i].size < 12)
                                validPlacement = 1;
                            else
                            {
                                validPlacement = 0;
                                break;
                            }
                        }
                        else
                        {
                            if(mapArray[y + j][x] == 0 && y + SHIP[i].size < 12)
                                validPlacement = 1;
                            else
                            {
                                validPlacement = 0;
                                break;
                            }
                        }
                    }
                }
        
        
        
        //mamarking all adjacent positions with either 1 (for ship body)
        //or 2 (for surrounding squares)or 2 (for surrounding squares)
        if(SHIP[i].orientation == 1)
        {
            //FOR HORIZONTAL ORIENTATION
            for(j = 0; j < SHIP[i].size ; j++)
                {
                    mapArray[y][x + j] = 1;
                    if(mapArray[y - 1][x + j] != 1)
                        mapArray[y - 1][x + j] = 2;
                    if(mapArray[y + 1][x + j] != 1)
                        mapArray[y + 1][x + j] = 2;
                }
            
            if(mapArray[y - 1][x - 1] != 1)
                mapArray[y - 1][x - 1] = 2;
            if(mapArray[y][x - 1] != 1)
                mapArray[y][x - 1] = 2;
            if(mapArray[y + 1][x - 1] != 1)
                mapArray[y + 1][x - 1] = 2;
            
            if(mapArray[y - 1][x + SHIP[i].size] != 1)
                mapArray[y - 1][x + SHIP[i].size] = 2;
            if(mapArray[y][x + SHIP[i].size] != 1)
                mapArray[y][x + SHIP[i].size] = 2;
            if(mapArray[y + 1][x + SHIP[i].size] != 1)
                mapArray[y + 1][x + SHIP[i].size] = 2;
        }
        else
        {
            //FOR VERTICAL ORIENTATION
            for(j = 0; j < SHIP[i].size ; j++)
                {
                    
                    mapArray[y + j][x] = 1;
                    if(mapArray[y + j][x - 1] != 1)
                        mapArray[y + j][x - 1] = 2;
                    if(mapArray[y + j][x + 1] != 1)
                        mapArray[y + j][x + 1] = 2;

                }

            if(mapArray[y - 1][x - 1] != 1)
                mapArray[y - 1][x - 1] = 2;
            if(mapArray[y - 1][x] != 1)
                mapArray[y - 1][x] = 2;
            if(mapArray[y - 1][x + 1] != 1)
                mapArray[y - 1][x + 1] = 2;
            
            if(mapArray[y + SHIP[i].size][x - 1] != 1)
                mapArray[y + SHIP[i].size][x - 1] = 2;
            if(mapArray[y + SHIP[i].size][x] != 1)
                mapArray[y + SHIP[i].size][x] = 2;
            if(mapArray[y + SHIP[i].size][x + 1] != 1)
                mapArray[y + SHIP[i].size][x + 1] = 2;
        }

        SHIP[i].Y = y * cellHeight - 1;
        SHIP[i].X = x * cellWidth - 2;


        wattron(game_map, COLOR_PAIR(PLACE_INVALID));
        draw_ship(game_map, y * cellHeight - 1 , x * cellWidth - 2, SHIP[i].size, SHIP[i].orientation, SHIP_DRAW );        
        wattroff(game_map, COLOR_PAIR(PLACE_INVALID));

        wrefresh(game_map);
    }

    //DEBUG-ONLY
    //SHOW MATRIX FOR PLACEMENT
    // for(i = 1; i <= 10; i++)
    //         for(j = 1; j <= 10; j++)
    //         {
    //             if(mapArray[i][j] == 2) {attron(COLOR_PAIR(PLACE_INVALID));}
    //             if(mapArray[i][j] == 1) {attron(COLOR_PAIR(PLACE_VALID));}
    //             mvprintw(i, j , "%d", mapArray[i][j]);
    //             attroff(COLOR_PAIR(PLACE_INVALID));
    //             attroff(COLOR_PAIR(PLACE_VALID));
    //         }   
}

void readships(ship* ships, char* filename )
{
    FILE *shipCONFIG;
    int i;
    shipCONFIG = fopen(filename, "r");
    if(shipCONFIG == NULL)
        mvprintw( 1,1, "ERROR READING FILE");

    for(i = 0 ; i < 10; i++)
    {
        fscanf(shipCONFIG, "%d %d %d %d %s\n", &ships[i].Y, &ships[i].X , &ships[i].size, &ships[i].orientation, ships[i].hitModules);
    }
    fclose(shipCONFIG);
}

void generate_shipArray(ship* ships, int array[10][10])
{
    int i,j;
    for(i = 0; i < 10; i++)
    {
        if(ships[i].orientation == 1)
            for(j = 0; j < ships[i].size; j++)
            {
                array[ships[i].Y/cellHeight][(ships[i].X/cellWidth) + j] = 1;
            }
        else
            for(j = 0; j < ships[i].size; j++)
            {
                array[ships[i].Y/cellHeight + j][ships[i].X/cellWidth ] = 1;
            }
        
    }

}
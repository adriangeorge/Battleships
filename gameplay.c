#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef __SHIPS__
#define __SHIPS__
#include "ships.h"
#endif

#ifndef __DRAW__
#define __DRAW__
#include "draw.h"
#endif

#ifndef __MAGIC__
#define __MAGIC__
#include "magic_numbers.h"
#endif

#ifndef __COLOR__
#define __COLOR__
#include "color_pairs.h"
#endif

#ifndef __UTILS__
#define __UTILS__
#include "utils.h"
#endif

#ifndef __GAMEPLAY__
#define __GAMEPLAY__
#include "gameplay.h"
#endif

#define Y_MTRX (y - 1 )/cellHeight
#define X_MTRX (x - 1 )/cellWidth

int gameplay(int *GAMESTATE, WINDOW** game_maps, WINDOW* background, char* map)
{
    ship playerShips[10];
    ship computerShips[10];
    int playerARRAY[10][10] = {0};
    int computerARRAY[10][10] = {0};

    int deployedCount[2][4] = {{4,3,2,1} , {4,3,2,1}};
    int i,j;
    int y;
    int x;
    int playerHits = 0;
    int computerHits = 0;

    int turn;

    x = 1;
    y = 1;
    
    //drawing all the needed boxes
    draw_background(background);
    game_maps[0] = create_window(22, 32, 2, 28, GAMEGRID_BLUE);
    game_maps[1] = create_window(22, 32, 2, 28 + 40 , GAMEGRID_BLUE);
    draw_game_grid(game_maps[0]);
    draw_game_grid(game_maps[1]);
    
    
    WINDOW* placementStatus;
    placementStatus = create_window(3, 20, 24 , 28 , BACKGROUND_COLOR);
    box(placementStatus, 0 , 0);
    mvwprintw(placementStatus, 0, 1 , "Status");
    wrefresh(placementStatus);

    //reading ship file either the one provided by the user or the one generated randomly
    readships(playerShips, map);
    readships(computerShips, "computerMAP");
    
    //generating the ship array 
    generate_shipArray(playerShips, playerARRAY);
    generate_shipArray(computerShips, computerARRAY);


    int keyPRESS;
    turn = 1;
    while(1)
    {
        draw_game_grid(game_maps[0]);
        draw_game_grid(game_maps[1]);
        

        for(i = 0 ; i < 10 ; i++)
            {
                //draws all the player's ships 
                draw_ship(game_maps[0], playerShips[i].Y, playerShips[i].X, playerShips[i].size, playerShips[i].orientation, SHIP_DRAW);
                //interpret the array map ( 2 = hit ship piece ; 3 = hit water)
                for(j = 0 ; j < 10; j++)
                {
                    if(computerARRAY[i][j] == 2)
                    {
                        draw_hit(1 + i * cellHeight  , 1 + j * cellWidth ,game_maps[1]);
                    }      
                    if(computerARRAY[i][j] == 3)
                    {
                        draw_splash(1 + i * cellHeight  , 1 + j * cellWidth ,game_maps[1]);
                    }    
                }
                for(j = 0 ; j < 10; j++)
                {
                    if(playerARRAY[i][j] == 2)
                    {
                        draw_hit(1 + i * cellHeight  , 1 + j * cellWidth ,game_maps[0]);
                    }      
                    if(playerARRAY[i][j] == 3)
                    {
                        draw_splash(1 + i * cellHeight  , 1 + j * cellWidth ,game_maps[0]);
                    }    
                }
            }
        
        //check for win condition , if all the pieces are hit end the game
        if(playerHits == 20)
            {
                mvwprintw(placementStatus, 1,1 , "                  ");
                mvwprintw(placementStatus, 1,1 , "You Win! Game End!");
                wrefresh(placementStatus);
                timeout(0);
                winner();
                sleep(5);

                *GAMESTATE = 1;
                return *GAMESTATE;
            }
        if(computerHits == 20)
            {
                mvwprintw(placementStatus, 1,1 , "                  ");
                mvwprintw(placementStatus, 1,1 , "Lost! Game End!");
                wrefresh(placementStatus);
                timeout(0);
                
                *GAMESTATE = 1;
                return *GAMESTATE;
            }
        
        draw_select(y, x , game_maps[1]);
        wrefresh(game_maps[1]);
        wrefresh(game_maps[0]);
        wrefresh(placementStatus);

        if(turn == 1)
        {
            keyPRESS = getch();
            switch (keyPRESS)
                {
                    case 10:
                        if(computerARRAY[Y_MTRX][X_MTRX] == 1)
                            {
                                computerARRAY[Y_MTRX][X_MTRX] = 2;
                                playerHits++;
                                mvwprintw(placementStatus, 1,1 , "                  ");
                                mvwprintw(placementStatus, 1,1 , "Enemy Ship Hit!");
                            }
                        else if(computerARRAY[Y_MTRX][X_MTRX] == 0)
                            {
                                computerARRAY[Y_MTRX][X_MTRX] = 3;
                                mvwprintw(placementStatus, 1,1 , "                  ");
                                mvwprintw(placementStatus, 1,1 , "Shot missed!");
                                turn = 0;
                            }
                        else if(computerARRAY[Y_MTRX][X_MTRX] == 2 || computerARRAY[Y_MTRX][X_MTRX] == 3)
                        {
                            mvwprintw(placementStatus, 1,1 , "                  ");
                            mvwprintw(placementStatus, 1,1 , "Already shot there");
                        }
                        
                    break;
                    case KEY_UP:
                        
                        if(y > cellHeight)
                            y -= 2;
                        else
                            y = 1;
                        break;
                    case KEY_DOWN:
                        if(y < cellHeight * 9)
                                y += 2;
                            else
                                y = cellHeight * 9 + 1;
                        break;
                    case KEY_RIGHT:
                        if(x + cellWidth < getmaxx(game_maps[1]) - cellWidth)
                                x += 3;
                            else
                                x = getmaxx(game_maps[1]) - 1 - cellWidth;
                        break;
                    case KEY_LEFT:
                        if(x > cellWidth)
                            x -= 3;
                        else
                            x = 1;
                        break;
                }
        }
        if(turn == 0)
            {
                computerTurn(playerARRAY, &turn, &computerHits);
            }
    }
    
}

int computerTurn(int array[10][10] , int* turn, int* counter)
{
    __time_t t;
    srand((unsigned) time(&t));
    int x, y;
    
    y = (rand() % 10 - 0 + 1) + 0;
    x = (rand() % 10 - 0 + 1) + 0;

    //check if this place hasn't been hit already
    while(array[y][x] == 2 || array[y][x] == 3 )
    {
        y = (rand() % 10 - 0 + 1) + 0;
        x = (rand() % 10 - 0 + 1) + 0;
    }

    // if the bot hits a player's piece it can pick another square randomly
    if(array[y][x] == 1)
        {
            array[y][x] = 2;
            counter++;
            *turn = 0;
        }
    if(array[y][x] == 0)
        {
            array[y][x] = 3;
            *turn = 1;
        }

}
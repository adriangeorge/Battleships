#include <ncurses.h>
#include "ships.h"
#include "draw.h"
#include "color_pairs.h"
#include "placement.h"

void placement(int* GAMESTATE, WINDOW** game_maps, WINDOW** inventory)
{
    //ship index interval 0-9 belongs to player
    //ship index interval 10-19 belongs to computer
    ship ships[20];
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
    start_color();
    
    inventory[0] = create_window(25, 21, 2, 3, INVENTORY);
    inventory[1] = create_window(25, 21, 2, 103, INVENTORY);
    
    
    int deployedCount[2][4] = {{0,0,0,0} , {0,0,0,0}};
    
    for(i = 4; i > 0; i--)
    {
        mvwprintw(inventory[0], 3 + (2 + 2) * (4 - i) , 2, "DEPL");
        mvwprintw(inventory[0], 2 + (2 + 2) * (4 - i) , 2, "%d" , deployedCount[0][i - 1]);
        draw_ship(inventory[0], 2 + (2 + 2) * (4 - i) , 7, i , 1);
        
        mvwprintw(inventory[1], 3 + (2 + 2) * (4 - i) , 2, "DEPL");
        mvwprintw(inventory[1], 2 + (2 + 2) * (4 - i) , 2, "%d" , deployedCount[1][i - 1]);
        draw_ship(inventory[1], 2 + (2 + 2) * (4 - i) , 7, i , 1);
    }
    draw_inventory(inventory[0]);
    draw_inventory(inventory[1]);
    wrefresh(inventory[0]);
    wrefresh(inventory[1]);

    game_maps[0] = create_window(22, 32, 2, 28, GAMEGRID_BLUE);
    game_maps[1] = create_window(22, 32, 2, 68, GAMEGRID_BLUE);
    draw_game_grid(game_maps[0]);
    mvwprintw(game_maps[0], 0, 13 , "GEORGE" );
    draw_game_grid(game_maps[1]);
    mvwprintw(game_maps[1], 0, 12 , "COMPUTER" );
    wrefresh(game_maps[0]);
    wrefresh(game_maps[1]);

    int sCount;
    int gameMapCounter;
    int keyPRESS;
    int orientFactor_h, orientFactor_v;
    int player;

    //0 for human player
    //1 for computer player
    player = 0;

    for(sCount = 0; sCount < 10; sCount++)
    {
        keyPRESS = KEY_RIGHT;
        while(keyPRESS != 10)
        {
            //drawing the game grid
            //and every ship that was previously placed
            draw_game_grid(game_maps[0]);
            for(i = 0 ; i < sCount; i++ )
                draw_ship(game_maps[0], ships[i].Y, ships[i].X, ships[i].modules, ships[i].orientation);
            
            //drawing the current position of active ship
            draw_ship(game_maps[0],ships[sCount].Y,ships[sCount].X,ships[sCount].modules,ships[sCount].orientation);
            
            //refresh so changes are displayed on screen
            wrefresh(game_maps[0]);



            //getting the next key press
            keyPRESS = getch();

            //accounting for ship rotation
            if(ships[sCount].orientation == 1)
            {
                orientFactor_h = ships[sCount].modules * 3; 
                orientFactor_v = 2;
            }
            else
            {
                orientFactor_h = 3;
                orientFactor_v = ships[sCount].modules * 2;
            }

            switch (keyPRESS)
            {
            case KEY_UP:
                if(ships[sCount].Y > 2)
                    ships[sCount].Y -= 2;
                else
                {
                    ships[sCount].Y = 1;
                }
                break;
            case KEY_DOWN:
                if(ships[sCount].Y + orientFactor_v < getmaxy(game_maps[0]) - 2)
                    ships[sCount].Y += 2;
                else
                    ships[sCount].Y = getmaxy(game_maps[0]) - 1 - orientFactor_v;
                break;
            case KEY_RIGHT:
                if(ships[sCount].X + orientFactor_h < getmaxx(game_maps[0]) - 2)
                    ships[sCount].X+= 3;
                else
                    ships[sCount].X = getmaxx(game_maps[0]) - 1 - orientFactor_h;
                break;
            case KEY_LEFT:
                if(ships[sCount].X > 2)
                    ships[sCount].X-= 3;
                else
                    ships[sCount].X = 1;
                break;
            case ' ':
                if(ships[sCount].orientation == 1)
                    ships[sCount].orientation = 2;
                else
                    ships[sCount].orientation = 1;
                break;   
            }
            validity_check(game_maps[0], ships[sCount]);
        }
        if(sCount < 4)
            deployedCount[0][0]++;
        else if(sCount < 7 && sCount >= 4)
            deployedCount[0][1]++;
        else if(sCount < 9 && sCount >= 7)
            deployedCount[0][2]++;
        else if(sCount == 9)
            deployedCount[0][3]++;

        for(i = 4; i > 0; i--)
        {
            mvwprintw(inventory[0], 3 + (2 + 2) * (4 - i) , 2, "DEPL");
            mvwprintw(inventory[0], 2 + (2 + 2) * (4 - i) , 2, "%d" , deployedCount[0][i - 1]);
            draw_ship(inventory[0], 2 + (2 + 2) * (4 - i) , 7, i , 1);
            
            mvwprintw(inventory[1], 3 + (2 + 2) * (4 - i) , 2, "DEPL");
            mvwprintw(inventory[1], 2 + (2 + 2) * (4 - i) , 2, "%d" , deployedCount[1][i - 1]);
            draw_ship(inventory[1], 2 + (2 + 2) * (4 - i) , 7, i , 1);
        }

        wrefresh(inventory[0]);
        wrefresh(inventory[1]);

            
    }
}

void computer_placement()
{

}

int validity_check(WINDOW* game_map, ship currentShip)
{
    int flag = 1;
    int validBoxHeight;
    int validBoxWidth;

    if(currentShip.orientation == 1)
    {
        validBoxHeight = 2;
        validBoxWidth = currentShip.modules + 3;
    }
    else
    {
        validBoxHeight = currentShip.modules + 2;
        validBoxWidth = 3;
    }

    int startingX;
    int startingY;

    startingX = currentShip.X - 1;
    startingY = currentShip.Y - 1;

    int i,j;
    int checkedBox;
    int getChar;
    for(i = 0; i <= validBoxWidth; i++)
    {
        getChar = mvwinch(game_map, startingY , startingX + i) & A_CHARTEXT;
        mvprintw(1, i+ 1, "%c", getChar);
    }    
}
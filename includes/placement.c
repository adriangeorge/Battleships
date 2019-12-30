#include <ncurses.h>
#include "ships.h"
#include "draw.h"
#include "magic_numbers.h"
#include "color_pairs.h"
#include "placement.h"

void placement(int* GAMESTATE, WINDOW** game_maps, WINDOW** inventory)
{

    ship ships[10];
    init_ships(ships);

    inventory[0] = create_window(25, 21, 2, 3, INVENTORY);
    inventory[1] = create_window(25, 21, 2, 103, INVENTORY);
    
    
    int deployedCount[2][4] = {{0,0,0,0} , {0,0,0,0}};
    int shipCounter;
    int gameMapCounter;
    int keyPRESS;
    int orientFactor_h, orientFactor_v;

    WINDOW* placementStatus;
    placementStatus = create_window(3, 20, 24 , 28 , BACKGROUND_COLOR);
    box(placementStatus, 0 , 0);
    mvwprintw(placementStatus, 0, 1 , "Status");
    wrefresh(placementStatus);

    int validFlag;
    int i,j;
    for(shipCounter = 0; shipCounter < 10; shipCounter++)
    {
        keyPRESS = 0;
        while(keyPRESS != 10)
        {
            draw_map_and_inventory(deployedCount,game_maps,inventory);
            validFlag = 1;
            //drawing the game grid
            //and every ship that was previously placed
            draw_game_grid(game_maps[0]);
            
            for(i = 0 ; i < shipCounter; i++ )
            {
                draw_ship(game_maps[0], ships[i].Y, ships[i].X, ships[i].modules, ships[i].orientation, SHIP_DRAW);
                if(ships[i].Y == ships[shipCounter].Y && ships[i].X == ships[shipCounter].X)
                    validFlag = 0;
            }
            if(validFlag)
                validFlag = validity_check(game_maps[0], ships[shipCounter]);

            draw_ship(game_maps[0], ships[shipCounter].Y, ships[shipCounter].X, ships[shipCounter].modules, ships[shipCounter].orientation, SHIP_DRAW);
            
            wrefresh(game_maps[0]); 

            keyPRESS = getch();
            if(keyPRESS == 10 && !validFlag)
            {
                mvwprintw(placementStatus, 1 ,1 , "Invalid Placement!");
                keyPRESS = 0;
                wrefresh(placementStatus);
            }
            else if(keyPRESS == 10 && validFlag)
            {
                //only redraw status window in this case because "Invalid Placement!" is longer
                //than "Ship Deployed!" and characters will remain
                werase(placementStatus);
                box(placementStatus, 0,0);
                mvwprintw(placementStatus, 0, 1 , "Status");
                mvwprintw(placementStatus, 1 ,1 , "Ship Deployed!");
                wrefresh(placementStatus);
            }

            switch (keyPRESS)
                {
                case KEY_UP:
                    if(ships[shipCounter].Y > 2)
                        ships[shipCounter].Y -= 2;
                    else
                    {
                        ships[shipCounter].Y = 1;
                    }
                    break;
                case KEY_DOWN:
                    if(ships[shipCounter].Y + orientFactor_v < getmaxy(game_maps[0]) - 2)
                        ships[shipCounter].Y += 2;
                    else
                        ships[shipCounter].Y = getmaxy(game_maps[0]) - 1 - orientFactor_v;
                    break;
                case KEY_RIGHT:
                    if(ships[shipCounter].X + orientFactor_h < getmaxx(game_maps[0]) - 2)
                        ships[shipCounter].X+= 3;
                    else
                        ships[shipCounter].X = getmaxx(game_maps[0]) - 1 - orientFactor_h;
                    break;
                case KEY_LEFT:
                    if(ships[shipCounter].X > 2)
                        ships[shipCounter].X-= 3;
                    else
                        ships[shipCounter].X = 1;
                    break;
                case ' ':
                    if(ships[shipCounter].orientation == 1)
                        ships[shipCounter].orientation = 2;
                    else
                        ships[shipCounter].orientation = 1;
                    break;
            }

            //accounting for ship rotation
            if(ships[shipCounter].orientation == 1)
            {
                orientFactor_h = ships[shipCounter].modules * 3; 
                orientFactor_v = 2;
            }
            else
            {
                orientFactor_h = 3;
                orientFactor_v = ships[shipCounter].modules * 2;
            }
        
        }

        //count how many of each ships was deployed by the player
        if(shipCounter < 4)
            deployedCount[0][0]++;
        else if(shipCounter < 7 && shipCounter >= 4)
            deployedCount[0][1]++;
        else if(shipCounter < 9 && shipCounter >= 7)
            deployedCount[0][2]++;
        else if(shipCounter == 9)
            deployedCount[0][3]++;

        for(j = 0; j < 2; j++)
            {
                for(i = 4; i > 0; i--)
                {
                    mvwprintw(inventory[j], 3 + (2 + 2) * (4 - i) , 2, "DEPL");
                    mvwprintw(inventory[j], 2 + (2 + 2) * (4 - i) , 2, "%d" , deployedCount[j][i - j]);
                    draw_ship(inventory[j], 2 + (2 + 2) * (4 - i) , 7, i , 1, INVENTORY);
                }
                wrefresh(inventory[j]);
            }
    }
    *GAMESTATE = 3;

}

void computer_placement()
{

}

//stores all ships in a file
void file_storage()
{

}

int validity_check(WINDOW* game_map, ship currentShip)
{
    int flag = 1;
    int validBoxHeight;
    int validBoxWidth;

    if(currentShip.orientation == 1)
    {
        validBoxHeight = cellHeight * 2;
        validBoxWidth =  (currentShip.modules + 1) * cellWidth;
    }
    else
    {
        validBoxHeight = (currentShip.modules + 1) * cellHeight;
        validBoxWidth = cellWidth * 2;
    }

    int startingY;
    int startingX;  

    //moving starting x and y of box 
    startingY = currentShip.Y - 2;
    startingX = currentShip.X - 2;

    int i;
    int getChar;

    //defining variables for all sides and corners of the box
    int top = 1;
    int bot = 1;
    int left = 1;
    int right = 1;
    int tl = 1;
    int tr = 1;
    int bl = 1;
    int br = 1;

    //checking top side of validBox
    for(i = cellWidth; i < validBoxWidth; i += 3)
    {
        if(startingY > 0)
        {
            getChar = mvwinch(game_map, startingY , startingX + i) & A_CHARTEXT;
            if(getChar != 32)
                {
                    wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                    mvwprintw(game_map, startingY, startingX + i, "x", getChar);
                    wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                    top = 0;
                } 
        }
    }

    //checking bottom of validBox
    for(i = cellWidth; i < validBoxWidth; i += 3)
    {
        if(startingY + validBoxHeight < getmaxy(game_map) - 1)
        {
            getChar = mvwinch(game_map, startingY + validBoxHeight, startingX + i) & A_CHARTEXT;
            if(getChar != 32)
                {
                    wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                    mvwprintw(game_map, startingY + validBoxHeight, startingX + i, "x", getChar);
                    wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                    bot = 0;
                }
        }
    }  
    
    //checking left edge of validBox
    for(i = cellHeight; i < validBoxHeight; i += 2)
    {
        if(startingX > 0)
        {
            getChar = mvwinch(game_map, startingY + i, startingX) & A_CHARTEXT;
            if(getChar != 32)
                {
                    wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                    mvwprintw(game_map, startingY + i, startingX , "x", getChar);
                    wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                    left = 0;
                }
        }
    }

    //checking right edge of validBox
    for(i = cellHeight; i < validBoxHeight; i += 2)
    {
        if(startingX + validBoxWidth < getmaxx(game_map) - 1)
        {
            getChar = mvwinch(game_map, startingY + i, startingX + validBoxWidth) & A_CHARTEXT;
            if(getChar != 32)
            {
                wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                mvwprintw(game_map, startingY + i, startingX + validBoxWidth, "x", getChar);
                wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                right = 0;
            }
        }
    }
    
    //check corners
    tl = mvwinch(game_map, startingY , startingX ) & A_CHARTEXT;
    tr = mvwinch(game_map, startingY , startingX + validBoxWidth) & A_CHARTEXT;
    bl = mvwinch(game_map, startingY + validBoxHeight , startingX ) & A_CHARTEXT;
    br = mvwinch(game_map, startingY + validBoxHeight , startingX + validBoxWidth) & A_CHARTEXT;

    if((startingY > 0) && (startingX > 0))
    {
        if(tl != 32)
            {
                wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                mvwprintw(game_map, startingY , startingX , "x");
                wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                tl = 0;
            }
        
    }

    if((startingY > 0) && (startingX + validBoxWidth < getmaxx(game_map))) 
    {
        if(tr != 32)
            {
                wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                mvwprintw(game_map, startingY , startingX + validBoxWidth, "x");
                wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                tr = 0;
            }
        
    }

    if((startingY + validBoxHeight < getmaxy(game_map) - cellHeight ) && (startingX > 0)) 
    {
        if(bl != 32)
            {
                wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                mvwprintw(game_map, startingY + validBoxHeight, startingX , "x");
                wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                bl = 0;
            }
    }

    if((startingY + validBoxHeight < getmaxy(game_map) - cellHeight ) && (startingX + validBoxWidth < getmaxx(game_map))) 
    {
        if(br != 32)
            {
                wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                mvwprintw(game_map, startingY + validBoxHeight, startingX + validBoxWidth, "x");
                wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
                br = 0;
            }
    }
    

    flag = left && right && top && bot && tl && tr && bl & br;
    //mvprintw(1, 1, "                   ");
    //mvprintw(1, 1, "FLAG %d X: %2d Y: %2d", flag, currentShip.X, currentShip.Y);
    
    return flag;
}
#include <stdio.h>
#include <ncurses.h>
#include <string.h>


#ifndef __MAGIC__
#define __MAGIC__
#include "magic_numbers.h"
#endif

#ifndef __COLOR__
#define __COLOR__
#include "color_pairs.h"
#endif

#ifndef __DRAW__
#define __DRAW__
#include "draw.h"
#endif


//check if the terminal screen is too small to display the entire gamescreen
//and display a prompt
void checkScreenSize()
{
    int x,y;
    int flag;
    initscr();
    if(y < 32 || x < 128)
        flag = 1;
    while (flag)
    {
        wmove(stdscr, 1, 1);
        getmaxyx(stdscr, y,x);
        mvwprintw(stdscr, 1, 1, "WINDOW IS TOO SMALL MIN 32x128 (%d x %d)", y, x);
        if(y > 32 && x > 128)
            {
                flag = 0;
                endwin();
            }
        refresh();
    }
}

WINDOW* create_window(int SCR_H, int SCR_W, int SCR_Y, int SCR_X, int color)
{
    color_init();

    WINDOW *local_win = newwin(SCR_H, SCR_W, SCR_Y, SCR_X);
    box(local_win, 0, 0);
    wbkgd(local_win, COLOR_PAIR(color));
    wrefresh(local_win);
    return local_win;
}

void draw_background(WINDOW* bkgrd)
{
    bkgrd = create_window(MAIN_SCREEN_H, MAIN_SCREEN_W, MAIN_SCREEN_Y, MAIN_SCREEN_X, BACKGROUND_COLOR);
}

void draw_title(WINDOW* TITLE_WIN)
{
    

    TITLE_WIN = create_window(TITLE_H, TITLE_W, TITLE_Y, TITLE_X, TITLE_BOX);

    mvwprintw(TITLE_WIN, TITLE_WRITING_Y + 0, TITLE_WRITING_X,   "______  ___ _____ _____ _      _____ _____ _   _ ___________  _____ ");
    mvwprintw(TITLE_WIN, TITLE_WRITING_Y + 1, TITLE_WRITING_X,   "| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\/  ___|");
    mvwprintw(TITLE_WIN, TITLE_WRITING_Y + 2, TITLE_WRITING_X,   "| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /\\ `--. ");
    mvwprintw(TITLE_WIN, TITLE_WRITING_Y + 3, TITLE_WRITING_X,   "| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/  `--. \\");
    mvwprintw(TITLE_WIN, TITLE_WRITING_Y + 4, TITLE_WRITING_X,   "| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |    /\\__/ /");
    mvwprintw(TITLE_WIN, TITLE_WRITING_Y + 5, TITLE_WRITING_X,   "\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|    \\____/ ");

    wrefresh(TITLE_WIN);
}

void draw_buttons(WINDOW **options)
{
    int i;
    for(i = 0 ; i < OPTION_COUNT ; i++)
        {   
            options[i] = create_window(3, 20, BUTTON_Y , BUTTON_X, MENU_BUTTONS);
            wrefresh(options[i]);
        }
}


void draw_game_grid(WINDOW* game_maps)
{
    int x,y;
    int flag = 0;
    for(y = 1; y < 21; y++)
    {
        for(x = 1; x < 31; x++)
        {     
            if(flag)
            {
                wattron(game_maps, COLOR_PAIR(GAMEGRID_CYAN));
                mvwprintw(game_maps, y , x, " ");
                wattroff(game_maps, COLOR_PAIR(GAMEGRID_CYAN));
            }
            else
                mvwprintw(game_maps, y , x , " ");

            if(x % 3 == 0)
                flag = !flag;
        }    
        if(y % 2 == 0)
            flag = !flag;      
    }
    box(game_maps, 0 , 0);
}

WINDOW* draw_inventory(WINDOW* inventory, int* deployedCount)
{
    int i;
    for(i = 4; i > 0; i--)
    {
        mvwprintw(inventory, 3 + (2 + 2) * (4 - i) , 2, "DEPL");
        mvwprintw(inventory, 2 + (2 + 2) * (4 - i) , 2, "%d" , deployedCount[i - 1]);
        draw_ship(inventory, 2 + (2 + 2) * (4 - i) , 7, i , 1, INVENTORY);
    }

    wrefresh(inventory);
    
    box(inventory, 0, 0);
    mvwprintw(inventory, 0, 21/2 - 4 , "SHIPYARD");
}


void draw_ship(WINDOW* PARENT, int Y, int X, int MODULES, int ORIENTATION, int COLOR)
{
    FILE *shipModel;
    char shipModel_path[18];
    char line[100];
    int i;
    sprintf(shipModel_path,"%d.%d", MODULES, ORIENTATION);
    shipModel = fopen(shipModel_path, "r");
    if(shipModel == NULL)
        mvwprintw(PARENT, 1,1, "ERROR READING FILE");
    else
    {
        i = 0;
        while(fgets(line , 100 , shipModel))
        {
            wattron(PARENT, COLOR_PAIR(COLOR));
            strtok(line, "\n");
            mvwprintw(PARENT, Y + i, X , line);
            wattroff(PARENT, COLOR_PAIR(COLOR));
            i++;
        }
        
    }
    fclose(shipModel);
}

void draw_select(int y, int x, WINDOW* game_map)
{
    int i,j;
    char c;

    for(i = 0; i < 2; i++)
        for(j = 0; j < 3; j++)
        {
                c = mvwinch(game_map,y + i, x + j) & A_CHARTEXT;
                wattron(game_map, COLOR_PAIR(PLACE_INVALID));
                mvwprintw(game_map, y + i, x + j , "%c", c);
                wattroff(game_map, COLOR_PAIR(PLACE_INVALID));
        }
}
void draw_hit(int y, int x, WINDOW* game_map)
{
    wattron(game_map, COLOR_PAIR(SELECTED_TEXT));
    mvwprintw(game_map, y, x  , "*");
    mvwprintw(game_map, y, x + 2 , "*");
    mvwprintw(game_map, y + 1, x + 1 , "*");
    wattroff(game_map, COLOR_PAIR(SELECTED_TEXT));
    mvwprintw(game_map, y, x + 1 , "~");
    mvwprintw(game_map, y + 1, x , "~");
    mvwprintw(game_map, y + 1, x + 2 , "~");
    


}

void draw_splash(int y, int x, WINDOW* game_map)
{
    wattron(game_map, COLOR_PAIR(SHIP_DRAW));
    mvwprintw(game_map, y, x  , "~");
    mvwprintw(game_map, y, x + 1 , " ");
    mvwprintw(game_map, y, x + 2 , "~");
    mvwprintw(game_map, y + 1, x , " ");
    mvwprintw(game_map, y + 1, x + 1 , "~");
    mvwprintw(game_map, y + 1, x + 2 , " ");
    wattroff(game_map, COLOR_PAIR(SHIP_DRAW));

}

void winner()
{
    WINDOW* splash = create_window(22, 72, 2, 28 , TITLE_BOX);

    
    mvwprintw(splash, (22 - 6)/2  + 0, (72 - 40)/2,   "_    _ _____ _   _  _   _  ___________ ");
    mvwprintw(splash, (22 - 6)/2  + 1, (72 - 40)/2,   "| |  | |_   _| \\ | || \\ | ||  ___| ___ \\");
    mvwprintw(splash, (22 - 6)/2  + 2, (72 - 40)/2,   "| |  | | | | |  \\| ||  \\| || |__ | |_/ /");
    mvwprintw(splash, (22 - 6)/2  + 3, (72 - 40)/2,   "| |/\\| | | | | . ` || . ` ||  __||    /");
    mvwprintw(splash, (22 - 6)/2  + 4, (72 - 40)/2,   "\\  /\\  /_| |_| |\\  || |\\  || |___| |\\ \\ ");
    mvwprintw(splash, (22 - 6)/2  + 5, (72 - 40)/2,   " \\/  \\/ \\___/\\_| \\_/\\_| \\_/\\____/\\_| \\_|"); 
    
    wrefresh(splash);

}

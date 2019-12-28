#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "magic_numbers.h"
#include "color_pairs.h"
#include "draw.h"


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
    start_color();
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

    mvwprintw(TITLE_WIN, (TITLE_H - TITLE_TXT_LINES)/2 + 0, (TITLE_W - TITLE_TXT_COLS)/2,   "______  ___ _____ _____ _      _____ _____ _   _ ___________  _____ ");
    mvwprintw(TITLE_WIN, (TITLE_H - TITLE_TXT_LINES)/2 + 1, (TITLE_W - TITLE_TXT_COLS)/2,   "| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\/  ___|");
    mvwprintw(TITLE_WIN, (TITLE_H - TITLE_TXT_LINES)/2 + 2, (TITLE_W - TITLE_TXT_COLS)/2,   "| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /\\ `--. ");
    mvwprintw(TITLE_WIN, (TITLE_H - TITLE_TXT_LINES)/2 + 3, (TITLE_W - TITLE_TXT_COLS)/2,   "| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/  `--. \\");
    mvwprintw(TITLE_WIN, (TITLE_H - TITLE_TXT_LINES)/2 + 4, (TITLE_W - TITLE_TXT_COLS)/2,   "| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |    /\\__/ /");
    mvwprintw(TITLE_WIN, (TITLE_H - TITLE_TXT_LINES)/2 + 5, (TITLE_W - TITLE_TXT_COLS)/2,   "\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|    \\____/ ");

    wrefresh(TITLE_WIN);
}

void draw_buttons(WINDOW **options)
{
    start_color();
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
}

WINDOW* draw_inventory(WINDOW* inventory)
{
    box(inventory, 0, 0);
    mvwprintw(inventory, 0, 21/2 - 4 , "SHIPYARD");
}

void draw_ship(WINDOW* PARENT, int Y, int X, int MODULES, int ORIENTATION)
{
    FILE *shipModel;
    char shipModel_path[18];
    char line[100];
    int i;
    sprintf(shipModel_path,"./res/ships/%d.%d", MODULES, ORIENTATION);
    shipModel = fopen(shipModel_path, "r");
    if(shipModel == NULL)
        mvwprintw(PARENT, 1,1, "ERROR READING FILE");
    else
    {
        i = 0;
        while(fgets(line , 100 , shipModel))
        {
            //wattron(PARENT, COLOR_PAIR(SHIP_DRAW));
            strtok(line, "\n");
            mvwprintw(PARENT, Y + i, X , line);
            //wattroff(PARENT, COLOR_PAIR(SHIP_DRAW));
            i++;
        }
        
    }
    fclose(shipModel);
}
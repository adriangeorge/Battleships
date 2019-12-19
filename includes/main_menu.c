#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include "main_menu.h"
#include "magic_numbers.h"
#include "draw.h"

void menu_navigation(int* GAMESTATE, WINDOW** options)
{
    init_pair(3, COLOR_RED, COLOR_BLUE);
    int selection = 0;
    int keyPRESS;
    int i;

    char option_text[3][18] = {"New Game", "Resume", "Exit"};

    //print all options in their respective boxes
    for(i = 0; i < OPTION_COUNT; i++)
    {
        mvwprintw(options[i], 1, 20/2 - strlen(option_text[i])/2, "%s", option_text[i]);
        wrefresh(options[i]);
    }
    
    //according to keypresses highlight an option
    while(*GAMESTATE)
    {   
        mvwprintw(options[selection], 1, 20/2 - strlen(option_text[selection])/2, "%s", option_text[selection]);
        wrefresh(options[selection]);
        switch(keyPRESS)
        {
            case KEY_UP:
                selection--;
                if(selection < 0)
                    selection = 0;
                break;

            case KEY_DOWN:
                selection++;
                if(selection == OPTION_COUNT)
                    selection = OPTION_COUNT - 1;
                break;
        }

        if(keyPRESS == 10)
        {   
            switch (selection)
            {
            case 0:
                *GAMESTATE = 2;
                break;
            
            case 1:
                *GAMESTATE = 3;
                break;
            case 2:
                *GAMESTATE = 0;
                break;
            }
            endwin();
            create_main_window(MAIN_SCREEN_H,MAIN_SCREEN_W,MAIN_SCREEN_Y,MAIN_SCREEN_X);
            break;
        }
        
        //highlight the currently selected option and print it 
        wattron(options[selection], COLOR_PAIR(3));
        mvwprintw(options[selection], 1, 20/2 - strlen(option_text[selection])/2, option_text[selection]);
        wattroff(options[selection], COLOR_PAIR(3));
        
        wrefresh(options[selection]);
        keyPRESS = getch();
        
        
    }
    
}




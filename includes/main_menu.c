#include <string.h>
#include <signal.h>
#include <ncurses.h>

#include "magic_numbers.h"
#include "color_pairs.h"
#include "draw.h"
#include "main_menu.h"


void menu(int* GAMESTATE, WINDOW** options, WINDOW* background, WINDOW* title)
{
    initscr();
    checkScreenSize();
    int selection = 0;
    int keyPRESS;

    char option_text[3][20] = {"New Game", "Resume", "Exit"};


    draw_background(background);
    draw_title(title);
    draw_buttons(options);

    

    //print all options in their boxes
    int i;
    for(i = 0; i < OPTION_COUNT; i++)
    {
        mvwprintw(options[i], 1, 20/2 - strlen(option_text[i])/2, option_text[i]);
        wrefresh(options[i]);
    }
    
    //according to keypresses highlight an option
    while(*GAMESTATE)
    {   
        mvwprintw(options[selection], 1, 20/2 - strlen(option_text[selection])/2, option_text[selection]);
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
            draw_background(background);
            break;
        }
        
        //highlight the currently selected option and print it 
        wattron(options[selection], COLOR_PAIR(SELECTED_TEXT));
        mvwprintw(options[selection], 1, 20/2 - strlen(option_text[selection])/2, option_text[selection]);
        wattroff(options[selection], COLOR_PAIR(SELECTED_TEXT));
        
        wrefresh(options[selection]);
        keyPRESS = getch();   
    }

}




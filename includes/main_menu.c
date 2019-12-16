#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include "main_menu.h"
#include "drawing.h"
#include "magic_numbers.h"


void draw_title(WINDOW* TITLE_WIN)
{
    

    TITLE_WIN = newwin(TITLE_H, TITLE_W, TITLE_Y, TITLE_X);
    box(TITLE_WIN, 0, 0);
    
    start_color();
    init_pair(1, COLOR_WHITE,COLOR_BLUE);
    wbkgd(TITLE_WIN,COLOR_PAIR(1));


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
    init_pair(1, COLOR_WHITE,COLOR_BLUE);
    for(i = 0 ; i < OPTION_COUNT ; i++)
        {   
            options[i] = create_window(3, 20, BUTTON_Y , BUTTON_X);
            wbkgd(options[i],COLOR_PAIR(1));
            wrefresh(options[i]);
        }
}

void draw_main_menu(WINDOW* title, WINDOW** options)
{
    start_color();
    draw_title(title);
    wrefresh(title);
    draw_buttons(options);
}

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




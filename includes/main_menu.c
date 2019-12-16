#include <ncurses.h>
#include <string.h>
#include "main_menu.h"
#include "drawing.h"




void draw_title(WINDOW* TITLE_WIN ,WINDOW* PARENT_WINDOW)
{
    int SCR_Y;
    int SCR_X;
    int SCR_H;
    int SCR_W;

    getyx(PARENT_WINDOW, SCR_Y, SCR_X);
    getmaxyx(PARENT_WINDOW,SCR_H,SCR_W);

    TITLE_WIN = newwin(TITLE_H, TITLE_W, TITLE_Y, TITLE_X);
    box(TITLE_WIN, 0, 0);
    
    start_color();
    init_pair(1, COLOR_WHITE,COLOR_BLUE);
    wbkgd(TITLE_WIN,COLOR_PAIR(1));


    mvwprintw(TITLE_WIN, TITLE_H/2 - 5/2 + 0, TITLE_W/2 - 69/2 ,   "______  ___ _____ _____ _      _____ _____ _   _ ___________  _____ ");
    mvwprintw(TITLE_WIN, TITLE_H/2 - 5/2 + 1, TITLE_W/2 - 69/2 ,   "| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\/  ___|");
    mvwprintw(TITLE_WIN, TITLE_H/2 - 5/2 + 2, TITLE_W/2 - 69/2 ,   "| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /\\ `--. ");
    mvwprintw(TITLE_WIN, TITLE_H/2 - 5/2 + 3, TITLE_W/2 - 69/2 ,   "| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/  `--. \\");
    mvwprintw(TITLE_WIN, TITLE_H/2 - 5/2 + 4, TITLE_W/2 - 69/2 ,   "| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |    /\\__/ /");
    mvwprintw(TITLE_WIN, TITLE_H/2 - 5/2 + 5, TITLE_W/2 - 69/2 ,   "\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|    \\____/ ");

    wrefresh(TITLE_WIN);
}

void draw_buttons(WINDOW **options, WINDOW *PARENT)
{
    int SCR_Y;
    int SCR_X;
    int SCR_H;
    int SCR_W;

    getyx(PARENT, SCR_Y, SCR_X);
    getmaxyx(PARENT,SCR_H,SCR_W);
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

void draw_main_menu(WINDOW* main_window, WINDOW* title, WINDOW** options )
{
    start_color();
    init_pair(2, COLOR_BLACK,COLOR_WHITE);
    main_window = create_window(SCREEN_H, SCREEN_W, SCREEN_X, SCREEN_Y);
    wbkgd(main_window,COLOR_PAIR(2));
    wrefresh(main_window);
    draw_title(title, main_window);
    wrefresh(title);
    draw_buttons(options , main_window);
}

void menu_navigation(WINDOW** options)
{
    init_pair(3, COLOR_RED, COLOR_BLUE);
    int selection = 0;
    int keyPRESS;
    int i;
    int GAMESTATE = 1;

    char option_text[3][18] = {"New Game", "Resume", "Exit"};

    for(i = 0; i < OPTION_COUNT; i++)
    {
        mvwprintw(options[i], 1, 20/2 - strlen(option_text[i])/2, "%s", option_text[i]);
        wrefresh(options[i]);
    }

    
    
    while(GAMESTATE)
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
        if(selection == 10)
            break;

        wattron(options[selection], COLOR_PAIR(3));
        mvwprintw(options[selection], 1, 20/2 - strlen(option_text[selection])/2, option_text[selection]);
        wattroff(options[selection], COLOR_PAIR(3));
        wrefresh(options[selection]);
        keyPRESS = getch();
        
        
    }
    
}




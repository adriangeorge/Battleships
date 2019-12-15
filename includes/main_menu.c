#include <ncurses.h>
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

    TITLE_WIN = newwin(13, 124, 2, 2);
    box(TITLE_WIN, 0, 0);
    
    start_color();
    init_pair(1, COLOR_WHITE,COLOR_BLUE);
    wbkgd(TITLE_WIN,COLOR_PAIR(1));

    mvwprintw(TITLE_WIN, 13/2 - 5/2 + 0, 124/2 - 69/2 ,   "______  ___ _____ _____ _      _____ _____ _     ___________  _____  ");
    mvwprintw(TITLE_WIN, 13/2 - 5/2 + 1, 124/2 - 69/2 ,   "| ___ \\/ _ \\_   _|_   _| |    |  ___/  ___| | | |_   _| ___ \\/  ___|");
    mvwprintw(TITLE_WIN, 13/2 - 5/2 + 2, 124/2 - 69/2 ,   "| |_/ / /_\\ \\| |   | | | |    | |__ \\ `--.| |_| | | | | |_/ /\\ `--. ");
    mvwprintw(TITLE_WIN, 13/2 - 5/2 + 3, 124/2 - 69/2 ,   "| ___ \\  _  || |   | | | |    |  __| `--. \\  _  | | | |  __/  `--. \\");
    mvwprintw(TITLE_WIN, 13/2 - 5/2 + 4, 124/2 - 69/2 ,   "| |_/ / | | || |   | | | |____| |___/\\__/ / | | |_| |_| |    /\\__/ /");
    mvwprintw(TITLE_WIN, 13/2 - 5/2 + 5, 124/2 - 69/2 ,   "\\____/\\_| |_/\\_/   \\_/ \\_____/\\____/\\____/\\_| |_/\\___/\\_|    \\____/ ");

    wrefresh(TITLE_WIN);
}

void draw_buttons(WINDOW **options, WINDOW *PARENT)
{
    int SCR_Y;
    int SCR_X;
    int SCR_H;
    int SCR_W;

    char option_text[3][18] = {"New Game", "Resume", "Exit"};
    getyx(PARENT, SCR_Y, SCR_X);
    getmaxyx(PARENT,SCR_H,SCR_W);
    printf("%s", option_text[0]);
    start_color();
    int i;
    init_pair(1, COLOR_WHITE,COLOR_BLUE);
    for(i = 0 ; i < OPTION_COUNT ; i++)
        {   
            options[i] = create_window(3, 20, BUTTON_Y , BUTTON_X);
            wbkgd(options[i],COLOR_PAIR(1));
            mvwprintw(options[i], 1 , 1,  "%s" , option_text[i]);
            wrefresh(options[i]);
        }

}

void menu_navigation(int GAMESTATE, WINDOW** options)
{
    init_pair(3, COLOR_RED, COLOR_CYAN);
    int selection = 0;
    int keyPRESS;
    int i;

    while(GAMESTATE)
    {
        for(i = 0; i < OPTION_COUNT; i++)
        {
            if(i == selection)
            {
               wattron(options[i], COLOR_PAIR(3));
            
            switch (i)
            {
            case 0:
                mvprintw(getbegy(options[i]) + 1, getbegx(options[i]) + 1, option1);
                break;
            case 1:
                mvprintw(getbegy(options[i]) + 1, getbegx(options[i]) + 1, option2);
                break;
            case 2:
                mvprintw(getbegy(options[i]) + 1, getbegx(options[i]) + 1, option3);
                break;
            }
            }
            wattroff(options[i], COLOR_PAIR(3));
        }
        
        switch(keyPRESS)
        {
            case KEY_UP:
                wclear(options[selection]);
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

        for(i = 0; i < OPTION_COUNT; i++)
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


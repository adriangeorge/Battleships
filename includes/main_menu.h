#define OPTION_COUNT    3
#define SCREEN_Y        0
#define SCREEN_X        0
#define SCREEN_H        32
#define SCREEN_W        128
#define BUTTON_Y        SCR_H/2 + SCR_Y + (OPTION_COUNT + 1)*i
#define BUTTON_X        SCR_W/2 - 20/2
#define TITLE_H         13
#define TITLE_W         124
#define TITLE_Y         2
#define TITLE_X         2

void draw_title(WINDOW* TITLE_WIN ,WINDOW* PARENT_WINDOW);
void draw_buttons(WINDOW **options, WINDOW *PARENT);
void draw_main_menu(WINDOW* main_window, WINDOW* title, WINDOW** options );
void menu_navigation(WINDOW** options);
WINDOW* create_window(int SCR_H, int SCR_W, int SCR_Y, int SCR_X, int color);
void draw_background(WINDOW* bkgrd);
void draw_game_grid(WINDOW* game_maps);
WINDOW* draw_inventory(WINDOW* inventory);
void checkScreenSize();
void draw_title(WINDOW* TITLE_WIN);
void draw_buttons(WINDOW **options);
void draw_ship(WINDOW* PARENT, int Y, int X, int MODULES, int ORIENTATION);

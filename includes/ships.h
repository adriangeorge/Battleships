typedef struct ship
{
    int X;
    int Y;
    int modules;
    int orientation;
    int hitModules[4];

}ship;

void draw_ship(WINDOW* PARENT, ship SHIP);
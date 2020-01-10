typedef struct ship ship;

typedef struct ship
{
    int X;
    int Y;
    int size;
    int orientation;
    char hitModules[5];

}ship;

void init_ships(ship* ships);
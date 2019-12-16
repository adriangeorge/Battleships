CC=gcc
CFLAGS=-g -lncurses -o
SRC=battleships.c
INCLD=includes/drawing.c includes/main_menu.c includes/game_grid.c

make: $(INCLD)
	$(CC) $(SRC) $(INCLD) $(CFLAGS) battleships
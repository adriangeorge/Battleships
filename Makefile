CC=gcc
CFLAGS=-g -lncurses -o
SRC=battleships.c
INCLD=includes/draw.c includes/main_menu.c includes/placement.c includes/ships.c includes/color_pairs.c

make: $(INCLD)
	$(CC) $(SRC) $(INCLD) $(CFLAGS) battleships
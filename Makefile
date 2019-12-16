CC=gcc
CFLAGS=-lncurses -o

make: battleships.c includes/drawing.c includes/main_menu.c
	$(CC) battleships.c includes/drawing.c includes/main_menu.c $(CFLAGS) battleships
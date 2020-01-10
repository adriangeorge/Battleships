CC=gcc
CFLAGS=-g -lncurses -o
SRC=battleship.c
INCLD=draw.c main_menu.c placement.c ships.c color_pairs.c gameplay.c utils.c

build: $(INCLD)
	$(CC) $(SRC) $(INCLD) $(CFLAGS) battleship

run:
	./battleship
clean:
	rm -rf battleship
CC = gcc
EXEC = prog
CFLAGS= -Wall 
LDFLAGS= `sdl2-config --cflags --libs` -lSDL2_image
OBJ = $(addprefix obj/, $(SRC:.c=.o))

default: $(EXEC) test

$(EXEC): player.o main.o plateau.o
	$(CC) -o bin/prog build/player.o build/main.o build/plateau.o $(CFLAGS) $(LDFLAGS)

player.o: src/player.c
	$(CC) -o build/player.o -c src/player.c $(CFLAGS) $(LDFLAGS)

plateau.o: src/plateau.c
	$(CC) -o build/plateau.o -c src/plateau.c $(CFLAGS) $(LDFLAGS)


main.o: src/main.c src/player.h src/plateau.h
	$(CC) -o build/main.o -c src/main.c $(CFLAGS) $(LDFLAGS)

test: test_game.o unity.o player.o
	$(CC) -o bin/test_game build/test_game.o build/unity.o build/player.o build/plateau.o -Iunity/src -Isrc -Iinclude $(CFLAGS) $(LDFLAGS)

test_game.o: test/test_game.c player.o  src/player.h  src/plateau.h
	$(CC) -o build/test_game.o -c test/test_game.c -Iunity/src -Isrc $(CFLAGS) $(LDFLAGS)

unity.o: unity/src/unity.c
	$(CC) -o build/unity.o -c unity/src/unity.c $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	$(RM) build/*.o bin/prog bin/test_game



#sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
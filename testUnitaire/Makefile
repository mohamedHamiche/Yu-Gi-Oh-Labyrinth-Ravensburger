CC = gcc
EXEC = prog
CFLAGS= -Wall 

default: $(EXEC) test

$(EXEC): player.o main.o pile.o
	$(CC) -o bin/player build/player.o build/pile.o build/main.o $(CFLAGS)

player.o: src/player.c
	$(CC) -o build/player.o -c src/player.c $(CFLAGS)

pile.o: src/pile.c
	$(CC) -o build/pile.o -c src/pile.c $(CFLAGS)

main.o: src/main.c src/player.h
	$(CC) -o build/main.o -c src/main.c $(CFLAGS)

test: test_game.o unity.o player.o
	$(CC) -o bin/test_game build/test_game.o build/unity.o build/player.o build/pile.o -Iunity/src -Isrc $(CFLAGS)

test_game.o: test/test_game.c player.o pile.o src/player.h
	$(CC) -o build/test_game.o -c test/test_game.c -Iunity/src -Isrc $(CFLAGS)

unity.o: unity/src/unity.c
	$(CC) -o build/unity.o -c unity/src/unity.c $(CFLAGS)

.PHONY: clean

clean:
	$(RM) build/* bin/*

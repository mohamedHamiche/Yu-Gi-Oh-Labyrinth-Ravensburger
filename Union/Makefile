CC = gcc
EXEC = prog
CFLAGS= -Wall 
LDFLAGS= -I include -L lib -lmingw32 -lSDL2main -lSDL2

default: $(EXEC) test

$(EXEC): player.o main.o pile.o plateau.o
	$(CC) -o bin/prog build/player.o build/pile.o build/main.o build/plateau.o $(CFLAGS) $(LDFLAGS)

player.o: src/player.c
	$(CC) -o build/player.o -c src/player.c $(CFLAGS) $(LDFLAGS)

plateau.o: src/plateau.c
	$(CC) -o build/plateau.o -c src/plateau.c $(CFLAGS) $(LDFLAGS)

pile.o: src/pile.c
	$(CC) -o build/pile.o -c src/pile.c $(CFLAGS) $(LDFLAGS)

main.o: src/main.c src/player.h src/pile.h src/plateau.h
	$(CC) -o build/main.o -c src/main.c $(CFLAGS) $(LDFLAGS)

test: test_game.o unity.o player.o
	$(CC) -o bin/test_game build/test_game.o build/unity.o build/player.o build/pile.o build/plateau.o -Iunity/src -Isrc -Iinclude $(CFLAGS) $(LDFLAGS)

test_game.o: test/test_game.c player.o pile.o src/player.h src/pile.h src/plateau.h
	$(CC) -o build/test_game.o -c test/test_game.c -Iunity/src -Isrc $(CFLAGS) $(LDFLAGS)

unity.o: unity/src/unity.c
	$(CC) -o build/unity.o -c unity/src/unity.c $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	$(RM) build/*.o bin/*.exe

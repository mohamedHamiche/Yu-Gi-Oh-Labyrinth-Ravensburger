CC = gcc
EXEC = prog
CFLAGS= -Wall -I include -L lib -lmingw32 -lSDL2main -lSDL2
#RM = del
#default: $(EXEC) test

$(EXEC): main.o
	$(CC) -o bin/prog build/main.o $(CFLAGS)

main.o: src/main.c 
	$(CC) -o build/main.o -c src/sdl.c $(CFLAGS) 


.PHONY: clean

clean:
	$(RM) build/* bin/prog.exe

#gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 [-mwindows]
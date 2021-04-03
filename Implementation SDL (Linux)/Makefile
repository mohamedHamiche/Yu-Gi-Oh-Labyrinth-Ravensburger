CC = gcc
EXEC = prog
FLAGS = -Wall
CFLAGS = `sdl2-config --cflags --libs`

$(EXEC) : main.o
	$(CC) -o prog build/main.o $(FLAGS) $(CFLAGS)


main.o : src/main.c
	$(CC)  -o build/main.o -c src/main.c $(FLAGS) $(CFLAGS)

.PHONY:
	clean

clean: 
	rm  -rf build/*.o bin/prog

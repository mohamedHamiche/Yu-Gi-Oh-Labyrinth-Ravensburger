CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=Jeu

all: $(EXEC)

Jeu: jeu.o alterner.o choixCouloir.o decalerCouloir.o initPlateau.o oppose.o quiCommence.o tresorAtteint.o tuilesFixes.o 
	$(CC) -o jeu alterner.o choixCouloir.o decalerCouloir.o initPlateau.o oppose.o quiCommence.o tresorAtteint.o tuilesFixes.o validationCouloir.o

alterner.o : alterner.c structures.h
	$(CC) -o alterner.o -c alterner.c $(CFLAGS)

choixCouloir.o : choixCouloir.c structures.h
	$(CC) -o choixCouloir.o -c choixCouloir.c $(CFLAGS)

decalerCouloir.o : decalerCouloir.c structures.h
	$(CC) -o decalerCouloir.o -c decalerCouloir.c $(CFLAGS)

initPlateau.o : initPlateau.c tuilesFixes.c tuilesCouloir.c structures.h
	$(CC) -o initPlateau.o -c initPlateau.c $(CFLAGS)

oppose.o : oppose.c structures.h
	$(CC) -o oppose.o -c oppose.c $(CFLAGS)

quiCommence.o : quiCommence.c structures.h
	$(CC) -o quiCommence.o -c quiCommence.c $(CFLAGS)

tresorAtteint.o : tresorAtteint.c structures.h
	$(CC) -o tresorAtteint.o -c tresorAtteint.c $(CFLAGS)

tuilesFixes.o : tuilesFixes.c structures.h
	$(CC) -o tuilesFixes.o -c tuilesFixes.c $(CFLAGS)

validationCouloir.o : validationCouloir.c oppose.c structures.h
	$(CC) -o validationCouloir.o -c validationCouloir.c $(CFLAGS)

clean:
    rm -rf *.o

mrproper: clean
    rm -rf $(EXEC)





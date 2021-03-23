Jeu: alterner.o
	gcc -o jeu alterner.o choixCouloir.o decalerCouloir.o initPlateau.o oppose.o quiCommence.o tresorAtteint.o tuilesFixes.o validationCouloir.o

alterner.o : alterner.c structures.h
	gcc -o alterner.o -c alterner.c

choixCouloir.o : choixCouloir.c structures.h
	gcc -o choixCouloir.o -c choixCouloir.c

decalerCouloir.o : decalerCouloir.c structures.h
	gcc -o decalerCouloir.o -c decalerCouloir.c

initPlateau.o : initPlateau.c tuilesFixes.c tuilesCouloir.c structures.h
	gcc -o initPlateau.o -c initPlateau.c

oppose.o : oppose.c structures.h
	gcc -o oppose.o -c oppose.c
quiCommence.o : quiCommence.c structures.h
	gcc -o quiCommence.o -c quiCommence.c

tresorAtteint.o : tresorAtteint.c structures.h
	gcc -o tresorAtteint.o -c tresorAtteint.c

tuilesFixes.o : tuilesFixes.c structures.h
	gcc -o tuilesFixes.o -c tuilesFixes.c

validationCouloir.o : validationCouloir.c oppose.c structures.h
	gcc -o validationCouloir.o -c validationCouloir.c





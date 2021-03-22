#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

//Fonction à compléter

void tuilesCouloir(TUILE Plateau[7][7], TUILE tuileEnMain){
	srand(time(NULL));

	TUILE tuilesCouloir[34];
	/*
	*Remplir toutes les tuiles couloirs ligne par ligne..
	*Faire un rand pour les tuiles sur les positions d'ouvertures pour pas avoir toutes les tuiles orientées dans la même direction.
	*/

	CORD tAleatoire;
	unsigned int i=0;
	while(i<33){ // Remplissage aléatorire
		pAleatoire.x = rand()%7;
		pAleatoire.y = rand()%7;
		if(Plateau[pAleatoire.x][pAleatoire.y].fixe == 0){
			Plateau[pAleatoire.x][pAleatoire.y] = tuilesCouloir[i];
			i++;
		}
	}
	tuileEnMain = tuilesCouloir[i];

}

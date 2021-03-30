#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

//Fonction à compléter

void tuilesCouloir(TUILE Plateau[7][7], TUILE tuileEnMain){
	srand(time(NULL));
	unsigned int temp = 0, opp; 

	TUILE tuilesCouloir[34];
	/*
	*Remplir toutes les tuiles couloirs ligne par ligne..
	*Faire un rand pour les tuiles sur les positions d'ouvertures pour pas avoir toutes les tuiles orientées dans la même direction.
	*/
	TUILE tuilesLignes[12];
	TUILE angleDroit[10];

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[0].fixe =0;
	tuilesLignes[0].tresor =0;
	tuilesLignes[0].g = temp;
	tuilesLignes[0].d = temp;
	tuilesLignes[0].h = opp;
	tuilesLignes[0].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[1].fixe =0;
	tuilesLignes[1].tresor =0;
	tuilesLignes[1].g = temp;
	tuilesLignes[1].d = temp;
	tuilesLignes[1].h = opp;
	tuilesLignes[1].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[2].fixe =0;
	tuilesLignes[2].tresor =0;
	tuilesLignes[2].g = temp;
	tuilesLignes[2].d = temp;
	tuilesLignes[2].h = opp;
	tuilesLignes[2].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[3].fixe =0;
	tuilesLignes[3].tresor =0;
	tuilesLignes[3].g = temp;
	tuilesLignes[3].d = temp;
	tuilesLignes[3].h = opp;
	tuilesLignes[3].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[4].fixe =0;
	tuilesLignes[4].tresor =0;
	tuilesLignes[4].g = temp;
	tuilesLignes[4].d = temp;
	tuilesLignes[4].h = opp;
	tuilesLignes[4].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[5].fixe =0;
	tuilesLignes[5].tresor =0;
	tuilesLignes[5].g = temp;
	tuilesLignes[5].d = temp;
	tuilesLignes[5].h = opp;
	tuilesLignes[5].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[6].fixe =0;
	tuilesLignes[6].tresor =0;
	tuilesLignes[6].g = temp;
	tuilesLignes[6].d = temp;
	tuilesLignes[6].h = opp;
	tuilesLignes[6].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[7].fixe =0;
	tuilesLignes[7].tresor =0;
	tuilesLignes[7].g = temp;
	tuilesLignes[7].d = temp;
	tuilesLignes[7].h = opp;
	tuilesLignes[7].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[8].fixe =0;
	tuilesLignes[8].tresor =0;
	tuilesLignes[8].g = temp;
	tuilesLignes[8].d = temp;
	tuilesLignes[8].h = opp;
	tuilesLignes[8].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[9].fixe =0;
	tuilesLignes[9].tresor =0;
	tuilesLignes[9].g = temp;
	tuilesLignes[9].d = temp;
	tuilesLignes[9].h = opp;
	tuilesLignes[9].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[10].fixe =0;
	tuilesLignes[10].tresor =0;
	tuilesLignes[10].g = temp;
	tuilesLignes[10].d = temp;
	tuilesLignes[10].h = opp;
	tuilesLignes[10].b = opp;

	temp = rand()%2;
	if(temp == 0)
		opp = 1;
	else
		opp = 0;

	tuilesLignes[11].fixe =0;
	tuilesLignes[11].tresor =0;
	tuilesLignes[11].g = temp;
	tuilesLignes[11].d = temp;
	tuilesLignes[11].h = opp;
	tuilesLignes[11].b = opp;
	
	for(int i=0; i<24; i+=2)
		tuilesCouloir[i] = tuileslignes[i];


	//### TUILE : angle droit
	unsigned int g,d,b,h;
	temp = rand()%4;
	if(temp == 0){
		g = 0;
		d = 1;
		b = 1;
		h = 0;
	}
	else if(temp == 1){
		g = 0;
		d = 1;
		b = 0;
		h = 1;
	}
	else if(temp == 2){
		g = 1;
		d = 0;
		b = 0;
		h = 1;
	}
	else if(temp == 2){
		g = 1;
		d = 0;
		b = 1;
		h = 0;
	}

		opp = 0;

	

	

	CORD tAleatoire, pAleatoire;
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


void ouvertureRand(unsigned int *g,unsigned int *d,unsigned int *b,unsigned int *h){
	srand(time(NULL));
	unsigned int temp = rand()%4;
	if(temp == 0){
		(*g) = 0;
		(*d) = 1;
		(*b) = 1;
		(*h) = 0;
	}
	else if(temp == 1){
		(*g) = 0;
		(*d) = 1;
		(*b) = 0;
		(*h) = 1;
	}
	else if(temp == 2){
		(*g) = 1;
		(*d) = 0;
		(*b) = 0;
		(*h) = 1;
	}
	else if(temp == 2){
		(*g) = 1;
		(*d) = 0;
		(*b) = 1;
		(*h) = 0;
	}
}
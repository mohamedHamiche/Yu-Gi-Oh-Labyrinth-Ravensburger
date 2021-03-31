#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

void ouvertureRand(unsigned int *g,unsigned int *d,unsigned int *b,unsigned int *h);

void tuilesCouloir(TUILE Plateau[7][7], TUILE tuileEnMain){
	srand(time(NULL));
	unsigned int temp = 0, opp; 

	TUILE tuilesCouloir[34];	
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
	
	for(int i=0; i<12; i++)
		tuilesCouloir[i] = tuilesLignes[i];


	//### TUILE : angle droit
	angleDroit[0].fixe = 0;
	angleDroit[0].tresor = 0;
	ouvertureRand(&angleDroit[0].g, &angleDroit[0].d,&angleDroit[0].b, &angleDroit[0].h);

	angleDroit[1].fixe = 0;
	angleDroit[1].tresor = 0;
	ouvertureRand(&angleDroit[1].g, &angleDroit[1].d,&angleDroit[1].b, &angleDroit[1].h);

	angleDroit[2].fixe = 0;
	angleDroit[2].tresor = 0;
	ouvertureRand(&angleDroit[2].g, &angleDroit[2].d,&angleDroit[2].b, &angleDroit[2].h);

	angleDroit[3].fixe = 0;
	angleDroit[3].tresor = 0;
	ouvertureRand(&angleDroit[3].g, &angleDroit[3].d,&angleDroit[3].b, &angleDroit[3].h);

	angleDroit[4].fixe = 0;
	angleDroit[4].tresor = 0;
	ouvertureRand(&angleDroit[4].g, &angleDroit[4].d,&angleDroit[4].b, &angleDroit[4].h);

	angleDroit[5].fixe = 0;
	angleDroit[5].tresor = 0;
	ouvertureRand(&angleDroit[5].g, &angleDroit[5].d,&angleDroit[5].b, &angleDroit[5].h);

	angleDroit[6].fixe = 0;
	angleDroit[6].tresor = 0;
	ouvertureRand(&angleDroit[6].g, &angleDroit[6].d,&angleDroit[6].b, &angleDroit[6].h);

	angleDroit[7].fixe = 0;
	angleDroit[7].tresor = 0;
	ouvertureRand(&angleDroit[7].g, &angleDroit[7].d,&angleDroit[7].b, &angleDroit[7].h);

	angleDroit[8].fixe = 0;
	angleDroit[8].tresor = 0;
	ouvertureRand(&angleDroit[8].g, &angleDroit[8].d,&angleDroit[8].b, &angleDroit[8].h);

	angleDroit[9].fixe = 0;
	angleDroit[9].tresor = 0;
	ouvertureRand(&angleDroit[9].g, &angleDroit[9].d,&angleDroit[9].b, &angleDroit[9].h);

	for(int i=12; i<22; i++)
		tuilesCouloir[i] = angleDroit[i];
	

	

	CORD tAleatoire, pAleatoire;
	unsigned int i=0;
	while(i<22){ // Remplissage aléatorire
		pAleatoire.x = rand()%7;
		pAleatoire.y = rand()%7;
		if(Plateau[pAleatoire.x][pAleatoire.y].posee == 0){
			Plateau[pAleatoire.x][pAleatoire.y] = tuilesCouloir[i];
			Plateau[pAleatoire.x][pAleatoire.y].posee = 1;
			i++;
		}
	}
	//tuileEnMain = tuilesCouloir[i];

}





void ouvertureRand(unsigned int *g,unsigned int *d,unsigned int *b,unsigned int *h){
	/*
	*Cette fonciton permet de retourner des ouvertures (les sorties et entrées possibles de la tuile) d'une tuiles "angle droit"
	*au hasard, afin d'éviter d'avoir les tuiles orientées tous dans le même sens lors de l'initialisation du plateau. 
	*/
	srand(time(NULL));
	unsigned int r = rand()%4;
	if(r == 0){
		(*g) = 0;
		(*d) = 1;
		(*b) = 1;
		(*h) = 0;
	}
	else if(r == 1){
		(*g) = 0;
		(*d) = 1;
		(*b) = 0;
		(*h) = 1;
	}
	else if(r == 2){
		(*g) = 1;
		(*d) = 0;
		(*b) = 0;
		(*h) = 1;
	}
	else if(r == 3){
		(*g) = 1;
		(*d) = 0;
		(*b) = 1;
		(*h) = 0;
	}
}
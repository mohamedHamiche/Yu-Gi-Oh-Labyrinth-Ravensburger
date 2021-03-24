#include <stdio.h>
#include <stdlib.h>
#include "player.h"
//#include "pile.h"

int main()
{
	/*
	unsigned int nbTotal=0;		
	JOUEUR **tabJoueur= initTabJoueur(&nbTotal);
	printPlayers(tabJoueur,nbTotal);
	freeTabJoueur(tabJoueur);
	*/

	Pile *pileTresor=initPile(25);
	afficherPile(pileTresor);
	empiler(pileTresor,1);
	empiler(pileTresor,2);
	afficherPile(pileTresor);
	//depiler(pileTresor);
	afficherPile(pileTresor);
	//while(!pileVide(pileTresor))
		printf("depiler %d\n",depiler(pileTresor)) ;

	afficherPile(pileTresor);

	return 0;
}

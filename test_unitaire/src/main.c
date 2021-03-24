#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"


int main()
{
	srand(time(NULL));
	unsigned int nbTotal=0;		
	JOUEUR **tabJoueur= initTabJoueur(&nbTotal);
	printPlayers(tabJoueur,nbTotal);
	/*distribuerCartes(tabJoueur,nbTotal);
	afficherPile(tabJoueur[0]->pile_tresor);
	afficherPile(tabJoueur[1]->pile_tresor);
	*/
	freeTabJoueur(tabJoueur);
	
	return 0;
}

#include <stdio.h>
#include "player.h"
#include "pile.h"

int main()
{
	srand(time(NULL));
	int nbTotal=0;		
	JOUEUR **tabJoueur= initTabJoueur(&nbTotal);
	initPositions(tabJoueur,nbTotal);
	printPlayers(tabJoueur,nbTotal);
	distribuerCartes(tabJoueur,nbTotal);
	for (int i = 0; i < nbTotal; ++i)
    {
        printf("tresors de %s\n",tabJoueur[i]->pseudo);
        afficherPile(tabJoueur[i]->pile_tresor);
    }
    
	

	freeTabJoueur(tabJoueur);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

int main()
{
	unsigned int nbTotal=0;		
	JOUEUR **tabJoueur= initTabJoueur(&nbTotal);
	printPlayers(tabJoueur,nbTotal);
	freeTabJoueur(tabJoueur);
	return 0;
}

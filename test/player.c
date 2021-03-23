#include <stdio.h>
#include <stdlib.h>

char *lirePseudo(unsigned int numJoueur)
{
	char *pseudo= malloc(25*sizeof(char));
	printf("Donnez le pseudo du joueur %d :\n",numJoueur);
	scanf("%s",pseudo);
	return pseudo;
}

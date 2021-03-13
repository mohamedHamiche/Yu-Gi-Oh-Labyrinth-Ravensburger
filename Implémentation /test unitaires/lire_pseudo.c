#include <stdio.h>
#include <stdlib.h>

char *lire_pseudo(unsigned int numJoueur);
int main()
{

	char *pseudo =lire_pseudo(1);
	printf("%s--\n",pseudo );
	free(pseudo);
	return 0;
}

char *lire_pseudo(unsigned int numJoueur)
{
	char *pseudo= malloc(25*sizeof(char));
	printf("Donnez le pseudo du joueur %d :\n",numJoueur);
	scanf("%s",pseudo);
	return pseudo;
}
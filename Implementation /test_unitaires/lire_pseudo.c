#include <stdio.h>
#include <stdlib.h>

char *lirePseudo(unsigned int numJoueur);
int main()
{

	char *pseudo =lirePseudo(1);
	printf("%s--\n",pseudo );
	free(pseudo);
	return 0;
}

char *lirePseudo(unsigned int numJoueur)
{
	char *pseudo= malloc(25*sizeof(char));
	printf("Donnez le pseudo du joueur %d :\n",numJoueur);
	scanf("%s",pseudo);
	return pseudo;
}

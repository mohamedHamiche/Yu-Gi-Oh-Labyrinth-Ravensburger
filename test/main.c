#include <stdio.h>
#include <stdlib.h>
#include "player.h"

int main()
{
	char *pseudo =lirePseudo(1);
	printf("%s--\n",pseudo );
	free(pseudo);
	return 0;
}

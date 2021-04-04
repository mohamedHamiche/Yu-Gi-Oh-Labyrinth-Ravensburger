#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

unsigned int validationCouloir(CORD &choixActuel, CORD &choixPrecedent)
{
	if(oppose(choixActuel,choixPrecedent)){
		choixPrecedent->x = choixActuel->x;
		choixPrecedent->y = choixActuel->y;
		return 1;
	}
	else return 0;
}

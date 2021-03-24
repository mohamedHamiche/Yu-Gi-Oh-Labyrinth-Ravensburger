#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

unsigned int validationCouloir(CORD choixActuel, CORD choixPrecedent){ //Entrer les adresses afin de changer les valeurs
	if(oppose(choixActuel,choixPrecedent)){
		choixPrecedent = choixActuel;
		return 1;
	}
	else return 0;
}
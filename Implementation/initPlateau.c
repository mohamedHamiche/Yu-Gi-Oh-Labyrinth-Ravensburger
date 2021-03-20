#include <stdio.h>
#include <stdlib.h>
#include "structures.h"


void initPlateau(TUILE Plateau[7][7], TUILE tuileEnMain){

	for(int i=0; i<7; i++){
		for(int j=0; j<7; j++){
			Plateau[i][j].pose = 0;
		}
	}
	TuilesFixes(Plateau);
	TuilesCouloir(Plateau, tuileEnMain);
}

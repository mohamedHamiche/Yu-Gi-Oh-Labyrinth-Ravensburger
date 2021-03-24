#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

//Vérification si le trésor atteint:

tresorAtteint(JOUEUR *P1, TUILE Plateau[7][7]){

    CORD a = P1->positionActuelle;
    if(plateau[a.x][a.y].tresor == P1->pileTresor)
        return 1;
    else
    	return 0;
}
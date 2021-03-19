#include <stdio.h>
#include <stdlib.h>

//Vérification si le trésor atteint:

tresorAtteint(Joueur *P1, Tuile Plateau[7][7]){

    coordonnees a = P1->positionActuelle;
    if(plateau[a.x][a.y].tresor == P1->pileTresor)
        return 1;
    else
    	return 0;
}
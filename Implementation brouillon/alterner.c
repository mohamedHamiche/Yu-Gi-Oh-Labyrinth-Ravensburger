#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

// A modifier pour plusieurs joueurs...
void alterner(JOUEUR *p1, JOUEUR *p2, JOUEUR *joueurActuel){
    if(joueurActuel == p1)
    	joueurActuel = p2;
    else
      joueurActuel = p1;
}
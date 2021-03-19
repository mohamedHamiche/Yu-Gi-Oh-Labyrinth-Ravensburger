#include <stdio.h>
#include <stdlib.h>


void alterner(Joueur *p1, Joueur *p2,Joueur *joueurActuel){
    if(joueurActuel == p1)
    	joueurActuel = p2;
    else
      joueurActuel = p1;
}

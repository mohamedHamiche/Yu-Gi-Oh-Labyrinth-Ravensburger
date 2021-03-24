#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <structures.h>


 unsigned int quiCommence(unsigned int nbJoueur){
 	srand(time(NULL));
 	return rand()%nbJoueur/* +1 ? */;
 }
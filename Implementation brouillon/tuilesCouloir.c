#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

TUILE tuilesCouloir(TUILE Plateau[7][7]){
    srand(time(NULL));

    TUILE tuilesCouloir[34];
    listTuilesCouloir(tuilesCouloir); 
   
    
    //charger tuile en main
    char bmpNameX[]="img/1.bmp";
    unsigned int last = rand()%3;
    bmpNameX[4]=last+'1';

    TUILE tmp = tuilesCouloir[last];
    tmp.image=SDL_LoadBMP(bmpNameX);
    if(tmp.image == NULL)
        SDL_ExitWithError("Erreur chargement image tuile en main");

    //charger le plateau
    CORD pAleatoire;
    unsigned int i=0;
    int numTresor;
    char bmpName[] = "img/C/cA.bmp";
    while(i<34)
    { // Remplissage aléatorire de 33 tuiles couloirs
        if(i == last) //si c'est la meme que tuileEnMain on passe
            i++;

        pAleatoire.x = rand()%7;
        pAleatoire.y = rand()%7;
        if(Plateau[pAleatoire.x][pAleatoire.y].posee == 0)
        {
            Plateau[pAleatoire.x][pAleatoire.y] = tuilesCouloir[i];
            Plateau[pAleatoire.x][pAleatoire.y].posee = 1;
            numTresor = Plateau[pAleatoire.x][pAleatoire.y].tresor;
            if(numTresor!=0) //chargement des image tresors
            {
                bmpName[7]=numTresor+'A'-1;
                printf("%s\n",bmpName);
                if((Plateau[pAleatoire.x][pAleatoire.y].image= SDL_LoadBMP(bmpName)) == NULL)
                    SDL_ExitWithError("Erreur chargement image");           
            }
            else
                {  //charger la bonne image selon la forme                  
                    chargerImageSelonType(&Plateau[pAleatoire.x][pAleatoire.y]);
                }

         i++; 
        }

    }    
            

    return tmp;
}
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>



void chargerImageSelonType(TUILE *tmp)
{
    if(tmp->type == 'I') //charger 1.bmp
    {
        if((tmp->image= SDL_LoadBMP("img/1.bmp")) == NULL)
            SDL_ExitWithError("Erreur chargement image");  
    }

    if(tmp->type == 'T') //charger 2.bmp
    {
        if((tmp->image= SDL_LoadBMP("img/2.bmp")) == NULL)
            SDL_ExitWithError("Erreur chargement image");  
    }

    if(tmp->type == 'L') //charger 3.bmp
    {
        if((tmp->image= SDL_LoadBMP("img/3.bmp")) == NULL)
            SDL_ExitWithError("Erreur chargement image");  
    }
    
}
#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include "player.h"
#include "pile.h"


void SDL_ExitWithError(const char *message);
void SDL_ExitWithErrorAndDestroy(const char *message,SDL_Window *window,SDL_Renderer *renderer);

int oppose(CORD a, CORD choixPrecedent);
unsigned int validationCouloir(CORD *choixActuel, CORD *choixPrecedent);
void tuilesFixes(TUILE Plateau[7][7]);
void ouvertureRand(unsigned int *g,unsigned int *d,unsigned int *b,unsigned int *h);
TUILE tuilesCouloir(TUILE Plateau[7][7]);
TUILE decalerCouloir(TUILE plateau[7][7], CORD choixCouloir, TUILE tuileEnMain);
void choixEvent(SDL_Event event, SDL_Rect *tuileEnMain, CORD *choix);
void chargerImageSelonType(TUILE *tmp);
void listTuilesCouloir(TUILE tuilesCouloir[34]);


#endif
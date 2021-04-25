#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include "player.h"
#include "pile.h"


void SDL_ExitWithError(const char *message);
void SDL_ExitWithErrorAndDestroy(const char *message,SDL_Window *window,SDL_Renderer *renderer);
void initPlateau(TUILE plateau[7][7]);
int oppose(CORD a, CORD choixPrecedent);
unsigned int validationCouloir(CORD *choixActuel, CORD *choixPrecedent);
void tuilesFixes(TUILE Plateau[7][7]);
void chargerImageTuileFixe(TUILE plateau[7][7], SDL_Window *window, SDL_Renderer *renderer);
TUILE tuilesCouloir(TUILE Plateau[7][7]);
TUILE decalerCouloir(TUILE plateau[7][7], CORD choixCouloir, TUILE tuileEnMain);
void sortirTuileEnMain(SDL_Rect *tuileEnMain,int indice);
void choixEvent(SDL_Event event, SDL_Rect *tuileEnMain, CORD *choix);
void chargerImageSelonType(TUILE *tmp);
void creerTextures(SDL_Window *window ,SDL_Renderer *renderer, TUILE *tuileEnMain, TUILE plateau[7][7]);
void initRectangles(SDL_Rect *tuileEnMainRect ,SDL_Rect caseSdl[7][7]);
void listTuilesCouloir(TUILE tuilesCouloir[34]);
void getCordClick(SDL_Event event, CORD *choixCase, JOUEUR *joueurActuel);
void deplacerRect(SDL_Event event,SDL_Rect *pionRect, CORD a, int index);
void decalerPion(CORD *pion, CORD choix, SDL_Rect *pionRect);
void validationCoup(TUILE plateau[7][7], CORD actuel, CORD choix, int *temp);
void tournerTuile(TUILE *tuileEnMain);
void initRectPions(JOUEUR **tabJoueur, int nbTotal);


#endif

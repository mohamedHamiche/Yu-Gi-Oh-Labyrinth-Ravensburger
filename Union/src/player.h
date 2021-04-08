#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
//----------------
typedef struct tuile TUILE;
struct tuile
{
    unsigned int angleTuile;
    int id;
    int fixe ;
    int tresor; 
    char type; // I L T
    int g, d, h, b;  
    int posee;
    int angle;

    SDL_Surface *image;
    SDL_Texture *texture;
};

typedef struct coordonnees CORD;
struct coordonnees
{
    unsigned int x;
    unsigned int y;
};

//----------------- Piles
typedef struct Element Element;
struct Element 
{
    int nombre;
    Element *suivant;
};
typedef struct Pile Pile;
struct Pile
{
    Element *premier;
};
//---------------
typedef struct joueur JOUEUR; 
struct joueur
{
    char *pseudo;
    CORD postion_actuelle;
    Pile *pile_tresor;
    int nombre_de_points;
    int machine;
    SDL_Surface *image;
    SDL_Texture *texture;
    SDL_Rect pionRect;
};


//variables globales
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 700

#define positionX (WINDOW_WIDTH-(70*7))/2
#define positionY (WINDOW_HEIGHT-(70*7))/2
//--------------


char *lirePseudo(int numJoueur);
JOUEUR *initJoueurH(int index);
JOUEUR *initJoueurM(int index);
void initPositions(JOUEUR **tabJoueurs,int nombreTotal);
JOUEUR **initTabJoueur(int *nombreTotal);
void freeJoueur(JOUEUR *Player);
void freeTabJoueur(JOUEUR **Tab, int nombreTotal);
void printPlayers(JOUEUR **tabJoueur, int nbTotal);
int appartientTab(int tab[24], int x);
void randomTresors(int tabTresor[24]);
void distribuerCartes(JOUEUR **tabJoueur, int nbTotal);

#endif // PLAYER_H_INCLUDED


#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//----------------
typedef struct tuile TUILE;
struct tuile
{
    int fixe ;// 1 fixe 0 couloir
    int tresor; //0 si pas de trésor, n sinon avec  1<= n <=25
    int g, d, h, b;  // 0 si mur, 1 si ouverture. g : gauche; d : droite ; h : haut ; b : bas 
    int posee; //si la tuile est posée ou pas sur le  plateau
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
};




char *lirePseudo(int numJoueur);
JOUEUR *initJoueurH(int index);
JOUEUR *initJoueurM(int index);
void initPositions(JOUEUR **tabJoueurs,int nombreTotal);
JOUEUR **initTabJoueur(int *nombreTotal);
void freeJoueur(JOUEUR *Player);
void freeTabJoueur(JOUEUR **Tab);// Pas de fuites mémoires, verifié avec valgrind
void printPlayers(JOUEUR **tabJoueur, int nbTotal);
int appartientTab(int tab[24], int x);
void randomTresors(int tabTresor[24]);
void distribuerCartes(JOUEUR **tabJoueur, int nbTotal);

#endif // PLAYER_H_INCLUDED


#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

//-------------------
typedef struct coordonnees CORD;
struct coordonnees
{
    unsigned int x;
    unsigned int y;
};
//----------------
typedef struct tuile TUILE;
struct tuile
{
    int fixe ;// 1 fixe 0 couloir
    int tresor; //0 si pas de trésor, n sinon avec  1<= n <=25
    int g, d, h, b;  // 0 si mur, 1 si ouverture. g : gauche; d : droite ; h : haut ; b : bas 
    int posee; //si la tuile est posée ou pas sur le  plateau
    SDL_Rect caseSdl;
    SDL_Surface *image;
    SDL_Texture *texture;
};

//-----------------Piles
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
    Pile pile_tresor;
    int nombre_de_points;
    int machine;
};

//------------------- fonctions


void Emplier (Pile* pile,int NvNombre);

int depiler (Pile* pile);

void afficherPile (Pile* pile);

//------------------------------------

char *lirePseudo(unsigned int numJoueur);

#endif // PILE_H_INCLUDED


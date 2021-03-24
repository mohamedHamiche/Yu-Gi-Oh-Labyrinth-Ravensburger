#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED


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
//-------------------
typedef struct coordonnees CORD;
struct coordonnees
{
    unsigned int x;
    unsigned int y;
};



//------------------- fonctions
Pile *initPile(int n);
int pileVide(Pile *pile);
void emplier (Pile* pile,int NvNombre);
int depiler (Pile* pile);
void afficherPile (Pile* pile);

#endif // PILE_H_INCLUDED
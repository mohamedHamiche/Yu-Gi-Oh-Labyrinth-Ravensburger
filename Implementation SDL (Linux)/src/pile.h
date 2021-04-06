#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED


//------------------- fonctions
Pile *initPile(int n);
int pileVide(Pile *pile);
void empiler (Pile* pile,int NvNombre);
int depiler (Pile* pile);
void afficherPile (Pile* pile);
void freePile(Pile *pile);
//------------------------------------

#endif // PILE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "player.h"
//#include "pile.h"


Pile *initPile(int n)
{
    Pile *maPile= malloc(sizeof(Pile *));
    Element *tete= malloc(sizeof(Element *));
    if (maPile == NULL || tete == NULL)
    {
        exit(EXIT_FAILURE);
    }
    tete->nombre=n;
    tete->suivant=NULL;
    maPile->premier=tete;

    return maPile;
}

void emplier (Pile* pile,int NvNombre)
{
    Element*nouveau = malloc(sizeof(*nouveau));
    if ( (pile=NULL) || (nouveau = NULL ))
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nombre=NvNombre;
    nouveau->suivant=pile->premier;
    pile->premier=nouveau;
}

int depiler (Pile* pile) 
{
    if (pile==NULL)
    {
        exit(EXIT_FAILURE);
    }
    int NombreDepile=0;
    Element*elementDepile = pile->premier;
    if((pile!=NULL)&&(pile->premier!=NULL))
    {
    // dabord on recupere le nombre de l'element a depiler
    NombreDepile=elementDepile->nombre;

    //pointer le pointeur premier vers l'element suivant a depiler ( recevoir l'adresse de l'enlement suivant a depiler )
    pile->premier=elementDepile->suivant;

    //supprimer l'element a depiler en utilisant le FREE
    free(elementDepile);
    }
  
  return NombreDepile;
}

int pileVide(Pile *pile)
{
    return (pile == NULL);
}

void afficherPile (Pile* pile)
{
    if (pile==NULL)
    {
        printf("pile vide...\n");
        exit(EXIT_FAILURE);
    }
    Element*actuel=pile->premier;
    while (actuel!=NULL)
    {
        printf("%d\n",actuel->nombre);
        actuel=actuel->suivant;
    }
    printf("\n");
}

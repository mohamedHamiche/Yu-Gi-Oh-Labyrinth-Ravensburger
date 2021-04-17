#include <stdlib.h>
#include <stdio.h>
#include "player.h"

Node *createNode(CORD pos)
{
    Node *r=malloc(sizeof(Node *));
    if(r == NULL)
    {
        exit(EXIT_FAILURE);
    }
    r->a.x = pos.x;
    r->a.y = pos.y;
    r->g=NULL;
    r->d=NULL;
    r->h=NULL;
    r->b=NULL;
    return r;
}

void freeTree(Node *r)
{
    if(r == NULL)
        return;
    printf("free de r->a = %d, %d \n",r->a.x, r->a.y );
    if(r->g && r->g->d != r)
        freeTree(r->g);

    if(r->d && r->d->g != r)
        freeTree(r->d);

    if(r->h && r->h->b != r)
        freeTree(r->h);

    if(r->b && r->b->h != r)
        freeTree(r->b);

    free(r);
}

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

void empiler (Pile* pile,int NvNombre)
{
    Element*nouveau = malloc(sizeof(*nouveau));
    if ( (pile==NULL) || (nouveau == NULL ))
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
    return (pile->premier == NULL);
}

void afficherPile (Pile* pile)
{
    if (pile==NULL)
    {        
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

void freePile(Pile *pile)
{
    if (pile==NULL)
    {        
        exit(EXIT_FAILURE);
    }
    while(!pileVide(pile))
    {
        depiler(pile);
    }
    free(pile->premier);    
}
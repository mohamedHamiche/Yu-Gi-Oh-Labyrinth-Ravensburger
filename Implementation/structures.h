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
    int tresor; //0 si pas de trésor, n sinon avec  1<= n <=24
    int gauche, droite, haut, bas;  //0 si mur, 1 si ouverture
    int posee; //si la tuile est posée ou pas sur le  plateau
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


void Emplier (Pile* pile,int NvNombre)
{
    Element*nouveau = malloc(sizeof(*nouveau));
    if ( (pile==NULL) || (nouveau ==NULL ))
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

//------------------------------------

char *lirePseudo(unsigned int numJoueur)
{
    char *pseudo= malloc(25*sizeof(char));
    printf("Donnez le pseudo du joueur %d :\n",numJoueur);
    scanf(" %[^\n]s\n",pseudo);
    return pseudo;
}

#endif // PILE_H_INCLUDED


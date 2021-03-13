#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED


struct coordonnees
{
	unsigned int x;
	unsigned int y;
};
typedef struct coordonnees CORD;

struct tuile
{
	int fixe ;// 1 fixe 0 couloir
	int tresor; //0 si pas de trésor, n sinon avec  1<= n <=24
	int gauche, droite, haut, bas;  //0 si mur, 1 si ouverture
	int posee; //si la tuile est posée ou pas sur le  plateau
};
typedef struct tuile TUILE;

TUILE Plateau [7][7]; // Matrice de tuiles





typedef struct pile PILE;

struct pile{
    int tab[50];
    int taille;
    int sommet;
};

int pile_vide(PILE p){
    if(p.sommet==0){
        return 1;
    }else{
        return 0;
    }
}

int pile_pleine(PILE p){
    return p.sommet==p.taille;
}

void empiler(PILE *p, int x){
    p->tab[p->sommet]=x;
    p->sommet++;
}

int depiler(PILE *p){
    p->sommet--;
    return p->tab[p->sommet];
}
struct joueur
{
	char *pseudo;
	CORD postion_actuelle;
	PILE pile_tresor;
	int nombre_de_points;
};
typedef struct joueur JOUEUR; 
//-------------------
#endif // PILE_H_INCLUDED

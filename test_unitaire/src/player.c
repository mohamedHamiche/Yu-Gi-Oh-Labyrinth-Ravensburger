#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"

 

char *lirePseudo(unsigned int numJoueur)
{
	char *pseudo= malloc(25*sizeof(char));
	printf("Donnez le pseudo du joueur %d :\n",numJoueur+1);
	scanf(" %s",pseudo);
	return pseudo;
}

void printPlayers(JOUEUR **tabJoueur, unsigned int nbTotal)
{
	for (int i = 0; i < nbTotal; ++i)
	{
		printf("Joueur %d : %s\n",i+1, tabJoueur[i]->pseudo);
		printf("\tPosition : ( %d , %d ) \n", tabJoueur[i]->postion_actuelle.x, tabJoueur[i]->postion_actuelle.y);
		//printf("Prochain trésor : %d\n",tabJoueur[i]->pile_tresor.premier->nombre);
		printf("\tNombre de points : %d\n",tabJoueur[i]->nombre_de_points);
	}
}

JOUEUR **initTabJoueur(unsigned int *nombreTotal)
{
  JOUEUR **tabJoueurs=(JOUEUR **)malloc(4*sizeof(JOUEUR *));
  if(tabJoueurs==NULL)
                {
                  printf("erreur :tabJoueurs initJoueur malloc\n");
                  exit(1);
                }
    unsigned int nombreMachines;
    unsigned int nombreHumains;
  printf("Donner le nombre de machines\n");
  scanf(" %d",&nombreMachines);
  printf("Donner le nombre des Humains\n");
  scanf(" %d",&nombreHumains);
  *nombreTotal= nombreMachines+nombreHumains;
  //printf("nombre total %d\n",*nombreTotal );
  int index=0;
  if(*nombreTotal <=4 && *nombreTotal >1)
  {
    
            while(index<nombreMachines)
            {                
                tabJoueurs[index]=initJoueurM(index);
                index++;
            }

            while(index<(*nombreTotal))
            {                
                tabJoueurs[index]=initJoueurH(index);               
                index++;
            }   
  } 
  else
  {
  	printf("un peu de concentration svp\n"); 
  	exit(1);
  }   

  initPositions(tabJoueurs,*nombreTotal);

    
  return tabJoueurs;
}

JOUEUR *initJoueurM(int index)
{//allocation de JOUEUR et initialisation du pseudo et type machine
   JOUEUR *tmplayer=NULL;
   tmplayer=(JOUEUR *)malloc(sizeof(JOUEUR));
    if(tmplayer==NULL)
    {
       printf("erreur : initJoueurM malloc\n");
       exit(1);
    }
   tmplayer->machine=1;
   char tmpseudo[]="Machine  ";  
   tmpseudo[8]=index+1+'0';  
   char *chaine=malloc(10*sizeof(char));
   if(chaine==NULL)
   {
    printf("Erreur initJoueurM : malloc \n");
    exit(1);
   }
   strcpy(chaine,tmpseudo);
   tmplayer->pseudo=chaine;
   tmplayer->nombre_de_points=0;
   tmplayer->pile_tresor=NULL;
   //printf("init jm pseudo %s**\n", tmplayer->pseudo);
 return tmplayer;                        
}


JOUEUR *initJoueurH(int index)
{//allocation de JOUEUR et initialisation du pseudo et type humain
    JOUEUR *tmplayer=NULL;
    tmplayer=(JOUEUR *)malloc(sizeof(JOUEUR));
    if(tmplayer==NULL)
     {
        printf("erreur : initJoueur malloc\n");
        exit(1);
     }
    tmplayer->machine=0;                  
    tmplayer->pseudo= lirePseudo(index);
    tmplayer->nombre_de_points=0;
    tmplayer->pile_tresor=NULL;
    //printf("initJoueurH pseudo %s--\n",tmplayer->pseudo );
  return tmplayer;
}                            

void initPositions(JOUEUR **tabJoueurs,int nombreTotal)
   {

     //parcourir tabJoueurs et initialiser       
        if(tabJoueurs[0]==NULL)
        {
          printf("erreur initPositions : entree NULL\n");
          exit(1);
        }
        //joueur 1 à 0,0
        tabJoueurs[0]->postion_actuelle.x=0;
        tabJoueurs[0]->postion_actuelle.y=0;
        if(tabJoueurs[1]==NULL)
        {
          printf("erreur initPositions : entree NULL\n");
          exit(1);
        }
        //joueur 2 à 6,6      
        tabJoueurs[1]->postion_actuelle.x=6;
        tabJoueurs[1]->postion_actuelle.y=6;
        //joueur 3 éventuel à 0,6
        if(nombreTotal>=3)
          {
            if(tabJoueurs[2]==NULL)
            {
              printf("erreur initPositions : entree NULL\n");
              exit(1);
            }
            tabJoueurs[2]->postion_actuelle.x=0;
            tabJoueurs[2]->postion_actuelle.y=6;
          }
        //joueur 4 éventuel à 6,0  
        if(nombreTotal>=4)
           {
            if(tabJoueurs[3]==NULL)
            {
              printf("erreur initPositions : entree NULL\n");
              exit(1);
            }
            tabJoueurs[3]->postion_actuelle.x=6;
            tabJoueurs[3]->postion_actuelle.y=0;
          }   
   }


void freeJoueur(JOUEUR *Player)
{
 
  free(Player->pseudo);
  
  free(Player);
}

void freeTabJoueur(JOUEUR **Tab)
{
  for (int i = 0; i < 4; ++i)
  {
    if(Tab[i]!=NULL)
    {
      freeJoueur(Tab[i]);
    }
  }
  free(Tab);
}


void distribuerCartes(JOUEUR **tabJoueur, unsigned int nbTotal)
{
   int i=0;
   int j=0;
   int tabTresor[24];   
    while(i < 24) 
    {
        //remplir aléatoirement avec un entier entre 1 et 24
        tabTresor[i] = rand() % 24 + 1;
        
        j=0;
        while (j < i) // verifie si la valeur entrée n'est pas égale à une valeur déja entré auparavant dans le tableau   
           {             //de sorte à ce que la pile ne contienne pas les mêmes trésors.
            if(tabTresor[i] != tabTresor[j])
                 j++;   
            }
        if(i==j)
            i++;    

    }

    //initialiser la pile des deux joueurs à leur position de départ 
    for (i=0; i<nbTotal; i++)
        tabJoueur[i]->pile_tresor=initPile(24+i);
    

    //remplir la pile des joueurs avec le tableau[24] de valeur aléatoire comprises entre 1 et 24

    //-------- nbTotal de joueurs  
    int depart=0;
    int arrivee=24/nbTotal;
    for (i=0; i<nbTotal; i++)
    {
            for(j=depart; j<arrivee; j++)
                empiler(tabJoueur[i]->pile_tresor,tabTresor[j]);              

            depart+=(24/nbTotal);
            arrivee+=(24/nbTotal);
    }
}
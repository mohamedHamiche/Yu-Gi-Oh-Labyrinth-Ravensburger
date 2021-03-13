#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h" 
#include "fonctions.h"

JOUEUR *initJoueurH(int index);
JOUEUR *initJoueurM(int index);

JOUEUR **initTabJoueur(int nombreTotal);

//---------
int main(void){
  printf("Hello World\n");
  
  return 0;
}
//-----------

JOUEUR **initTabJoueur(int nombreTotal)
{
  JOUEUR **tabJoueurs=(JOUEUR **)malloc(4*sizeof(JOUEUR *));
  if(tabJoueurs==NULL)
                {
                  printf("erreur :tabJoueurs initJoueur malloc\n");
                  exit(1);
                }
    unsigned int nombreMachines;
    unsigned int nombreHumains;
  printf("donner le nombre de machines\n");
  scanf("%d",&nombreMachines);
  printf("donner le nombre des Humains\n");
  scanf("%d",&nombreHumains);
  nombreTotal= nombreMachines+nombreHumains;
  int index=0;
  if(nombreTotal <=4 && nombreTotal >0)
  {
    
            while(index<nombreMachines)
            {                
                tabJoueurs[index]=initJoueurM(index);
                index++;
            }
            while(index<nombreTotal)
            {                
                tabJoueurs[index]=initJoueurH(index);;                
                index++;
            }   
  } 
    //parcourir tabJoueurs et initialiser 
        //joueur 1 à 0,0
        tabJoueurs[0]->postion_actuelle.x=0;
        tabJoueurs[0]->postion_actuelle.y=0;
        //joueur 2 à 6,6
        tabJoueurs[1]->postion_actuelle.x=6;
        tabJoueurs[1]->postion_actuelle.y=6;
        //joueur 3 éventuel à 0,6
        if(nombreTotal>=2)
          {
            tabJoueurs[2]->postion_actuelle.x=0;
            tabJoueurs[2]->postion_actuelle.y=6;
          }
        //joueur 4 éventuel à 6,0  
        if(nombreTotal>=3)
           {
            tabJoueurs[3]->postion_actuelle.x=6;
            tabJoueurs[3]->postion_actuelle.y=0;
          }   
    
  return tabJoueurs;
}

JOUEUR *initJoueurM(int index)
{
  JOUEUR *tmplayer=NULL;
   tmplayer=(JOUEUR *)malloc(sizeof(JOUEUR));
    if(tmplayer==NULL)
    {
       printf("erreur : initJoueurM malloc\n");
       exit(1);
    }
   tmplayer->machine=1;
   char tmpseudo[25]="Machine\0";
   tmpseudo[7]=' ';
   tmpseudo[8]=index;
   tmpseudo[9]='\0';
   tmplayer->pseudo=tmpseudo;
 return tmplayer;                        
}



JOUEUR *initJoueurH(int index)
{
JOUEUR *tmplayer=NULL;
                tmplayer=(JOUEUR *)malloc(sizeof(JOUEUR));
                if(tmplayer==NULL)
                {
                  printf("erreur : initJoueur malloc\n");
                  exit(1);
                }
                tmplayer->machine=0;
                
                tmplayer->pseudo= lire_pseudo(index);    
return tmplayer;
}                            

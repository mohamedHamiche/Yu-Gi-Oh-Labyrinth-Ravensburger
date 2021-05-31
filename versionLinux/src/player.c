#include "player.h"
#include "plateau.h"


char *lirePseudo( int numJoueur)
{
	char *pseudo= malloc(25*sizeof(char));
	printf("Donnez le pseudo du joueur %d :\n",numJoueur);
	scanf(" %s",pseudo);
	return pseudo;
}

void printPlayers(JOUEUR **tabJoueur, int nbTotal)
{
	for (int i = 0; i < nbTotal; ++i)
	{
		printf("Joueur %d : %s\n",i+1, tabJoueur[i]->pseudo);
		printf("\tPosition : ( %d , %d ) \n", tabJoueur[i]->postion_actuelle.x, tabJoueur[i]->postion_actuelle.y);		
		printf("\tNombre de points : %d\n",tabJoueur[i]->nombre_de_points);
	}
}

JOUEUR **initTabJoueur(int *nombreTotal)
{
  JOUEUR **tabJoueurs=(JOUEUR **)malloc(4*sizeof(JOUEUR *));
  if(tabJoueurs==NULL)
    {
        printf("erreur :tabJoueurs initJoueur malloc\n");
        exit(1);
    }
  
   int nombreMachines;
   int nombreHumains;
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
                tabJoueurs[index]=initJoueurM(index+1);
                index++;
            }

            while(index<(*nombreTotal))
            {                
                tabJoueurs[index]=initJoueurH(index+1);               
                index++;
            }   
    } 
    else
    {
    	printf("un peu de concentration svp\n"); 
    	exit(1);
    }   
    if(*nombreTotal == 2)
      {
        free(tabJoueurs[2]);
        free(tabJoueurs[3]);
      }
     
    if(*nombreTotal == 3)
      free(tabJoueurs[3]);


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
   tmpseudo[8]=index+'0';  
   char *chaine=malloc(10*sizeof(char));
   if(chaine==NULL)
   {
    printf("Erreur initJoueurM : malloc \n");
    exit(1);
   }
   strcpy(chaine,tmpseudo);

   tmplayer->machine=1;
   tmplayer->pseudo=chaine;
   tmplayer->nombre_de_points=0;
   for (int i = 0; i <= 12; ++i)
    {
      tmplayer->pile_tresor[i]=0;      
    }
   
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
    for (int i = 0; i <= 12; ++i)
    {
      tmplayer->pile_tresor[i]=0;      
    }
    
    
  return tmplayer;
}                            

void initPositions(JOUEUR **tabJoueurs, int nombreTotal)
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
        //joueur 2 à 0,6      
        tabJoueurs[1]->postion_actuelle.x=0;
        tabJoueurs[1]->postion_actuelle.y=6;
        //joueur 3 éventuel à 6,6
        if(nombreTotal>=3)
          {
            if(tabJoueurs[2]==NULL)
            {
              printf("erreur initPositions : entree NULL\n");
              exit(1);
            }
            tabJoueurs[2]->postion_actuelle.x=6;
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
  //if(Player->pile_tresor != NULL)
    //freePile(Player->pile_tresor);
  free(Player->imgTresors);
  free(Player->textureTresors);
  free(Player);
}

void freeTabJoueur(JOUEUR **Tab, int nombreTotal)
{
  for (int i = 0; i < nombreTotal; ++i)
  {    
      freeJoueur(Tab[i]);    
  }
  free(Tab);
}

int appartientTab(int tab[24], int x)
{
  for (int i = 0; i < 24; ++i)
  {
    if(x==tab[i])
      return 1;
  }
  return 0;
}

void randomTresors(int tabTresor[24])
{
   int i=0;
   int tmp=-1; 
    while(i < 24) 
    {
        //remplir aléatoirement avec un entier entre 1 et 24
        tmp = rand() % 24 + 1;
        if(!appartientTab(tabTresor,tmp))
          {
            tabTresor[i]=tmp;
            i++;
          }        
    }
}

void distribuerCartes(JOUEUR **tabJoueur, int nbTotal)
{
  //remplir aléatoirement avec un entier entre 1 et 24
  int tabTresor[24]={-1};
  randomTresors(tabTresor);

  int i=0,j=0;
   
    for (i=0; i<nbTotal; i++)
    {
       //initialiser la pile des deux joueurs à leur position de départ 
      tabJoueur[i]->pile_tresor[24/nbTotal +1]=(24+i+1);
      //allocation des surfaces et textures 
        tabJoueur[i]->imgTresors =(SDL_Surface **) malloc( ((24/nbTotal)+1) * sizeof(SDL_Surface *) );
        tabJoueur[i]->textureTresors =(SDL_Texture **) malloc( ((24/nbTotal)+1) * sizeof(SDL_Texture *) );
        if(tabJoueur[i]->imgTresors == NULL)
          {
            printf("Erreur distribuerCartes malloc\n");
            exit(1);
          }
          
        
    }
    

    //remplir la pile des joueurs avec le tableau[24] de valeur aléatoire comprises entre 1 et 24

    //-------- nbTotal de joueurs  
    int depart=0;
    int arrivee=24/nbTotal;
    char bmpName[]= "img/T/TA.bmp";
    for (i=0; i<nbTotal; i++)
    {
      int k=0;
            for(j=depart; j<=arrivee; j++)
            {
               if(j < arrivee)
               {
                tabJoueur[i]->pile_tresor[k]= tabTresor[j];
               }               
               
               if(j == arrivee)
               {
                bmpName[6]='D';
                bmpName[7]='A'+i;
               }
               else{
                bmpName[6]='T';
                bmpName[7]='A'+tabTresor[j]-1;
               }
               tabJoueur[i]->imgTresors[k]= SDL_LoadBMP(bmpName);
               if(tabJoueur[i]->imgTresors[k] == NULL)
               {
                SDL_ExitWithError("erreur chargement images");
               }
               //printf("%d chargement de %s\n",j,bmpName );
               k++;                              
            }

            depart+=(24/nbTotal);
            arrivee+=(24/nbTotal);
    }
}

void createTexturesCartes(JOUEUR **tabJoueur, int nbTotal, SDL_Renderer *renderer)
{
  for (int i=0; i<nbTotal; i++)
    {
       for (int k = 0; k <= (24/nbTotal); k++)
       {
         tabJoueur[i]->textureTresors[k] = SDL_CreateTextureFromSurface(renderer, tabJoueur[i]->imgTresors[k]);
          SDL_FreeSurface(tabJoueur[i]->imgTresors[k]);
          if(tabJoueur[i]->textureTresors[k]  == NULL)
          {
              SDL_ExitWithError("Impossible de creer la texture de tabJoueur[i]->textureTresors[k]");
          }       
        //  printf("texture %d du joueur %s cree\n",k , tabJoueur[i]->pseudo);
       }    
    }     
}

void initRectanglesCartes(JOUEUR **tabJoueur, int nbTotal)
{
  if(tabJoueur[0])
  {
    tabJoueur[0]->tresorRect.x= 40;
    tabJoueur[0]->tresorRect.y= 40;
    tabJoueur[0]->tresorRect.h= 100;
    tabJoueur[0]->tresorRect.w= 66;

    tabJoueur[0]->pionRectCoin.x= 40+66+12;
    tabJoueur[0]->pionRectCoin.y= 40+38;
    tabJoueur[0]->pionRectCoin.h= 25;
    tabJoueur[0]->pionRectCoin.w= 25;
  }
  if(tabJoueur[1])
  {
    tabJoueur[1]->tresorRect.x= WINDOW_WIDTH - 40-66;
    tabJoueur[1]->tresorRect.y= 40;
    tabJoueur[1]->tresorRect.h= 100;
    tabJoueur[1]->tresorRect.w= 66;

    tabJoueur[1]->pionRectCoin.x= WINDOW_WIDTH - 40-66 -45;
    tabJoueur[1]->pionRectCoin.y= 40 + 38;
    tabJoueur[1]->pionRectCoin.h= 25;
    tabJoueur[1]->pionRectCoin.w= 25;
  }
  if(tabJoueur[2] && nbTotal >= 3)
  {
    tabJoueur[2]->tresorRect.x= WINDOW_WIDTH - 40-66;
    tabJoueur[2]->tresorRect.y= WINDOW_HEIGHT - 40-100;
    tabJoueur[2]->tresorRect.h= 100;
    tabJoueur[2]->tresorRect.w= 66;

    tabJoueur[2]->pionRectCoin.x= WINDOW_WIDTH - 40-66 -45;
    tabJoueur[2]->pionRectCoin.y= WINDOW_HEIGHT - 40-100 +25;
    tabJoueur[2]->pionRectCoin.h= 25;
    tabJoueur[2]->pionRectCoin.w= 25;
  }
  if(tabJoueur[3] && nbTotal == 4)
  {
    tabJoueur[3]->tresorRect.x= 40;
    tabJoueur[3]->tresorRect.y= WINDOW_HEIGHT - 40-100;
    tabJoueur[3]->tresorRect.h= 100;
    tabJoueur[3]->tresorRect.w= 66;

    tabJoueur[3]->pionRectCoin.x= 40+66+10;
    tabJoueur[3]->pionRectCoin.y= WINDOW_HEIGHT - 40-100 +25;
    tabJoueur[3]->pionRectCoin.h= 25;
    tabJoueur[3]->pionRectCoin.w= 25;
  }
  
}

//fonction qui retourne le choix du couloir par la machine !! 
//on l'a pas utilisé car on n'a pas mis au point le deplacement d'un pion pour le cas de la machine

void getChoixCouloirMachine(CORD *choixCase,CORD choixPrecedent,JOUEUR joueurActuel, TUILE plateau[7][7], int *nbTours, CORD * cordTresor)
{  
  CORD choix;
  TUILE tuileEnMain;
  int valide =0;
  int trouvee = 0;
  
  //recherche du tresor :
  for (int i = 0; i < 7 && !trouvee; ++i)
   {
     for (int j = 0; j < 7 && !trouvee; ++j)
     {
      printf("tresor recherche : %d -- trouve : %d\n",joueurActuel.pile_tresor[joueurActuel.nombre_de_points],plateau[i][j].tresor );
      printf("cord (%d, %d)\n",i,j );
       if(plateau[i][j].tresor == joueurActuel.pile_tresor[joueurActuel.nombre_de_points])
        {
          cordTresor->x=i;
          cordTresor->y=j;
          trouvee=1;          
        }
   } 
 }
   if(cordTresor->x == -1 || cordTresor->y == -1)
   {
    printf("Erreur getChoixCouloirMachine cordTresor non trouvee\n");
    exit(1);
   }
    trouvee = 0;
   int i=0,j=0;
   CORD choixOppose;
  choixOppose.x=-1;
  choixOppose.y=-1; 
  while(i<7 && trouvee == 0)
  {
    j=0;
    while(j<7 && trouvee == 0)
    {
      choix.x=i;
      choix.y=j;
      if(validationCouloir(&choix, &choixPrecedent) ==1)
      {
        for(int t=0; t<4 ; t++)
        {

          tuileEnMain = decalerCouloir(plateau, choix,tuileEnMain);
          printf("j'ai decale choix %d %d\n",choix.x, choix.y );
          validationCoup(plateau,joueurActuel.postion_actuelle, *cordTresor,&valide);
          if (valide == 1)
          {
            choixCase->x= i;
            choixCase->y= j;
            *nbTours=t;  
            trouvee = 1;
          }
          //trouver l'oppose
          for (int k = 0; k < 7 &&(!oppose(choixOppose, choix)); ++k)
          {
            for (int p = 0; p < 7 && (!oppose(choixOppose, choix)); ++p)
            {
              choixOppose.x=k;
              choixOppose.y=p;                                    
            }
          }
          //recaler
          tuileEnMain= decalerCouloir(plateau, choixOppose, tuileEnMain);
          tournerTuile(&tuileEnMain);
        }
        
        
      }
      j++;
    }
    i++;
  }

  if(trouvee == 0)
  {
    choixCase->x= 0;
    choixCase->y= 5;
  }
  printf("trouvee = %d\n",trouvee );
}

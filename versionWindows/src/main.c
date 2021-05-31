#include "plateau.h"
#include "player.h"

//Pour le test: le jeu marche bien avec 3 ou 4 joueurs, il reste des problèmes à regler pour 2 joueurs
//exemple 2 machines 1 humain : abcd
//les machines ne marchent, on va jouer à leur place


int main(int argc, char *argv[]){


	srand(time(NULL));
    
    int nbTotal=0;      
    JOUEUR **tabJoueur= initTabJoueur(&nbTotal);
    initPositions(tabJoueur,nbTotal);
	//----------------------------------  initialisation de la fenetre window
    SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;


	if(SDL_Init(SDL_INIT_VIDEO) != 0)	
		SDL_ExitWithError("Erreur SDL_Init "); 
	
	window = SDL_CreateWindow("Labyrinthe Ravensburger Yu Gi Oh", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
	if(window == NULL)
		SDL_ExitWithError("Erreur SDL_CreateWindow"); 

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
	if(renderer == NULL)
	{
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Erreur SDL_CreateRenderer");
	}

	if(SDL_SetRenderDrawColor(renderer,0, 0, 0, 255) != 0)
		SDL_ExitWithErrorAndDestroy("Impossible de changer la couleur",window, renderer);
	
	SDL_RenderClear(renderer); 

    //----------------------------------------- distribution des cartes et création du rendu des cartes

    //printPlayers(tabJoueur,nbTotal);
    distribuerCartes(tabJoueur,nbTotal); //distribue et charge les images
    createTexturesCartes(tabJoueur,nbTotal, renderer);
    initRectanglesCartes(tabJoueur,nbTotal);
    
    //----------------------------------------- initialisation du plateau et de la tuile en main
	
	TUILE plateau[7][7];	
   	initPlateau(plateau); // met les champs posee et angle à 0
	tuilesFixes(plateau);      //pose les tuiles fixes dans la matrice plateau

     //etape 1 chargement des images bmp
	chargerImageTuileFixe(plateau, window, renderer);
	TUILE tuileEnMain = tuilesCouloir(plateau); //poser les tuiles couloirs, charge les images des couloirs et renvoie la tuile en main

    //etape 2 creation des textures
    creerTextures(window, renderer, &tuileEnMain, plateau);     //créer les textures des tuiles du plateau et tuile en main
 	
    //etape 3 creation des rectangles  
    SDL_Rect tuileEnMainRect;
    SDL_Rect caseSdl[7][7];
    initRectangles(&tuileEnMainRect, caseSdl);

    //----------- on a un plateau qui s'affiche avec la tuile en main

    //-------------------------- images des pions pour chaque joueur 
    char bmpName[] ="img/P1.bmp";
    for (int i = 0; i < nbTotal; ++i)
    {
        bmpName[5]='1'+i;
        tabJoueur[i]->image=NULL;
        tabJoueur[i]->image=SDL_LoadBMP(bmpName);
        if(tabJoueur[i]->image == NULL)
            SDL_ExitWithErrorAndDestroy("Impossible de charger les pions bmp",window, renderer); 
       
        tabJoueur[i]->texture=NULL;
        tabJoueur[i]->texture=SDL_CreateTextureFromSurface(renderer, tabJoueur[i]->image);
        SDL_FreeSurface(tabJoueur[i]->image);
        if(tabJoueur[i]->texture == NULL)
        {
            SDL_ExitWithError("Impossible de creer la texture de tuile en main");
        }       
       
    }    

    //initialistion des rectangles
    initRectPions(tabJoueur, nbTotal);  

    //------------------------------------------------ GAME LOOP


    SDL_RendererFlip flip = SDL_FLIP_NONE;
   //les choix des couloirs
    CORD choix, choixPrecedent;
    choix.x =-1;
    choix.y =-1;
    choixPrecedent.x=-1;
    choixPrecedent.x=-1;

    //de la case où mettre le pion
    CORD choixCase;

    int i=0;
    JOUEUR *joueurActuel= tabJoueur[0];

    //etats: 
    int insertion=1;
    int deplacement = 0;
	int exit=SDL_FALSE;
    int coupValide=0;

	SDL_Event event;	
	while(!exit)
    {     
		while(SDL_PollEvent(&event)) //attend les evenements du clavier et souris
        { 
			switch(event.type)
            {
				case SDL_QUIT:
					exit=SDL_TRUE;
					break;

				case SDL_MOUSEBUTTONDOWN:   

                    //etat d'insertion 
 					if(event.button.button == 1 && insertion){                          
                            choixEvent(event, &tuileEnMainRect,&choix);
                          //renvoie le choix du couloir ou inserer quand on fait un click gauche dessus                    
                    }                    
					if(event.button.button == 3 && insertion){
						tournerTuile(&tuileEnMain);                        					      
                        //si on fait click droit on peut tourner la tuile en main
					}

                    //etape de deplacement du pion si on click gauche
                    if(event.button.button == 1 && deplacement){ 

                            //on recupere les coordonées de la case ciblée
                            getCordClick(event, &choixCase,tabJoueur[i]); 
                                                                                                            
                        //si le coup est valide ?
       					for(int i=0;i<7;i++){
                            for(int j=0; j<7; j++){                           
                                plateau[i][j].parcouru  = 0;
                            }
                        }                    
                        validationCoup(plateau,joueurActuel->postion_actuelle, choixCase,&coupValide);
                        printf("validation : %d\n",coupValide);                        
                        if(coupValide == 1)
                        {
                            //mettre à jour la position du joueur actuel
                        	tabJoueur[i]->postion_actuelle.x=choixCase.x;
	                        tabJoueur[i]->postion_actuelle.y=choixCase.y; 	                                
	                                               
                            //deplacer le rectangle de son pion                                                    
	                        deplacerRect(event,&tabJoueur[i]->pionRect, tabJoueur[i]->postion_actuelle,i);

                            //si la position choisi contient le tresor recherché
	                        if(plateau[tabJoueur[i]->postion_actuelle.x][tabJoueur[i]->postion_actuelle.y].tresor == tabJoueur[i]->pile_tresor[tabJoueur[i]->nombre_de_points])
	                        {
	                        	printf("tresor trouve !!!!!\n");
	                        	tabJoueur[i]->pile_tresor[tabJoueur[i]->nombre_de_points]*= -1;
	                        	tabJoueur[i]->nombre_de_points++;
	                        }
                            //s'il ne reste plus de tresors à trouver on tester si le joueur a pu revenir à sa case de départ
	                        if(tabJoueur[i]->nombre_de_points == (24/nbTotal) +1)
	                        {
	                        	printf("%s a gange la partie\n",tabJoueur[i]->pseudo);
	                        	exit= SDL_TRUE;	                        	
	                        }
	                   
                           //alterner tour on passe au joueur suivant
                            i=(i+1)%nbTotal;
                            joueurActuel=tabJoueur[i];
                            printf("tour du joueur %s : %d points \n",tabJoueur[i]->pseudo, tabJoueur[i]->nombre_de_points);
                            for (int k = 0; k <= 24/nbTotal; ++k)
                            {
                            	printf("%d\n",tabJoueur[i]->pile_tresor[k]);
                            }                        
                            
                               coupValide =0;
                               deplacement=0;
                               insertion =1;
                        }
         
                    }                                            
                       
                //etat d'insertion si le couloir choisi est valide on appuie sur touche du haut pour inserer 
				case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_UP && validationCouloir(&choix, &choixPrecedent) && insertion)
                    {
                        //decaler le couloir est mettre à jour la tuile en main
                        tuileEnMain = decalerCouloir(plateau, choix,tuileEnMain);
                        //on décale aussi tous les pions qui se trouvent sur le meme couloir
                        for (int i = 0; i < nbTotal; ++i)
                        {
                            decalerPion(&tabJoueur[i]->postion_actuelle,choix, &tabJoueur[i]->pionRect);
                        }
                        insertion = 0;
                        deplacement = 1;
                                                          
                    }

				default:                
					break;
			}  
           
			SDL_RenderClear(renderer);
						
		}  
         
   //----------------------------------------- affichage du rendu
        for(int i=0; i<7; i++)
        {
        	for(int j=0; j<7; j++)
        	{
    			 SDL_RenderCopyEx(renderer,plateau[i][j].texture,NULL,&caseSdl[i][j],plateau[i][j].angle,NULL,flip);    			
    		}
    	}
		SDL_RenderCopyEx(renderer,tuileEnMain.texture,NULL,&tuileEnMainRect,tuileEnMain.angle,NULL,flip);
      
        for (int i = 0; i < nbTotal; ++i)
        {
            SDL_RenderCopyEx(renderer, tabJoueur[i]->texture,NULL,&tabJoueur[i]->pionRect,0,NULL,flip);
            SDL_RenderCopyEx(renderer, tabJoueur[i]->textureTresors[tabJoueur[i]->nombre_de_points],NULL,&tabJoueur[i]->tresorRect,0,NULL,flip);
            if(joueurActuel == tabJoueur[i])
            	SDL_RenderCopyEx(renderer, tabJoueur[i]->texture,NULL,&tabJoueur[i]->pionRectCoin,0,NULL,flip);
        }
        
    	SDL_RenderPresent(renderer);

    }

    //------------------------------------------------------
    //destroy and quit
    	for(int i=0; i<7; i++)        
        {
            for(int j=0; j<7; j++)            
    		{               
                if(plateau[i][j].texture != NULL)
                    SDL_DestroyTexture(plateau[i][j].texture);
            }
        }
        for (int i = 0; i < nbTotal; ++i)
        {
        	for (int j = 0; j <= 24/nbTotal; ++j)
        	{
        		SDL_DestroyTexture(tabJoueur[i]->textureTresors[j]);
        	}
        	SDL_DestroyTexture(tabJoueur[i]->texture);
        }
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("SDL_QUIT\n");
    freeTabJoueur(tabJoueur,nbTotal);
	return EXIT_SUCCESS;


}


#include "plateau.h"
#include "player.h"
#include "pile.h"



//Linux
//#include "SDL2/SDL_image.h
//#include <SDL2/SDL_ttf.h>
//sudo apt-get install libsdl2-ttf-dev
//sudo apt-get update && sudo apt-get upgrade
//sudo apt-get install libsdl2-image-dev
//gcc main.c $(sdl2-config --cflags --libs)


int main(int argc, char *argv[]){


	srand(time(NULL));
    
     int nbTotal=0;      
    JOUEUR **tabJoueur= initTabJoueur(&nbTotal);
    initPositions(tabJoueur,nbTotal);
	//----------------------------------  init window
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
	
	SDL_RenderClear(renderer); // pour la fenetre entiere
    //-----------------------------------------

    //printPlayers(tabJoueur,nbTotal);
    distribuerCartes(tabJoueur,nbTotal);
    createTexturesCartes(tabJoueur,nbTotal, renderer);
    /*for (int i = 0; i < nbTotal; ++i)
    {
        printf("tresors de %s\n",tabJoueur[i]->pseudo);
        afficherPile(tabJoueur[i]->pile_tresor);
    }
    
   */
    //----------------------------------------- init plateau
	
	TUILE plateau[7][7];	
   	initPlateau(plateau);
	tuilesFixes(plateau);
	chargerImageTuileFixe(plateau, window, renderer);

	TUILE tuileEnMain = tuilesCouloir(plateau); //rempli les couloirs, charge les images et renvoie la tuile en main

    creerTextures(window, renderer, &tuileEnMain, plateau);
 	
    SDL_Rect tuileEnMainRect;
    SDL_Rect caseSdl[7][7];
    initRectangles(&tuileEnMainRect, caseSdl);

    char bmpName[] ="img/P1.bmp";
    for (int i = 0; i < nbTotal; ++i)
    {
        bmpName[5]='1'+i;
        tabJoueur[i]->image=NULL;
        tabJoueur[i]->image=SDL_LoadBMP(bmpName);
        if(tabJoueur[i]->image == NULL)
            SDL_ExitWithErrorAndDestroy("Impossible de charger les pions bmp",window, renderer); 

        printf("images charges %s \n",bmpName );
        tabJoueur[i]->texture=NULL;
        tabJoueur[i]->texture=SDL_CreateTextureFromSurface(renderer, tabJoueur[i]->image);
        SDL_FreeSurface(tabJoueur[i]->image);
        if(tabJoueur[i]->texture == NULL)
        {
            SDL_ExitWithError("Impossible de creer la texture de tuile en main");
        }       
        printf("tectures crees %s \n",bmpName );
    }
    printf("fin chargement\n");
    //initialistion des rectangles
    initRectPions(tabJoueur, nbTotal);        
    initRectanglesCartes(tabJoueur,nbTotal);
    
    //------------------------------------------------ GAME LOOP


    SDL_RendererFlip flip = SDL_FLIP_NONE;
    CORD choix, choixPrecedent;
    choix.x =-1;
    choix.y =-1;
    choixPrecedent.x=-1;
    choixPrecedent.x=-1;

    CORD choixCase;
    int i=0;
    JOUEUR *joueurActuel= tabJoueur[0];
    //etats: 
    int insertion=1;
    int deplacement = 0;
	int exit=SDL_FALSE;
	SDL_Event event;	

    int temporaire=0;
	while(!exit)
    {
        
		while(SDL_PollEvent(&event))
        { 
			switch(event.type)
            {
				case SDL_QUIT:
					exit=SDL_TRUE;
					break;

				case SDL_MOUSEBUTTONDOWN:         
 					if(event.button.button == 1 && insertion){  
                        choixEvent(event, &tuileEnMainRect,&choix);  
                        //la tuile est rentrée                        
                    }
					if(event.button.button == 3 && insertion){
						tournerTuile(&tuileEnMain);
					      fprintf(stdout,"%d\n",event.button.y); 
					}
                    if(event.button.button == 1 && deplacement){  

                        getCordClick(event, &choixCase,tabJoueur[i]); 
                        //si le coup est valide
       					for(int i=0;i<7;i++){
                            for(int j=0; j<7; j++){                           
                                plateau[i][j].parcouru  = 0;
                            }
                        }
                        int compt=0;
                        validationCoup(plateau,joueurActuel->postion_actuelle, choixCase,&temporaire,joueurActuel->postion_actuelle,&compt);
                        printf("validation : %d\n",temporaire);                        
                        if(temporaire == 1)
                        {
                        	tabJoueur[i]->postion_actuelle.x=choixCase.x;
	                        tabJoueur[i]->postion_actuelle.y=choixCase.y; 
	                        printf("choixCase = %d %d\n",choixCase.x, choixCase.y );          
	                                               
	                        deplacerRect(event,&tabJoueur[i]->pionRect, tabJoueur[i]->postion_actuelle,i);

	                        if(plateau[tabJoueur[i]->postion_actuelle.x][tabJoueur[i]->postion_actuelle.y].tresor == tabJoueur[i]->pile_tresor[tabJoueur[i]->nombre_de_points])
	                        {
	                        	printf("tresor trouve !!!!!\n");
	                        	tabJoueur[i]->pile_tresor[tabJoueur[i]->nombre_de_points]*= -1;
	                        	tabJoueur[i]->nombre_de_points++;
	                        }
	                        if(tabJoueur[i]->nombre_de_points == (24/nbTotal) +1)
	                        {
	                        	printf("%s a gange la partie\n",tabJoueur[i]->pseudo);
	                        	exit= SDL_TRUE;	                        	
	                        }
                        }

                        //alterner tour 
                       // i=(i+1)%nbTotal;
                       // joueurActuel=tabJoueur[i];
                        printf("tour du joueur %s : %d points \n",tabJoueur[i]->pseudo, tabJoueur[i]->nombre_de_points);
                        for (int k = 0; k <= 24/nbTotal; ++k)
                        {
                        	printf("%d\n",tabJoueur[i]->pile_tresor[k]);
                        }                        
                        //afficherPile(tabJoueur[i]->pile_tresor);
                       temporaire =0;
                       deplacement=0;
                       insertion =1;
                       
                    }                                            
                       

				case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_UP && validationCouloir(&choix, &choixPrecedent) && insertion)
                    {
                        tuileEnMain = decalerCouloir(plateau, choix,tuileEnMain);
                        for (int i = 0; i < nbTotal; ++i)
                        {
                            decalerPion(&tabJoueur[i]->postion_actuelle,choix, &tabJoueur[i]->pionRect);
                        }
                        insertion = 0;
                        deplacement = 1;
                        //sortirTuileEnMain(&tuileEnMainRect, i);                                      
                    }

                //case SDL_MOUSEMOTION:
                     //printf("%d ; %d\n",event.motion.x, event.motion.y );
                    printf("case (0,1) : h= %d /d= %d/ b= %d/ g= %d \n",plateau[0][1].h,plateau[0][1].d, plateau[0][1].b,plateau[0][1].g );
				default:
					break;
			}            
			SDL_RenderClear(renderer);
						
		}  
   //----------------------------------------- affiche rendu
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
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("SDL_QUIT\n");
    freeTabJoueur(tabJoueur,nbTotal);
	return EXIT_SUCCESS;


}


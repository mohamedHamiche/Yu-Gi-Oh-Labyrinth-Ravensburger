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
    printPlayers(tabJoueur,nbTotal);
    distribuerCartes(tabJoueur,nbTotal);
    for (int i = 0; i < nbTotal; ++i)
    {
        printf("tresors de %s\n",tabJoueur[i]->pseudo);
        afficherPile(tabJoueur[i]->pile_tresor);
    }
    
    
    
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
    //----------------------------------------- init plateau
	TUILE plateau[7][7];

    for(int i=0; i<7;i++){
        for(int j=0; j<7;j++){
            plateau[i][j].posee =0;
            plateau[i][j].angle =0;
        }
    }
	tuilesFixes(plateau);


    //------------------------------------ chargerImagesFixes
	printf("test\n");

	char Nom[] = "img/a.bmp";
	unsigned int suiv=0;
	for(int i=0 ;i<7; i+=2){
		for(int j=0; j<7; j+=2){
			plateau[i][j].image = SDL_LoadBMP(Nom);
			if(plateau[i][j].image == NULL){
				SDL_ExitWithErrorAndDestroy("Impossible de charger les images",window, renderer);
			}
			Nom[4] = 'a'+suiv+1;
			suiv++;
		}
	}
	printf("test\n");//Tuiles fixes chargées
    //----------------------------------------------

	//------------------------------------------------Charger tuiles couloirs et tuile en main
	TUILE tuileEnMain = tuilesCouloir(plateau); //rempli les couloirs et charge les images
    
    //-----------------------------------------------------creerTextures
    tuileEnMain.texture = SDL_CreateTextureFromSurface(renderer, tuileEnMain.image);
    SDL_FreeSurface(tuileEnMain.image);
    if(tuileEnMain.texture == NULL)
    {
        SDL_ExitWithError("Impossible de creer la texture de tuile en main");
    }
    

        for(int i=0; i<7; i++)
        {  
    		for(int j=0; j<7; j++)
            {    		
    				plateau[i][j].texture=SDL_CreateTextureFromSurface(renderer, plateau[i][j].image);
                    SDL_FreeSurface(plateau[i][j].image);
                    if(plateau[i][j].texture == NULL)                                            
                        SDL_ExitWithErrorAndDestroy("Impossible de creer la textures",window, renderer);                    
            }
        }
    //---------------------------------------------------------------
    			
    printf("test2\n");

    //-------------------------------- init rectangles
    

    SDL_Rect tuileEnMainRect;
    tuileEnMainRect.x=positionX+(8*70);
    tuileEnMainRect.y=positionY+(3.5*70);
    tuileEnMainRect.h =70;
    tuileEnMainRect.w=70;

	// table 2D de Rectangles
    SDL_Rect caseSdl[7][7];

    for(int i=0; i<7; i++){
    	for(int j=0; j<7; j++){
    		caseSdl[i][j].y = positionY+i*70;
    		caseSdl[i][j].x = positionX+j*70;
    		caseSdl[i][j].h = 70;
    		caseSdl[i][j].w = 70;

    	}
    }
    printf("test2\n");
    //------------------------------------------------ GAME LOOP


    SDL_RendererFlip flip = SDL_FLIP_NONE;
    CORD choix;
    choix.x =1;
    choix.y =0;
	int exit=SDL_FALSE;
	SDL_Event event;	
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
 					if(event.button.button == 1){  
                        choixEvent(event, &tuileEnMainRect,&choix);                                        
                    }
					if(event.button.button == 3){
					   tuileEnMain.angle = (tuileEnMain.angle + 90)%360;
                        fprintf(stdout,"%d\n",event.button.y);
 
					}
                    
				case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_UP)
                        tuileEnMain = decalerCouloir(plateau, choix,tuileEnMain);

                //case SDL_MOUSEMOTION:
                     //printf("%d ; %d\n",event.motion.x, event.motion.y );

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


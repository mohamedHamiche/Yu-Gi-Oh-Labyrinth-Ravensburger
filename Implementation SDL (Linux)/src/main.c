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
    for (int i = 0; i < nbTotal; ++i)
    {        
        printf("bonjour\n");
       tabJoueur[i]->pionRect.h = 25;
       tabJoueur[i]->pionRect.w = 25;
       tabJoueur[i]->pionRect.x=0;
       tabJoueur[i]->pionRect.y=0;       
       tabJoueur[i]->pionRect.y=positionY+ tabJoueur[i]->postion_actuelle.x*70 +40;
       tabJoueur[i]->pionRect.x=positionX+ tabJoueur[i]->postion_actuelle.y*70 +10; 
    }
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

        for(int i=0;i<7;i++){
            for(int j=0; j<7; j++){
                /*printf("[%d][%d] -> g: %d\n",i,j,plateau[i][j].g);
                printf("[%d][%d] -> d: %d\n",i,j,plateau[i][j].d);
                printf("[%d][%d] -> h: %d\n",i,j,plateau[i][j].h);
                printf("[%d][%d] -> b: %d\n",i,j,plateau[i][j].b);
                printf("\n");*/
                plateau[i][j].parcouru  = 0;
            }
            printf("\n");
        }
   int temporaire =0;

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
                       tuileEnMain.angle = (tuileEnMain.angle + 90)%360;
                       int tmpH = tuileEnMain.h;
                       int tmpD = tuileEnMain.d;
                       int tmpG = tuileEnMain.g;
                       int tmpB = tuileEnMain.b;
                       tuileEnMain.h = tmpG;
                       tuileEnMain.d = tmpH;
                       tuileEnMain.b = tmpD;
                       tuileEnMain.g = tmpB;

                        fprintf(stdout,"%d\n",event.button.y); 
                    }
                    if(event.button.button == 1 && deplacement){  

                        getCordClick(event, &choixCase,joueurActuel); 
                        //si le coup est valide
                        int compt=0;
                        validationCoup(plateau,joueurActuel->postion_actuelle, choixCase,&temporaire,joueurActuel->postion_actuelle,&compt);
                        printf("validation : %d\n",temporaire);
                        for(int i=0;i<7;i++){
                            for(int j=0; j<7; j++){                           
                                plateau[i][j].parcouru  = 0;
                            }
                        }
                        temporaire =0;
                        joueurActuel->postion_actuelle.x=choixCase.x;
                        joueurActuel->postion_actuelle.y=choixCase.y; 
                        printf("choixCase = %d %d\n",choixCase.x, choixCase.y );

                        deplacerRect(event,&tabJoueur[i]->pionRect, tabJoueur[i]->postion_actuelle,i);
                        
                        
                        //alterner tour 
                        i=(i+1)%nbTotal;
                        joueurActuel=tabJoueur[i];
                        printf("tour du joueur %s \n",tabJoueur[i]->pseudo);
                        afficherPile(tabJoueur[i]->pile_tresor);
                       deplacement=0;
                       insertion =1;
                       
                    }                                            
                       

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_UP)
                    {
                        tuileEnMain = decalerCouloir(plateau, choix,tuileEnMain);
                        for (int i = 0; i < nbTotal; ++i)
                        {
                            decalerPion(&tabJoueur[i]->postion_actuelle,choix, &tabJoueur[i]->pionRect);
                        }
                        insertion = 0;
                        deplacement = 1;
                        //sortirTuileEnMain(&tuileEnMainRect, i);
                        for(int i=0;i<7;i++){
                            for(int j=0; j<7; j++){
                                printf("[%d][%d] -> g: %d\n",i,j,plateau[i][j].g);
                                printf("[%d][%d] -> d: %d\n",i,j,plateau[i][j].d);
                                printf("[%d][%d] -> h: %d\n",i,j,plateau[i][j].h);
                                printf("[%d][%d] -> b: %d\n",i,j,plateau[i][j].b);
                                printf("\n");
                            }
                                    printf("\n");
                                   }

                                         
                    }

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
        
        for (int i = 0; i < nbTotal; ++i)
        {
            SDL_RenderCopyEx(renderer, tabJoueur[i]->texture,NULL,&tabJoueur[i]->pionRect,0,NULL,flip);
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


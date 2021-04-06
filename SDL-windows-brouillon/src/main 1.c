#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>

typedef struct coordonnees CORD;
struct coordonnees
{
    unsigned int x;
    unsigned int y;
};


typedef struct tuile TUILE;
struct tuile
{
    unsigned int angleTuile;
    int id;
    int fixe ;
    int tresor; 
    char type; // I L T
    int g, d, h, b;  
    int posee;
    int angle;

    SDL_Surface *image;
    SDL_Texture *texture;
};
//#include "SDL2/SDL_image.h
//#include <SDL2/SDL_ttf.h>
//sudo apt-get install libsdl2-ttf-dev
//sudo apt-get update && sudo apt-get upgrade
//sudo apt-get install libsdl2-image-dev
//gcc main.c $(sdl2-config --cflags --libs)
void SDL_ExitWithError(const char *message);
void SDL_ExitWithErrorAndDestroy(const char *message,SDL_Window *window,SDL_Renderer *renderer);

void tuilesFixes(TUILE Plateau[7][7]);
void ouvertureRand(unsigned int *g,unsigned int *d,unsigned int *b,unsigned int *h);
TUILE tuilesCouloir(TUILE Plateau[7][7]);
TUILE decalerCouloir(TUILE plateau[7][7], CORD choixCouloir, TUILE tuileEnMain);
void choixEvent(SDL_Event event, SDL_Rect *tuileEnMain, CORD *choix);



int main(int argc, char *argv[]){

	srand(time(NULL));
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;


	if(SDL_Init(SDL_INIT_VIDEO) != 0)	
		SDL_ExitWithError("Erreur SDL_Init "); 
	
	window = SDL_CreateWindow("Labyrinthe Ravensburger Yu Gi Oh", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 940,940,SDL_WINDOW_SHOWN);
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

	TUILE plateau[7][7];

    for(int i=0; i<7;i++){
        for(int j=0; j<7;j++){
            plateau[i][j].posee =0;
            plateau[i][j].angle =0;
        }
    }
	tuilesFixes(plateau);
	printf("test\n");

	char Nom[10] = "img/a.bmp";
	unsigned int suiv=0;
	for(int i=0 ;i<7; i+=2){
		for(int j=0; j<7; j+=2){
			plateau[i][j].image = SDL_LoadBMP(Nom);
			if(plateau[i][j].image == NULL)
				SDL_ExitWithErrorAndDestroy("Impossible de charger les images tuiles fixes",window, renderer);
			
			Nom[4] = 'a'+suiv+1;
			suiv++;
		}
	}
	printf("test\n");//Tuiles fixes chargées

	//Charger tuiles couloirs:
	TUILE tuileEnMain = tuilesCouloir(plateau); //rempli les couloirs et charge les images



    printf("test2\n");


	unsigned int r=0;

	int tmp=0, tFixe=0, k=1;

        for(int i=0; i<7; i++){
    		for(int j=0; j<7; j++){
    		
    				plateau[i][j].texture=SDL_CreateTextureFromSurface(renderer, plateau[i][j].image);
                    SDL_FreeSurface(plateau[i][j].image);                 
                    if(plateau[i][j].texture == NULL)
                    {
                        printf("%d - %d",i,j);
                        SDL_ExitWithErrorAndDestroy("Impossible de creer la textures",window, renderer);
                    }
                }
            }
    			
    printf("test2\n");


    int positionX = 150;
    int positionY = 150; 
    int j=0;


    SDL_Rect tuileEnMainRect;
    tuileEnMainRect.x=520;
    tuileEnMainRect.y=340;
    tuileEnMainRect.h =70;
    tuileEnMainRect.w=70;

	// table 2D de Rectangles
    SDL_Rect caseSdl[7][7];

    for(int i=0; i<7; i++){
    	for(int j=0; j<7; j++){
    		caseSdl[i][j].y = positionX+i*70;
    		caseSdl[i][j].x = positionY+j*70;
    		caseSdl[i][j].h = 70;
    		caseSdl[i][j].w = 70;

    	}
    }
    printf("test2\n");



SDL_RendererFlip flip = SDL_FLIP_NONE;
    CORD choix;
    TUILE tuileM;
    choix.x =1;
    choix.y =0;
	int exit=1;
	SDL_Event event;	
	unsigned int i=0, test=0;



    printf("test2\n");
	while(exit){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					exit=0;
					break;
				case SDL_MOUSEBUTTONDOWN:         
 					if(event.button.button == 1){  
                        choixEvent(event, &tuileEnMainRect,&choix);                 

                    }
					if(event.button.button == 3){
					   tuileEnMain.angle = (tuileEnMain.angle + 90)%360;
                        fprintf(stdout,"%d\n",event.button.y);

					}
                    if(event.button.button == 2){
                       tuileEnMain = decalerCouloir(plateau, choix,tuileEnMain);
                    }
					
					       
				default:
					break;
			}
			SDL_RenderClear(renderer);
				
		
		}
       

       r=0;
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


	for(int i=0; i<7; i++){
    	for(int j=0; j<7; j++){
			SDL_DestroyTexture(plateau[i][j].texture);
			SDL_FreeSurface(plateau[i][j].image);		
		}
	}
	


	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;


}

void SDL_ExitWithError(const char *message)
{
	SDL_Log("ERREUR : %s > %s\n",message, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void SDL_ExitWithErrorAndDestroy(const char *message, SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);	
	SDL_DestroyWindow(window);
	SDL_Log("ERREUR : %s > %s\n",message, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}


//Testé avec des entiers au lieu des tuiles, qui ne sont pas encore initialisées dans le programme
 

TUILE decalerCouloir(TUILE plateau[7][7], CORD choixCouloir, TUILE tuileEnMain){

    TUILE tmp,dec;
    unsigned int i = 0;
    if(choixCouloir.x == 0 || choixCouloir.x == 6){

        if(choixCouloir.x == 0){
            tmp = plateau[choixCouloir.x][choixCouloir.y];
            plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
            dec = plateau[choixCouloir.x+1][choixCouloir.y];
            plateau[choixCouloir.x+1][choixCouloir.y] = tmp;
            tmp=dec;
            for(i=1; i<6; i++){
                dec =plateau[i+1][choixCouloir.y];
                plateau[i+1][choixCouloir.y] = tmp;
                tmp = dec;
            }
        }
          
        if(choixCouloir.x == 6){
            tmp = plateau[choixCouloir.x][choixCouloir.y];
            plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
            for(i=6; i>0; i--){
                dec = plateau[i-1][choixCouloir.y];
                plateau[i-1][choixCouloir.y] = tmp;
                tmp = dec;
            }
        } 
    }
    
    else if(choixCouloir.y == 0 || choixCouloir.y == 6){

            if(choixCouloir.y == 0){
                tmp = plateau[choixCouloir.x][choixCouloir.y];
                plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
                dec = plateau[choixCouloir.x][choixCouloir.y+1];
                plateau[choixCouloir.x][choixCouloir.y+1] = tmp;
                tmp=dec;
                for(i=1; i<6; i++){
                    dec = plateau[choixCouloir.x][i+1];
                    plateau[choixCouloir.x][i+1] = tmp;
                    tmp = dec;
                }
            }
        
            if(choixCouloir.y == 6){
                tmp = plateau[choixCouloir.x][choixCouloir.y];
                plateau[choixCouloir.x][choixCouloir.y] = tuileEnMain;
                    for(i=6; i>0; i--){
                        dec = plateau[choixCouloir.x][i-1];
                        plateau[choixCouloir.x][i-1] = tmp;
                        tmp = dec;
                    }
            }
        }

    return tmp; // nouvelle tuileEnMain
}


void choixEvent(SDL_Event event, SDL_Rect *tuileEnMain, CORD *choix){
    //NORD
                        if(event.button.x > 219 &&  event.button.x < 290 && event.button.y > 79 && event.button.y < 150){
                            (tuileEnMain->x) = 220;
                            (tuileEnMain->y) = 80;
                            (choix->x) = 1;
                           (choix->y) = 0;
                        }
                        if(event.button.x > 359 &&  event.button.x < 430 && event.button.y > 79 && event.button.y < 150){
                            (tuileEnMain->x) = 360;
                           (tuileEnMain->y) = 80;
                           (choix->x) = 3;
                            (choix->y) = 0;
                        }
                        if(event.button.x > 499 &&  event.button.x < 570 && event.button.y > 79 && event.button.y < 150){
                            (tuileEnMain->x) = 500;
                            (tuileEnMain->y) = 80;
                            (choix->x) = 5;
                            (choix->y) = 0;
                        }

                       //EST

                        if(event.button.x > 639 &&  event.button.x < 710 && event.button.y > 219 && event.button.y < 290){
                            (tuileEnMain->x) = 640;
                            (tuileEnMain->y) = 220;
                            (choix->x) = 6;
                            (choix->y) = 1;
                        }
                        if(event.button.x > 639 &&  event.button.x < 710 && event.button.y > 359 && event.button.y < 430){
                            (tuileEnMain->x) = 640;
                            (tuileEnMain->y) = 360;
                            (choix->x)= 6;
                            (choix->y) = 3;
                        }

                          if(event.button.x > 639 &&  event.button.x < 710 && event.button.y > 499 && event.button.y < 570){
                            (tuileEnMain->x) = 640;
                            (tuileEnMain->y) = 500;
                            (choix->x)= 6;
                            (choix->y) = 5;
                        }

                        //SUD
                        if(event.button.x > 219 &&  event.button.x < 290 && event.button.y > 640 && event.button.y < 710){
                            (tuileEnMain->x) = 220;
                            (tuileEnMain->y) = 640;
                            (choix->x) = 1;
                            (choix->y) = 6;
                        }
                        if(event.button.x > 359 &&  event.button.x < 430 && event.button.y > 640 && event.button.y < 710){
                            (tuileEnMain->x) = 360;
                            (tuileEnMain->y) = 640;
                            (choix->x) = 3;
                            (choix->y )= 6;
                        }
                        if(event.button.x > 499 &&  event.button.x < 570 && event.button.y > 640 && event.button.y < 710){
                            (tuileEnMain->x) = 500;
                            (tuileEnMain->y) = 640;
                            (choix->x) = 5;
                            (choix->y) = 6;
                        }

                        //OUEST
                        if(event.button.x > 79 &&  event.button.x < 150 && event.button.y > 219 && event.button.y < 290){
                            (tuileEnMain->x) = 79;
                            (tuileEnMain->y) = 220;
                            (choix->x) = 0;
                            (choix->y) = 1;
                        }
                        if(event.button.x > 79 &&  event.button.x < 150 && event.button.y > 359 && event.button.y < 430){
                            (tuileEnMain->x) = 79;
                            (tuileEnMain->y) = 360;
                            (choix->x) = 0;
                            (choix->y) = 3;
                        }

                          if(event.button.x > 79 &&  event.button.x < 150 && event.button.y > 499 && event.button.y < 570){
                            (tuileEnMain->x) = 79;
                            (tuileEnMain->y) = 500;
                            (choix->x) = 0;
                            (choix->y) = 5;
                        }
}


void tuilesFixes(TUILE Plateau[7][7]){
    //LIGNE 0:
    Plateau[0][0].fixe=1;
    Plateau[0][0].tresor= 25; //depart joueur 1
    Plateau[0][0].g=0;
    Plateau[0][0].d=1;
    Plateau[0][0].h=0;
    Plateau[0][0].b=1;
    Plateau[0][0].posee=1;
    Plateau[0][0].angle=0;

    Plateau[0][2].fixe=1;
    Plateau[0][2].tresor= 24;
    Plateau[0][2].g=1;
    Plateau[0][2].d=1;
    Plateau[0][2].h=0;;
    Plateau[0][2].b=1;
    Plateau[0][2].posee=1;
    Plateau[0][2].angle=0;

    Plateau[0][4].fixe=1;
    Plateau[0][4].tresor= 23;
    Plateau[0][4].g=1;
    Plateau[0][4].d=1;
    Plateau[0][4].h=0;
    Plateau[0][4].b=1;
    Plateau[0][4].posee=1;
    Plateau[0][4].angle=0;

    Plateau[0][6].fixe=1;
    Plateau[0][6].tresor= 27; //depart joueur 3
    Plateau[0][6].g=1;
    Plateau[0][6].d=0;
    Plateau[0][6].h=0;
    Plateau[0][6].b=1;
    Plateau[0][6].posee=1;
    Plateau[0][6].angle=0;

    //LIGNE 2:
    Plateau[2][0].fixe=1;
    Plateau[2][0].tresor= 22;
    Plateau[2][0].g=0;
    Plateau[2][0].d=1;
    Plateau[2][0].h=1;
    Plateau[2][0].b=1;
    Plateau[2][0].posee=1;
    Plateau[2][0].fixe=1;
    Plateau[2][0].angle=0;

    Plateau[2][2].tresor= 21;
    Plateau[2][2].g=0;
    Plateau[2][2].d=1;
    Plateau[2][2].h=1;
    Plateau[2][2].b=1;
    Plateau[2][2].posee=1;
    Plateau[2][2].fixe=1;
    Plateau[2][2].angle=0;

    Plateau[2][4].tresor= 20;
    Plateau[2][4].g=1;
    Plateau[2][4].d=1;
    Plateau[2][4].h=0;
    Plateau[2][4].b=1;
    Plateau[2][4].posee=1;
    Plateau[2][4].fixe=1;
    Plateau[2][4].angle=0;

    Plateau[2][6].tresor= 19;
    Plateau[2][6].g=1;
    Plateau[2][6].d=0;
    Plateau[2][6].h=1;
    Plateau[2][6].b=1;
    Plateau[2][6].posee=1;
    Plateau[2][6].fixe=1;
    Plateau[2][6].angle=0;

    //LIGNE 4:
    Plateau[4][0].tresor= 18;
    Plateau[4][0].g=0;
    Plateau[4][0].d=1;
    Plateau[4][0].h=1;
    Plateau[4][0].b=1;
    Plateau[4][0].posee=1;
    Plateau[4][0].fixe=1;
    Plateau[4][0].angle=0;

    Plateau[4][2].tresor= 17;
    Plateau[4][2].g=1;
    Plateau[4][2].d=1;
    Plateau[4][2].h=1;
    Plateau[4][2].b=0;
    Plateau[4][2].posee=1;
    Plateau[4][2].fixe=1;
    Plateau[4][2].angle=0;

    Plateau[4][4].tresor= 16;
    Plateau[4][4].g=1;
    Plateau[4][4].d=0;
    Plateau[4][4].h=1;
    Plateau[4][4].b=1;
    Plateau[4][4].posee=1;
    Plateau[4][4].fixe=1;
    Plateau[4][4].angle=0;

    Plateau[4][6].tresor= 15;
    Plateau[4][6].g=1;
    Plateau[4][6].d=0;
    Plateau[4][6].h=1;
    Plateau[4][6].b=1;
    Plateau[4][6].posee=1;
    Plateau[4][6].fixe=1;
    Plateau[4][6].angle=0;

    //LIGNE 6:
    Plateau[6][0].tresor= 28; //depart joueur 4
    Plateau[6][0].g=0;
    Plateau[6][0].d=1;
    Plateau[6][0].h=1;
    Plateau[6][0].b=0;
    Plateau[6][0].posee=1;
    Plateau[6][0].fixe=1;
    Plateau[6][0].angle=0;

    Plateau[6][2].tresor= 14;
    Plateau[6][2].g=1;
    Plateau[6][2].d=1;
    Plateau[6][2].h=1;
    Plateau[6][2].b=0;
    Plateau[6][2].posee=1;
    Plateau[6][2].fixe=1;
    Plateau[6][2].angle=0;

    Plateau[6][4].tresor= 13;
    Plateau[6][4].g=1;
    Plateau[6][4].d=1;
    Plateau[6][4].h=1;
    Plateau[6][4].b=0;
    Plateau[6][4].posee=1;
    Plateau[6][4].fixe=1;
    Plateau[6][4].angle=0;

    Plateau[6][6].tresor= 26; //depart joueur 2
    Plateau[6][6].g=1;
    Plateau[6][6].d=0;
    Plateau[6][6].h=1;
    Plateau[6][6].b=0;
    Plateau[6][6].posee=1;
    Plateau[6][6].fixe=1;
    Plateau[6][6].angle=0;
}


TUILE tuilesCouloir(TUILE Plateau[7][7]){
    srand(time(NULL));
    unsigned int temp = 0;
    TUILE tuilesCouloir[34]; 
   
    for(int i=0; i<12; i++) //les 12 premieres sont des tuiles droites
    {           
        tuilesCouloir[i].angle= 0;
    	temp = rand()%2; 
    	tuilesCouloir[i].fixe =0;
    	tuilesCouloir[i].posee =0;
    	tuilesCouloir[i].tresor =0;
    	tuilesCouloir[i].type ='I'; 
    	tuilesCouloir[i].g = temp; //la gauche au hasard 

        if(temp == 0)
        {
            tuilesCouloir[i].id = 1; //a quoi ca sert ??
            tuilesCouloir[i].angle = 0;
            tuilesCouloir[i].d = 0;
            tuilesCouloir[i].g = 0;
		    tuilesCouloir[i].h = 1;
		    tuilesCouloir[i].b = 1;
        }
        else
        {
            tuilesCouloir[i].id = 1;
            tuilesCouloir[i].angle =90;
            tuilesCouloir[i].d = 1;
            tuilesCouloir[i].g = 1;
		    tuilesCouloir[i].h = 0;
		    tuilesCouloir[i].b = 0;
        }
        
    }

     //### TUILE : angle droit supposons que g h a un angle 0 
    int nbTresors=6; //de 6 à 1 tresors dans angle droit    
    for (int i = 12; i < 16+12; ++i) // de 12 à 28 angle droit
    {
        tuilesCouloir[i].angle= 0;
    	temp = rand()%4; // 4 cas possibles
    	tuilesCouloir[i].fixe =0;
    	tuilesCouloir[i].posee =0;
    	tuilesCouloir[i].type ='L';     
    	if(temp == 0)
    	{
    		tuilesCouloir[i].g=1;
    		tuilesCouloir[i].d=0;
    		tuilesCouloir[i].h=1;
    		tuilesCouloir[i].b=0;
    		tuilesCouloir[i].angle=0;
    	}
    	if(temp == 1)
    	{
    		tuilesCouloir[i].g=1;
    		tuilesCouloir[i].d=0;
    		tuilesCouloir[i].h=0;
    		tuilesCouloir[i].b=1;
    		tuilesCouloir[i].angle=90;
    	}
    	if(temp == 2)
    	{
    		tuilesCouloir[i].g=0;
    		tuilesCouloir[i].d=1;
    		tuilesCouloir[i].h=1;
    		tuilesCouloir[i].b=0;
    		tuilesCouloir[i].angle=180;
    	}
    	if(temp == 3)
    	{
    		tuilesCouloir[i].g=0;
    		tuilesCouloir[i].d=1;
    		tuilesCouloir[i].h=0;
    		tuilesCouloir[i].b=1;
    		tuilesCouloir[i].angle=270; 
    	}
    	tuilesCouloir[i].tresor=0;
    	if(nbTresors>0)
    	{	    		
    		tuilesCouloir[i].tresor=nbTresors;    		
    		nbTresors--;
    	}
    }

    //les tresors restants: de 7 à 12 dans tuile en T
    nbTresors=7;
    for (int i = 16+12; i < 34; ++i)
     {
     	temp = rand()%4; // 4 cas possibles
    	tuilesCouloir[i].fixe =0;
    	tuilesCouloir[i].posee =0; 
    	tuilesCouloir[i].type ='T'; 
    	tuilesCouloir[i].tresor =nbTresors;
    	nbTresors++;   
    	if(temp == 0)
    	{
    		tuilesCouloir[i].g=1;
    		tuilesCouloir[i].d=1;
    		tuilesCouloir[i].h=1;
    		tuilesCouloir[i].b=0;
    		tuilesCouloir[i].angle=0;
    	}
    	if(temp == 1)
    	{
    		tuilesCouloir[i].g=0;
    		tuilesCouloir[i].d=1;
    		tuilesCouloir[i].h=1;
    		tuilesCouloir[i].b=1;
    		tuilesCouloir[i].angle=90;
    	}
    	if(temp == 2)
    	{
    		tuilesCouloir[i].g=1;
    		tuilesCouloir[i].d=1;
    		tuilesCouloir[i].h=0;
    		tuilesCouloir[i].b=1;
    		tuilesCouloir[i].angle=180;
    	}
    	if(temp == 3)
    	{
    		tuilesCouloir[i].g=1;
    		tuilesCouloir[i].d=0;
    		tuilesCouloir[i].h=1;
    		tuilesCouloir[i].b=1;
    		tuilesCouloir[i].angle=270; 
    	}

     } 
    for(int i=0; i<34;i++){
        printf("%d : %d\n",i,tuilesCouloir[i].tresor);
    }

    CORD pAleatoire;
    unsigned int i=0;
    int numTresor;
    char bmpName[12] = "img/C/cA.bmp";
    while(i<33){ // Remplissage aléatorire de 33 tuiles couloirs
        pAleatoire.x = rand()%7;
        pAleatoire.y = rand()%7;
        if(Plateau[pAleatoire.x][pAleatoire.y].posee == 0)
        {
            Plateau[pAleatoire.x][pAleatoire.y] = tuilesCouloir[i];
            Plateau[pAleatoire.x][pAleatoire.y].posee = 1;
            numTresor = Plateau[pAleatoire.x][pAleatoire.y].tresor;
            if(numTresor!=0) //chargement des image tresors
            {
            	bmpName[7]=numTresor+'A'-1;
                printf("%s\n",bmpName);
            	if((Plateau[pAleatoire.x][pAleatoire.y].image= SDL_LoadBMP(bmpName)) == NULL)
            		SDL_ExitWithError("Erreur chargement image");           
            }
            else
            	{
            		if(Plateau[pAleatoire.x][pAleatoire.y].type == 'I' ) //charger 1.bmp
            		{
            			if((Plateau[pAleatoire.x][pAleatoire.y].image= SDL_LoadBMP("img/1.bmp")) == NULL)
            				SDL_ExitWithError("Erreur chargement image");  
            		}
            		if(Plateau[pAleatoire.x][pAleatoire.y].type == 'T') //charger 2.bmp
            		{
            			if((Plateau[pAleatoire.x][pAleatoire.y].image= SDL_LoadBMP("img/2.bmp")) == NULL)
            				SDL_ExitWithError("Erreur chargement image");  
            		}
            		if(Plateau[pAleatoire.x][pAleatoire.y].type == 'L') //charger 3.bmp
            		{
            			if((Plateau[pAleatoire.x][pAleatoire.y].image= SDL_LoadBMP("img/3.bmp")) == NULL)
            				SDL_ExitWithError("Erreur chargement image");  
            		}

            	}

             // suivant
         printf("%d\n",i);
         i++;
        }

    }
    //&tuileEnMain = tuilesCouloir[i]; //la 34 eme
    //bloc a mettre dans une fonction à part ---------
    				if(tuilesCouloir[i].type == 'I' ) //charger 1.bmp
            		{
            			if((tuilesCouloir[i].image= SDL_LoadBMP("img/1.bmp")) == NULL)
            				SDL_ExitWithError("Erreur chargement image");  
            		}
            		if(tuilesCouloir[i].type == 'T') //charger 2.bmp
            		{
            			if((tuilesCouloir[i].image= SDL_LoadBMP("img/2.bmp")) == NULL)
            				SDL_ExitWithError("Erreur chargement image");  
            		}
            		if(tuilesCouloir[i].type == 'L') //charger 3.bmp
            		{
            			if((tuilesCouloir[i].image= SDL_LoadBMP("img/3.bmp")) == NULL)
            				SDL_ExitWithError("Erreur chargement image");  
            		}

            TUILE tmp = tuilesCouloir[i];
            
            unsigned int last = rand()%34;

            return tmp;
}





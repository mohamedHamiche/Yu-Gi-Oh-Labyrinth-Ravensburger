#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

typedef struct tuile TUILE;
struct tuile
{
    int fixe ;
    int tresor; 
    int g, d, h, b;  
    int posee;
    SDL_Rect caseSdl;
    SDL_Surface *image;
    SDL_Texture *texture;
};
//#include "SDL2/SDL_image.h
//#include <SDL2/SDL_ttf.h>
//sudo apt-get install libsdl2-ttf-dev
//sudo apt-get update && sudo apt-get upgrade
//sudo apt-get install libsdl2-image-dev
//gcc main.c $(sdl2-config --cflags --libs)


void tuilesFixes(TUILE Plateau[7][7]);


int main(int argc, char *argv[]){
	srand(time(NULL));
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	//SDL_Texture *texture[2] = {0};



	if( 0!= SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stderr,"Erreur SDL_Init : %s",SDL_GetError());
		 
	}
	window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 940,940,SDL_WINDOW_SHOWN);
	if(window == NULL){
		fprintf(stderr, "Erreur: %s",SDL_GetError());
		exit(1);
	}
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
	if(renderer == NULL){
		fprintf(stderr,"Erreur SDL_createRenderer : %s",SDL_GetError());
		exit(1);
	}

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer); // pour la fenetre entiere

	TUILE plateau[7][7];
	tuilesFixes(plateau);

	char Nom[10] = "a.bmp";
	unsigned int suiv=0;
	for(int i=0 ;i<7; i+=2){
		for(int j=0; j<7; j+=2){
			plateau[i][j].image = SDL_LoadBMP(Nom);
			if(plateau[i][j].image == NULL){
				fprintf(stderr,"Erreur: chargements des images, tuiles fixes.\n");
				exit(1);
			}
			Nom[0] = 'a'+suiv+1;
			suiv++;
		}
	}


	SDL_Surface *imageTCtresor[12];
	char img2[10] = "A.bmp";

	for(int i =0; i<12 ; i++){
		imageTCtresor[i] = SDL_LoadBMP(img2);
		printf("%d : %s\n",i,img2);

		img2[0] = 'A'+i+1;
		if(imageTCtresor[i] == NULL){
			fprintf(stderr,"Erreur : impossible de charger l'image2 %s\n",img2);
			exit(1);
		}
	}

	SDL_Surface *imageTC[3];
	imageTC[0] = SDL_LoadBMP("1.bmp");
	imageTC[1] = SDL_LoadBMP("2.bmp");
	imageTC[2] = SDL_LoadBMP("3.bmp");




printf("a\n");

	unsigned int r=0;

	int tmp=0, tFixe=0, k=1;

        for(int i=0; i<7; i++){
    		for(int j=0; j<7; j++){
    			if((j%2 == 0) && (i%2 == 0) ){
    				plateau[i][j].texture=SDL_CreateTextureFromSurface(renderer, plateau[i][j].image);
    				 printf("%d",tFixe);
    				tFixe +=4;
    				if(tFixe > 15){
    					tFixe=k;
    					k++;
    				} 


    			}
    			else{
    				r= rand()%2;

    				plateau[i][j].texture=SDL_CreateTextureFromSurface(renderer, imageTCtresor[r]);
    			}
    		}
    		printf("\n");	

    	}

printf("\n");

    
    int positionX = 150;
    int positionY = 150; 
    int j=0;

    SDL_Rect tuileEnMain;
    tuileEnMain.x=720;
    tuileEnMain.y=340;
    tuileEnMain.h = 70;
    tuileEnMain.w=70;

    for(int i=0; i<7; i++){
    	for(int j=0; j<7; j++){
    		plateau[i][j].caseSdl.x = positionX+i*70;
    		plateau[i][j].caseSdl.y = positionY+j*70;
    		plateau[i][j].caseSdl.h = 70;
    		plateau[i][j].caseSdl.w = 70;

    	}
    }
    double angle2=0, a=0;
    double angle[33] ={0};
    for(int i =0; i<33; i++){
    	a = rand()%4;
    	angle[i] = 90*a;
    }
   
SDL_RendererFlip flip = SDL_FLIP_NONE;

	int exit=1;
	SDL_Event event;	
	unsigned int i=0;
	while(exit){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					exit=0;
					break;
				case SDL_MOUSEBUTTONDOWN:
                    //fprintf(stdout, "\t x: %d\n",event.button.x);
                    //fprintf(stdout, "\t x : %d\n",event.button.y);
 					if(event.button.x >163 &&  event.button.x < 229 && event.button.y > 35 && event.button.y < 101){
						tuileEnMain.x = 100+64;
						tuileEnMain.y = 100-64;
					}
					if(event.button.button == 3){
						angle2+=90;
					}
					if(event.button.button == 1){
						tuileEnMain.x = event.button.x-35;
						tuileEnMain.y = event.button.y-35
						;

					}
					       
				default:
					break;
			}
			SDL_RenderClear(renderer);
				
		
		}
       

        // Incrémentation de l'angle

       r=0;
    for(int i=0; i<7; i++){
    	for(int j=0; j<7; j++){
    		if((j%2 != 0) || (i%2 != 0)){	    		
				SDL_RenderCopyEx(renderer,plateau[i][j].texture,NULL,&plateau[i][j].caseSdl,0,NULL,flip);
				r++;
			}
			else{
			SDL_RenderCopyEx(renderer,plateau[i][j].texture,NULL,&plateau[i][j].caseSdl,0,NULL,flip);


			}
		}
	}
			SDL_RenderCopyEx(renderer,plateau[0][0].texture,NULL,&tuileEnMain,angle2,NULL,flip);
			SDL_RenderPresent(renderer);

	}








	for(int i=0; i<7; i++){
    	for(int j=0; j<7; j++){
			SDL_DestroyTexture(plateau[i][j].texture);
			//if((i%2 == 0) && (j%2 == 0))
			SDL_FreeSurface(plateau[i][j].image);
				
		}
	}


	for(int i=0; i<12; i++){
		SDL_FreeSurface(imageTCtresor[i]);
		
	}
		SDL_FreeSurface(imageTC[0]);
		SDL_FreeSurface(imageTC[2]);
		SDL_FreeSurface(imageTC[1]);

			


	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;


}




void tuilesFixes(TUILE Plateau[7][7]){
    //LIGNE 0:
    Plateau[0][0].fixe=1;
    Plateau[0][0].tresor= 25;
    Plateau[0][0].g=0;
    Plateau[0][0].d=1;
    Plateau[0][0].h=0;
    Plateau[0][0].b=1;
    Plateau[0][0].posee=1;
    Plateau[0][2].fixe=1;
    Plateau[0][2].tresor= 24;
    Plateau[0][2].g=1;
    Plateau[0][2].d=1;
    Plateau[0][2].h=0;;
    Plateau[0][2].b=1;
    Plateau[0][2].posee=1;
    Plateau[0][4].fixe=1;
    Plateau[0][4].tresor= 23;
    Plateau[0][4].g=1;
    Plateau[0][4].d=1;
    Plateau[0][4].h=0;
    Plateau[0][4].b=1;
    Plateau[0][4].posee=1;
    Plateau[0][6].fixe=1;
    Plateau[0][6].tresor= 22;
    Plateau[0][6].g=1;
    Plateau[0][6].d=0;
    Plateau[0][6].h=0;
    Plateau[0][6].b=1;
    Plateau[0][6].posee=1;
    //LIGNE 2:
    Plateau[2][0].fixe=1;
    Plateau[2][0].tresor= 20;
    Plateau[2][0].g=0;
    Plateau[2][0].d=1;
    Plateau[2][0].h=1;
    Plateau[2][0].b=1;
    Plateau[2][0].posee=1;
    Plateau[2][0].fixe=1;
    Plateau[2][2].tresor= 19;
    Plateau[2][2].g=0;
    Plateau[2][2].d=1;
    Plateau[2][2].h=1;
    Plateau[2][2].b=1;
    Plateau[2][2].posee=1;
    Plateau[2][2].fixe=1;
    Plateau[2][4].tresor= 18;
    Plateau[2][4].g=1;
    Plateau[2][4].d=1;
    Plateau[2][4].h=0;
    Plateau[2][4].b=1;
    Plateau[2][4].posee=1;
    Plateau[2][4].fixe=1;
    Plateau[2][6].tresor= 17;
    Plateau[2][6].g=1;
    Plateau[2][6].d=0;
    Plateau[2][6].h=1;
    Plateau[2][6].b=1;
    Plateau[2][6].posee=1;
    Plateau[2][6].fixe=1;
    //LIGNE 4:
    Plateau[4][0].tresor= 16;
    Plateau[4][0].g=0;
    Plateau[4][0].d=1;
    Plateau[4][0].h=1;
    Plateau[4][0].b=1;
    Plateau[4][0].posee=1;
    Plateau[4][0].fixe=1;
    Plateau[4][2].tresor= 15;
    Plateau[4][2].g=1;
    Plateau[4][2].d=1;
    Plateau[4][2].h=1;
    Plateau[4][2].b=0;
    Plateau[4][2].posee=1;
    Plateau[4][2].fixe=1;
    Plateau[4][4].tresor= 14;
    Plateau[4][4].g=1;
    Plateau[4][4].d=0;
    Plateau[4][4].h=1;
    Plateau[4][4].b=1;
    Plateau[4][4].posee=1;
    Plateau[4][4].fixe=1;
    Plateau[4][6].tresor= 13;
    Plateau[4][6].g=1;
    Plateau[4][6].d=0;
    Plateau[4][6].h=1;
    Plateau[4][6].b=1;
    Plateau[4][6].posee=1;
    Plateau[4][6].fixe=1;
    //LIGNE 6:
    Plateau[6][0].tresor= 12;
    Plateau[6][0].g=0;
    Plateau[6][0].d=1;
    Plateau[6][0].h=1;
    Plateau[6][0].b=0;
    Plateau[6][0].posee=1;
    Plateau[6][0].fixe=1;
    Plateau[6][2].tresor= 11;
    Plateau[6][2].g=1;
    Plateau[6][2].d=1;
    Plateau[6][2].h=1;
    Plateau[6][2].b=0;
    Plateau[6][2].posee=1;
    Plateau[6][2].fixe=1;
    Plateau[6][4].tresor= 10;
    Plateau[6][4].g=1;
    Plateau[6][4].d=1;
    Plateau[6][4].h=1;
    Plateau[6][4].b=0;
    Plateau[6][4].posee=1;
    Plateau[6][4].fixe=1;
    Plateau[6][6].tresor= 9;
    Plateau[6][6].g=1;
    Plateau[6][6].d=0;
    Plateau[6][6].h=1;
    Plateau[6][6].b=0;
    Plateau[6][6].posee=1;
    Plateau[6][6].fixe=1;
}
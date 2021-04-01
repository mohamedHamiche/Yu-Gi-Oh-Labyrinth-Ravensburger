#include <stdio.h>
#include <SDL2/SDL.h>
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
    int id;
    unsigned int angleTuile;
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
void ouvertureRand(unsigned int *g,unsigned int *d,unsigned int *b,unsigned int *h);
void tuilesCouloir(TUILE Plateau[7][7], TUILE tuileEnMain);
TUILE decalerCouloir(TUILE plateau[7][7], CORD choixCouloir, TUILE tuileEnMain);


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

	TUILE plateau[7][7], tuileEm;
	tuilesFixes(plateau);
    //tuilesCouloir(plateau,tuileEm);
printf("test\n");

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
printf("test\n");


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


printf("test\n");


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
                    if(plateau[i][j].id == 1)
                        plateau[i][j].texture=SDL_CreateTextureFromSurface(renderer, imageTC[0]);

                    else
    				plateau[i][j].texture=SDL_CreateTextureFromSurface(renderer, imageTCtresor[r]);

    			}
    		}
    		printf("\n");	

    	}

printf("\n");

    printf("test\n");


    int positionX = 150;
    int positionY = 150; 
    int j=0;

    SDL_Rect tuileEnMain;
    TUILE tuileEnMain1 = plateau[0][0];

    tuileEnMain.x=720;
    tuileEnMain.y=340;
    tuileEnMain.h = 70;
    tuileEnMain.w=70;
    SDL_Rect caseSdl[7][7];


    for(int i=0; i<7; i++){
    	for(int j=0; j<7; j++){
    		caseSdl[i][j].x = positionX+i*70;
    		caseSdl[i][j].y = positionY+j*70;
    		caseSdl[i][j].h = 70;
    		caseSdl[i][j].w = 70;

    	}
    }
    double angle2=0, a=0;
    double angle[33] ={0};
    for(int i =0; i<33; i++){
    	a = rand()%4;
    	angle[i] = 90*a;
    }
   
SDL_RendererFlip flip = SDL_FLIP_NONE;
    CORD choix;
    TUILE tuileM;
    choix.x =1;
    choix.y =0;
	int exit=1;
	SDL_Event event;	
	unsigned int i=0, test=0;;
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
                    if(event.button.button == 2){
                       tuileEnMain1 = decalerCouloir(plateau, choix,tuileEnMain1);
                    }
					if(event.button.button == 1){
						tuileEnMain.x = event.button.x-35;
						tuileEnMain.y = event.button.y-35;
						

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
				SDL_RenderCopyEx(renderer,plateau[i][j].texture,NULL,&caseSdl[i][j],0,NULL,flip);
				r++;
			}

            

			else{
			SDL_RenderCopyEx(renderer,plateau[i][j].texture,NULL,&caseSdl[i][j],0,NULL,flip);


			}
		}
	}
			SDL_RenderCopyEx(renderer,tuileEnMain1.texture,NULL,&tuileEnMain,angle2,NULL,flip);
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



void tuilesCouloir(TUILE Plateau[7][7], TUILE tuileEnMain){
    srand(time(NULL));
    unsigned int temp = 0, opp; 

    TUILE tuilesCouloir[34];    
    TUILE tuilesLignes[12];
    TUILE angleDroit[10];

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[0].fixe =0;
    tuilesLignes[0].tresor =0;
    tuilesLignes[0].g = temp;
    tuilesLignes[0].d = temp;
    tuilesLignes[0].h = opp;
    tuilesLignes[0].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[1].fixe =0;
    tuilesLignes[1].tresor =0;
    tuilesLignes[1].g = temp;
    tuilesLignes[1].d = temp;
    tuilesLignes[1].h = opp;
    tuilesLignes[1].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[2].fixe =0;
    tuilesLignes[2].tresor =0;
    tuilesLignes[2].g = temp;
    tuilesLignes[2].d = temp;
    tuilesLignes[2].h = opp;
    tuilesLignes[2].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[3].fixe =0;
    tuilesLignes[3].tresor =0;
    tuilesLignes[3].g = temp;
    tuilesLignes[3].d = temp;
    tuilesLignes[3].h = opp;
    tuilesLignes[3].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[4].fixe =0;
    tuilesLignes[4].tresor =0;
    tuilesLignes[4].g = temp;
    tuilesLignes[4].d = temp;
    tuilesLignes[4].h = opp;
    tuilesLignes[4].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[5].fixe =0;
    tuilesLignes[5].tresor =0;
    tuilesLignes[5].g = temp;
    tuilesLignes[5].d = temp;
    tuilesLignes[5].h = opp;
    tuilesLignes[5].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[6].fixe =0;
    tuilesLignes[6].tresor =0;
    tuilesLignes[6].g = temp;
    tuilesLignes[6].d = temp;
    tuilesLignes[6].h = opp;
    tuilesLignes[6].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[7].fixe =0;
    tuilesLignes[7].tresor =0;
    tuilesLignes[7].g = temp;
    tuilesLignes[7].d = temp;
    tuilesLignes[7].h = opp;
    tuilesLignes[7].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[8].fixe =0;
    tuilesLignes[8].tresor =0;
    tuilesLignes[8].g = temp;
    tuilesLignes[8].d = temp;
    tuilesLignes[8].h = opp;
    tuilesLignes[8].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[9].fixe =0;
    tuilesLignes[9].tresor =0;
    tuilesLignes[9].g = temp;
    tuilesLignes[9].d = temp;
    tuilesLignes[9].h = opp;
    tuilesLignes[9].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[10].fixe =0;
    tuilesLignes[10].tresor =0;
    tuilesLignes[10].g = temp;
    tuilesLignes[10].d = temp;
    tuilesLignes[10].h = opp;
    tuilesLignes[10].b = opp;

    temp = rand()%2;
    if(temp == 0)
        opp = 1;
    else
        opp = 0;

    tuilesLignes[11].fixe =0;
    tuilesLignes[11].tresor =0;
    tuilesLignes[11].g = temp;
    tuilesLignes[11].d = temp;
    tuilesLignes[11].h = opp;
    tuilesLignes[11].b = opp;
    
    for(int i=0; i<12; i++){
        if(tuilesLignes[i].g == 0){
            tuilesLignes[i].id = 1;
            tuilesLignes[i].angleTuile = 0;
        }
        else{
            tuilesLignes[i].id = 1;
            tuilesLignes[i].angleTuile =90;

        }

        tuilesCouloir[i] = tuilesLignes[i];
        
    }

/*
    //### TUILE : angle droit
    angleDroit[0].fixe = 0;
    angleDroit[0].tresor = 0;
    ouvertureRand(&angleDroit[0].g, &angleDroit[0].d,&angleDroit[0].b, &angleDroit[0].h);

    angleDroit[1].fixe = 0;
    angleDroit[1].tresor = 0;
    ouvertureRand(&angleDroit[1].g, &angleDroit[1].d,&angleDroit[1].b, &angleDroit[1].h);

    angleDroit[2].fixe = 0;
    angleDroit[2].tresor = 0;
    ouvertureRand(&angleDroit[2].g, &angleDroit[2].d,&angleDroit[2].b, &angleDroit[2].h);

    angleDroit[3].fixe = 0;
    angleDroit[3].tresor = 0;
    ouvertureRand(&angleDroit[3].g, &angleDroit[3].d,&angleDroit[3].b, &angleDroit[3].h);

    angleDroit[4].fixe = 0;
    angleDroit[4].tresor = 0;
    ouvertureRand(&angleDroit[4].g, &angleDroit[4].d,&angleDroit[4].b, &angleDroit[4].h);

    angleDroit[5].fixe = 0;
    angleDroit[5].tresor = 0;
    ouvertureRand(&angleDroit[5].g, &angleDroit[5].d,&angleDroit[5].b, &angleDroit[5].h);

    angleDroit[6].fixe = 0;
    angleDroit[6].tresor = 0;
    ouvertureRand(&angleDroit[6].g, &angleDroit[6].d,&angleDroit[6].b, &angleDroit[6].h);

    angleDroit[7].fixe = 0;
    angleDroit[7].tresor = 0;
    ouvertureRand(&angleDroit[7].g, &angleDroit[7].d,&angleDroit[7].b, &angleDroit[7].h);

    angleDroit[8].fixe = 0;
    angleDroit[8].tresor = 0;
    ouvertureRand(&angleDroit[8].g, &angleDroit[8].d,&angleDroit[8].b, &angleDroit[8].h);

    angleDroit[9].fixe = 0;
    angleDroit[9].tresor = 0;
    ouvertureRand(&angleDroit[9].g, &angleDroit[9].d,&angleDroit[9].b, &angleDroit[9].h);

    for(int i=12; i<22; i++)
        tuilesCouloir[i] = angleDroit[i];
    
*/
    

    CORD tAleatoire, pAleatoire;
    unsigned int i=0;
    while(i<12){ // Remplissage aléatorire
        pAleatoire.x = rand()%7;
        pAleatoire.y = rand()%7;
        if(Plateau[pAleatoire.x][pAleatoire.y].posee == 0){
            Plateau[pAleatoire.x][pAleatoire.y] = tuilesCouloir[i];
            Plateau[pAleatoire.x][pAleatoire.y].posee = 1;
            i++;
        }
    }
    //tuileEnMain = tuilesCouloir[i];

}





void ouvertureRand(unsigned int *g,unsigned int *d,unsigned int *b,unsigned int *h){
    /*
    *Cette fonciton permet de retourner des ouvertures (les sorties et entrées possibles de la tuile) d'une tuiles "angle droit"
    *au hasard, afin d'éviter d'avoir les tuiles orientées tous dans le même sens lors de l'initialisation du plateau. 
    */
    srand(time(NULL));
    unsigned int r = rand()%4;
    if(r == 0){
        (*g) = 0;
        (*d) = 1;
        (*b) = 1;
        (*h) = 0;
    }
    else if(r == 1){
        (*g) = 0;
        (*d) = 1;
        (*b) = 0;
        (*h) = 1;
    }
    else if(r == 2){
        (*g) = 1;
        (*d) = 0;
        (*b) = 0;
        (*h) = 1;
    }
    else if(r == 3){
        (*g) = 1;
        (*d) = 0;
        (*b) = 1;
        (*h) = 0;
    }
}
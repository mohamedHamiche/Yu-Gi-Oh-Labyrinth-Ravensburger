#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void SDL_ExitWithError(const char *message);

int main(int argc, char** argv)
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer =NULL;

	SDL_version maVersion;
	SDL_VERSION(&maVersion);
	printf("bienvenue sur la sdl : %d %d %d \n",maVersion.major, maVersion.minor, maVersion.patch);

	//Lancement SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_ExitWithError("Initialisation SDL");
	}

	//Creation fenetre + rendu 
	if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)							
		SDL_ExitWithError("Creation fenetre echouée");		

	/*------------------------------------*/
	if(SDL_SetRenderDrawColor(renderer,112,68,237, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de changer la couleur");
	
	if(SDL_RenderDrawPoint(renderer, 100, 450) != 0)
		SDL_ExitWithError("Impossible de dessiner un point");

	if(SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0)
		SDL_ExitWithError("Impossible de dessiner une ligne");

	if(SDL_SetRenderDrawColor(renderer,255,15,15, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de changer la couleur");

	
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;

	image = SDL_LoadBMP("img/a.bmp");
	if(image == NULL)
	{
		SDL_DestroyRenderer(renderer);	
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de charger l'image");
	}

	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	if(texture == NULL)
	{
		SDL_DestroyRenderer(renderer);	
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de créer la texture");
	}

	SDL_Rect rectangle;
	if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
	{
		SDL_DestroyRenderer(renderer);	
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de charger la texture");
	}

	rectangle.x= (WINDOW_WIDTH - rectangle.w) /2 ;
	rectangle.y= (WINDOW_HEIGHT - rectangle.h) /2 ;
	//rectangle.x= 0;
	//rectangle.y= 0;

	if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0)
	{
		SDL_DestroyRenderer(renderer);	
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible d'afficher la texture");
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(6000);
	/*------------------------------------*/

	SDL_DestroyRenderer(renderer);	
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
	
}

// gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 [-mwindows]

void SDL_ExitWithError(const char *message)
{
	SDL_Log("ERREUR : %s > %s\n",message, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}
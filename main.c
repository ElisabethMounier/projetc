#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "display.h"
#include "events.h"

int main(int argc, char** argv){

	SDL_Event event;
	Layout    layouts;
	SDL_Window * window;
	bool exit = false;

	/* initialisation de la SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Candy Crush Saga",SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH, WINDOW_HEIGH, SDL_WINDOW_SHOWN);

	if ( window == NULL )
	{
		fprintf(stdout,"Échec de création de la fenêtre (%s)\n",SDL_GetError());
		return -2;
	}

	create_menus(window, &layouts); //display.c
	SDL_RenderPresent(layouts.renderer); // affiche le renderer dans la fenêtre

	/* Boucle principale */
	while(!exit)
	{
		exit = events_handler(event, &layouts); //events.c
	}
	/* Destruction de la fenêtre */
	SDL_DestroyWindow(window);

	/* Fermeture de la SDL */
	SDL_Quit();

	return 0;
}

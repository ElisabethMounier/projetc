#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "display.h"
#include "events.h"
#include "grid.h"

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

	int grid[5][8];
	init_grid(grid); //grid.c
	SDL_Surface * candy_surfaces[7] = {
	IMG_Load("purple_candy.png"),
	IMG_Load("red_candy.png"),
	IMG_Load("orange_candy.png"),
	IMG_Load("yellow_candy.png"),
	IMG_Load("green_candy.png"),
	IMG_Load("blue_candy.png"),
	IMG_Load("empty_candy.png"),
	};
	draw_candy(&layouts, E_level1_menu, grid,candy_surfaces);




	/* Boucle principale */
	while(!exit)
	{
		exit = events_handler(event, &layouts); //events.c
		SDL_RenderPresent(layouts.renderer); // affiche le renderer dans la fenêtre

	}
	/* Destruction de la fenêtre */
	SDL_DestroyWindow(window);

	/* Fermeture de la SDL */
	SDL_Quit();

	return 0;
}

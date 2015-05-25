#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include "display.h"
#include "events.h"
#include "grid.h"
#include "game.h"


int main(int argc, char** argv){

	SDL_Event event;
	Layout    layouts;
	SDL_Window * window;
	char *scoretext;
	char *movetext;
	char *targettext;
	bool exit = false;
	SDL_Color couleurBlanche = {255, 255, 255};
	SDL_Surface *texte = NULL;
	SDL_Surface *texte2 = NULL;
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
	TTF_Init();
	TTF_Font *police  = TTF_OpenFont("JandaHappyDay.ttf", 89);

	
	create_menus(window, &layouts); //display.c
	
	//SDL_Surface* textSurface = TTF_RenderText_Solid( Score, textureText.c_str(), textColor );
	//int grid[5][8
	//initGrid(); //grid.c
	initialize_level_1();	
	SDL_Surface * candy_surfaces[7] = {
	IMG_Load("empty_candy.png"),
	IMG_Load("red_candy.png"),
	IMG_Load("orange_candy.png"),
	IMG_Load("yellow_candy.png"),
	IMG_Load("green_candy.png"),
	IMG_Load("blue_candy.png"),
	IMG_Load("purple_candy.png")
	};
	
	int click1=0,click2=0;
	int x1, x2, y1, y2;

	draw_candy(&layouts, E_level1_menu, grid,candy_surfaces);
	/* Boucle principale */
	while(!exit)
	{
		int menu=0;
		//SDL_Delay(20);
		if(menu)
			exit = events_handler(event, &layouts); //events.c
		//draw_candy(&layouts, E_level1_menu, grid,candy_surfaces);
		else{
			SDL_WaitEvent(&event);// on utilise waitevent par rapport à pollevent pour récupérer un seul clic de souris, car pollevent trop sensible
			
		
				if(event.type==SDL_WINDOWEVENT)
					if(event.window.event == SDL_WINDOWEVENT_CLOSE)
						exit=1;
								 	
				if(event.type == SDL_MOUSEBUTTONDOWN  ) { 
									 
					if(!click1){					
						SDL_GetMouseState( &x1, &y1 );
						click1=1;
										
					}					
					else{
						SDL_GetMouseState( &x2, &y2 );
						click2=1;
						
					}
				}
			
			if(click2){			
				play((int)(y1-150)/107,(int)(x1-380)/110,(int)(y2-150)/107,(int)(x2-380)/110);
				click1=0;click2=0;
				SDL_RenderCopy(layouts.renderer, layouts.texture[E_level1_menu], NULL, NULL);
				SDL_RenderPresent(layouts.renderer);
				draw_candy(&layouts, E_level1_menu, grid,candy_surfaces);
				sprintf(scoretext, "%d", total_score);
				puts(scoretext);
				texte = TTF_RenderText_Blended(police, scoretext, couleurBlanche);
				draw_score(&layouts, E_level1_menu, texte);
				//sprintf(movetext, "%d", moves);
				//texte2 = TTF_RenderText_Blended(police, movetext, couleurBlanche);
				//draw_move(&layouts, E_level1_menu, texte2);
			}		
		}
		SDL_RenderPresent(layouts.renderer); // affiche le renderer dans la fenêtre
		
	}
	/* Destruction de la fenêtre */
	SDL_DestroyWindow(window);

	/* Fermeture de la SDL */
	SDL_Quit();

	return 0;
}

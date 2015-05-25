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
	char scoretext[80]={ };
	char movetext[80]={ };
	char targettext[80]={ };
	bool exit = false;
	SDL_Color couleurBlanche = {255, 255, 255};
SDL_Color couleurGrise = {118, 111, 100};
	SDL_Surface *texte = NULL;
	SDL_Surface *texte2 = NULL;
	SDL_Surface *texte3 = NULL;
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
	SDL_RenderPresent(layouts.renderer);
	int test=0;
	draw_candy(&layouts, E_level1_menu, grid,candy_surfaces);
	enum E_layout old_layout=E_level1_menu;
	/* Boucle principale */
	while(!exit)
	{	
		
		if(layouts.current_layout!=old_layout){
			test=0;
			initialize_level_1();
			printf("yep");
		}
		old_layout=layouts.current_layout;
		if(layouts.current_layout==E_level1_menu)
			{
				//printf("oui");
				if(test==0){draw_candy(&layouts, E_level1_menu, grid,candy_surfaces);test=1;SDL_RenderPresent(layouts.renderer); }}
		//SDL_Delay(20);
		
			exit = events_handler(event, &layouts, &click1, &click2); //events.c
			
			if(layouts.current_layout==E_level1_menu)
			{
				
			
			
			if(click2){			
				play((int)(y11-150)/107,(int)(x11-385)/110,(int)(y22-150)/107,(int)(x22-385)/110);
				click1=0;click2=0;
				y11=0;y22=0;x11=0;x22=0;
				SDL_RenderCopy(layouts.renderer, layouts.texture[E_level1_menu], NULL, NULL);
				SDL_RenderPresent(layouts.renderer);
				draw_candy(&layouts, E_level1_menu, grid,candy_surfaces);
				sprintf(scoretext, "%d", total_score);
				texte = TTF_RenderText_Blended(police, scoretext, couleurBlanche);
				draw_score(&layouts, E_level1_menu, texte);
				sprintf(movetext, "%d", rest_moves);
				texte2 = TTF_RenderText_Blended(police, movetext, couleurBlanche);
				draw_move(&layouts, E_level1_menu, texte2);
				sprintf(targettext, "%d", target);
				texte3 = TTF_RenderText_Blended(police, targettext, couleurGrise);
				draw_target(&layouts, E_level1_menu, texte3);
				SDL_RenderPresent(layouts.renderer); 
			}		
			
			if(total_score>=target){
				layouts.current_layout=E_win_menu;
				SDL_RenderPresent(layouts.renderer); 
			}			
			if(rest_moves<1){
				layouts.current_layout=E_lose_menu;
				SDL_RenderPresent(layouts.renderer); 
			}		
		// affiche le renderer dans la fenêtre
		}
	}
	/* Destruction de la fenêtre */
	SDL_DestroyWindow(window);

	/* Fermeture de la SDL */
	SDL_Quit();

	return 0;
}

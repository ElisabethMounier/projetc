#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "grid.h"
#include "display.h"
/*
void init_grid(int grid[][8]) {
	int i;
	int j;
  	for (i=0; i<5; i++) {
    		for (j=0; j<8; j++) {
      			grid[i][j]=rand()%7;
    		}
  	}
}
*/
int draw_candy(Layout * l,enum E_layout e, int grid[][8], SDL_Surface* candy_surfaces[7])
{
	SDL_Texture * texture;
	SDL_Rect rect;
	int i;
	int j;
	
	for (i=0; i<5; i++) {
    		for (j=0; j<8; j++) {

    			SDL_Surface * temp_surface = candy_surfaces[grid[i][j]];
    			texture = SDL_CreateTextureFromSurface(l->renderer, temp_surface);
    			rect.x = j*107 + 380;
    			rect.y = i*107 + 150;
    			rect.w = temp_surface->w;
    			rect.h = temp_surface->h;
			//free(temp_surface);
    			SDL_RenderCopy(l->renderer, texture, NULL, &rect);
    			}
    	}

return 0;

}

int draw_score(Layout * l,enum E_layout e,SDL_Surface *temp_surface)
{
	SDL_Texture * texture;
	SDL_Rect rect;		
    	texture = SDL_CreateTextureFromSurface(l->renderer, temp_surface);
    	rect.x = 75;
    	rect.y = 455;
    	rect.w = 250;
    	rect.h = 50;
	SDL_FreeSurface(temp_surface);
    	SDL_RenderCopy(l->renderer, texture, NULL, &rect);

return 0;

}

int draw_move(Layout * l,enum E_layout e,SDL_Surface *temp_surface)
{
	SDL_Texture * texture;
	SDL_Rect rect;		
    	texture = SDL_CreateTextureFromSurface(l->renderer, temp_surface);
    	rect.x = 150;
    	rect.y = 265;
    	rect.w = 100;
    	rect.h = 50;
	SDL_FreeSurface(temp_surface);
    	SDL_RenderCopy(l->renderer, texture, NULL, &rect);

return 0;

}

int draw_target(Layout * l,enum E_layout e,SDL_Surface *temp_surface)
{
	SDL_Texture * texture;
	SDL_Rect rect;		
    	texture = SDL_CreateTextureFromSurface(l->renderer, temp_surface);
    	rect.x = 1085;
    	rect.y = 60;
    	rect.w = 130;
    	rect.h = 50;
	SDL_FreeSurface(temp_surface);
    	SDL_RenderCopy(l->renderer, texture, NULL, &rect);

return 0;

}




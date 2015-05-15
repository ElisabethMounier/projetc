#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "grid.h"
#include "display.h"

void init_grid(int grid[][8]) {
  	for (int i=0; i<5; i++) {
    		for (int j=0; j<8; j++) {
      			grid[i][j]=rand()%7;
    		}
  	}
}

int draw_candy(Layout * l,enum E_layout e, int grid[][8], SDL_Surface* candy_surfaces[7])
{
	SDL_Texture * texture;
	SDL_Rect rect;
	for (int i=0; i<5; i++) {
    		for (int j=0; j<8; j++) {

    			SDL_Surface * temp_surface = candy_surfaces[grid[i][j]];
    			texture = SDL_CreateTextureFromSurface(l->renderer, temp_surface);
    			rect.x = j*107 + 380;
    			rect.y = i*107 + 150;
    			rect.w = temp_surface->w;
    			rect.h = temp_surface->h;

    			SDL_RenderCopy(l->renderer, texture, NULL, &rect);
    			}
    	}

return 0;

}









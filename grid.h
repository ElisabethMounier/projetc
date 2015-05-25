#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "display.h"


#ifndef __GRID_H__
#define __GRID_H__

void init_grid(int grid[][8]);

int draw_candy(Layout * l,enum E_layout e, int grid[][8], SDL_Surface* candy_surfaces[7]);





#endif // __GRID_H__

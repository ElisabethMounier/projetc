#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define WINDOW_HEIGH  800
#define WINDOW_WIDTH 1280
#define MAX_BUTTON_PER_VIEW 5

enum E_layout // E comme enum
{
	E_main_menu,
	E_level_menu,
	E_help_menu,
	E_level1_menu,
	E_win_menu,
	E_lose_menu,
	E_max_nb_menu
};

typedef struct Layout Layout; //on le définit ici car la structure Button a besoin du Layout (et le Layout n'est défini qu'après)

typedef int (*ButtonHandler)(Layout * l, void * memo);

typedef struct
{
	SDL_Rect attributs;
	ButtonHandler handler;	// fonction qu'on appelle en cliquant sur le bouton
}Button;


struct Layout 
{
	SDL_Renderer * renderer;
	SDL_Texture * texture[E_max_nb_menu];
	Button buttons[E_max_nb_menu][MAX_BUTTON_PER_VIEW];
	int nb_button_in_layout[E_max_nb_menu];
	enum E_layout current_layout;
};



int create_menus(SDL_Window *, Layout *);

#endif // __DISPLAY_H__

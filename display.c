#include <SDL.h>

#include "display.h"


static int _exit(){
	SDL_Quit();
	return 0;
	
}

static void _change_menu(Layout * l, enum E_layout layout)
{
	l->current_layout = layout;
	//SDL_RenderClear( l->renderer );
	SDL_RenderCopy(l->renderer, l->texture[layout], NULL, NULL);
	SDL_RenderPresent(l->renderer);
}

static int _get_level_menu(Layout * l, void * memo)
{
	_change_menu(l, E_level_menu);
	return 0;
} 

static int _get_main_menu(Layout * l, void * memo)
{
	_change_menu(l, E_main_menu);
	return 0;
}

static int _get_help_menu(Layout * l, void * memo)
{
	_change_menu(l, E_help_menu);
	return 0;
} 

static int _get_level1_menu(Layout * l, void * memo)
{
	_change_menu(l, E_level1_menu);
	return 0;
}

static void  _init_layout(Layout * l)
{
	int i;
	l->current_layout = E_main_menu; //dit quel est le menu actuel
	for(i = 0; i < E_max_nb_menu; i++)
	{
		l->nb_button_in_layout[i] = 0;
		l->texture[i] = SDL_CreateTexture(l->renderer ,SDL_PIXELFORMAT_RGB888,SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGH ); // initialise une texture vide
	}
}

static int _add_background_to_menu(Layout * l, enum E_layout e, char * image)
{
	SDL_Texture * temp_texture; // texture temporaire
	SDL_Surface * temp_surface = SDL_LoadBMP(image);

	SDL_SetRenderTarget(l->renderer,l->texture[e]); // renderer pointe vers la texture du layout

	temp_surface = SDL_LoadBMP(image);
	temp_texture = SDL_CreateTextureFromSurface(l->renderer,temp_surface);
	SDL_RenderCopy(l->renderer, temp_texture, NULL, NULL);

	SDL_SetRenderTarget(l->renderer,NULL); // enlève le pointeur
	return 0;
}

static int _add_button_to_menu(Layout * l, int x, int y, ButtonHandler bh, enum E_layout e, char * image) //layout en paramètre car les boutons sont définis dedans
{
	SDL_Texture * temp_texture; 
	SDL_Surface * temp_surface = IMG_Load(image);
	Button * b = l->buttons[e];

	SDL_SetRenderTarget(l->renderer,l->texture[e]);

	if (l->nb_button_in_layout[e] >= MAX_BUTTON_PER_VIEW)
	{
		printf("Too many buttons in the view\n");
		return -1;
	}

	b[l->nb_button_in_layout[e]].attributs.x = x;
	b[l->nb_button_in_layout[e]].attributs.y = y;
	b[l->nb_button_in_layout[e]].attributs.w = temp_surface->w;
	b[l->nb_button_in_layout[e]].attributs.h = temp_surface->h;
	b[l->nb_button_in_layout[e]].handler = bh;

	temp_texture = SDL_CreateTextureFromSurface(l->renderer,temp_surface);
	SDL_RenderCopy(l->renderer, temp_texture, NULL, &(b[l->nb_button_in_layout[e]].attributs));

	SDL_SetRenderTarget(l->renderer,NULL);

	l->nb_button_in_layout[e] += 1;
	return 0;
}

static int _add_grid_to_menu(Layout * l, int x, int y, enum E_layout e, char * image)
{
	SDL_Texture * temp_texture; 
	SDL_Surface * temp_surface = IMG_Load(image);
	SDL_Rect rect;

	SDL_SetRenderTarget(l->renderer,l->texture[e]);

	rect.x = x;
	rect.y = y;
	rect.w = temp_surface->w;
	rect.h = temp_surface->h;

	temp_texture = SDL_CreateTextureFromSurface(l->renderer,temp_surface);
	SDL_RenderCopy(l->renderer, temp_texture, NULL, &rect);

	SDL_SetRenderTarget(l->renderer,NULL);

	return 0;
}




/*static int _add_grid_to_menu(Layout * l)
{
	MaTexture* gSpriteSheetTexture = maTexture_create();
	MaTexture* gridCandy = maTexture_create();
	SDL_Texture * temp_texture; 

	SDL_Rect stretchRect; 
	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = 600; 
	stretchRect.h = 467;

	SDL_Rect spritcandies[6][5];


	RGB couleur_sprite_candy={0 ,0, 0};
	int grid[5][8];

	SDL_SetRenderDrawColor( l->renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	gridCandy=loadMaTexture2( "gridCandy.bmp",l->renderer,couleur_sprite_candy);
	gSpriteSheetTexture=loadMaTexture2( "gridCandy.bmp" ,l->renderer,couleur_sprite_candy);

	int i,j;
	for(i = 0; i < 6;i++){
		for(j=0;j<5;j++){
			spritcandies[ i ][ j ].x = i*100; spritcandies[ i ][ j ].y = j*93; spritcandies[ i ][ j ].w = 100; spritcandies[ i ][ j ].h = 93;
		}
	}
	void initGrid() {
  		for (i=0; i<5; i++) {
    			for (j=0; j<8; j++) {
      				grid[i][j]=rand()%6+1;
    			}
  		}
	}

	initGrid();
	SDL_RenderClear( l->renderer );
	i=0;
	for (i=0; i<5; i++) {
    					for (j=0; j<8; j++) {	
    						printf("%d",grid[i][j]);
						render( i*100,j*93 ,gridCandy,l->renderer,&spritcandies[ grid[i][j]-1][0]);
					}
				}

	SDL_SetRenderDrawColor( l->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        			//SDL_RenderClear( gRenderer );
        
        			//render( 0,0 ,accueil1,gRenderer,&spritcandies[ 0][2]);
        
        			SDL_RenderPresent( l->renderer );


	SDL_SetRenderTarget(l->renderer,NULL);

	return 0;

} */

int create_menus(SDL_Window * window, Layout * l)
{
		
	l->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED); // récupère le renderer
	if(l->renderer == NULL)
		printf("%s\n", SDL_GetError());

	_init_layout(l);
	SDL_RenderClear( l->renderer );
	/***************************************/
	/*             MAIN_MENU               */
	/***************************************/

	_add_background_to_menu(l, E_main_menu, "background.bmp");
	
	_add_button_to_menu(l, 400, 200,_get_level_menu, E_main_menu, "buttonStart.png");
		
	_add_button_to_menu(l, 400, 500,_get_help_menu, E_main_menu, "buttonHelp.png");
		
	_add_button_to_menu(l, 1050, 700,_exit, E_main_menu, "buttonExit.png");

	
	
	/***************************************/
	/*            LEVEL_MENU               */
	/***************************************/

	_add_background_to_menu(l, E_level_menu, "background.bmp");
	_add_button_to_menu(l, 650, 100,_get_level1_menu, E_level_menu, "buttonLevel1.png");
	_add_button_to_menu(l, 650, 300,_get_main_menu, E_level_menu, "buttonLevel2.png");
	_add_button_to_menu(l, 650, 500,_get_main_menu, E_level_menu, "buttonLevel3.png");
	_add_button_to_menu(l, 1050, 700,_exit, E_level_menu, "buttonExit.png");
	_add_button_to_menu(l, 100, 400,_get_main_menu, E_level_menu, "buttonMainMenu.png");

		
	/***************************************/
	/*             HELP_MENU               */
	/***************************************/

	_add_background_to_menu(l, E_help_menu, "background.bmp"); 
	_add_button_to_menu(l,100, 400,_get_main_menu, E_help_menu, "buttonMainMenu.png"); 

	
	/***************************************/
	/*             LEVEL1_MENU             */
	/***************************************/

	_add_background_to_menu(l, E_level1_menu, "background.bmp");
	_add_button_to_menu(l,20, 650,_get_level_menu, E_level1_menu, "back.png");
	_add_button_to_menu(l,20, 200,_get_level1_menu, E_level1_menu, "moves.png");
	_add_button_to_menu(l,20, 400,_get_level1_menu, E_level1_menu, "Score.png");
	_add_button_to_menu(l,900, 30,_get_level1_menu, E_level1_menu, "target.png");
	_add_grid_to_menu(l, 380, 150, E_level1_menu, "grid.bmp");

	
	SDL_RenderCopy(l->renderer, l->texture[l->current_layout], NULL, NULL);

	return 0;
}

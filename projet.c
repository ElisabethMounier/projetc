#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "init.h"

#define GRAVITE 0.2
#define VITESSE 0.2
#define HAUT_PERSO 45
#define LARG_PERSO 35

int cle = 0 ;
int sonKey = 0;

//code un peu commenté mais à factoriser/diviser

static void quit(int rc)
{
	SDL_Quit();
	exit(rc);
}

void initSDL(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
	}
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		printf( "Warning: Linear texture filtering not enabled!" );
	}
}


MaTexture* maTexture_create(){
	MaTexture *text = malloc(sizeof(MaTexture));
	text->texture = NULL;
	text->width = 0;
	text->height = 0;

	return text;
}


void freeMaTexture(MaTexture *t){
	SDL_DestroyTexture(t->texture);
}


int main(int argc, char *argv[])
{
////////////////////////////////début initialisation/////////////////////////////////////
	SDL_Window *window;
	SDL_Event e;
	SDL_Surface* gScreenSurface = NULL;
	//SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ]; 
	SDL_Surface* gCurrentSurface = NULL;

	//The window renderer 
	SDL_Renderer* gRenderer = NULL;
	//Current displayed texture 
	SDL_Texture* gTexture;
	
	MaTexture* gSpriteSheetTexture = maTexture_create();
	
	MaTexture* accueil1 = maTexture_create();
	

	SDL_Rect spritcandies[6][5];
	


	int done;
	SDL_Rect stretchRect; 
	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = 600; 
	stretchRect.h = 467;
	
	RGB couleur = { 255,255,255}; 

	RGB couleur_sprite={64 ,64, 64};
	RGB couleur_sprite_candy={0 ,0, 0};
	int grid[5][8];

	

	
	//initialisation SDL 
	initSDL();
	
	//initialisation fenêtre
	/* Set 500x500 video mode */
	window = SDL_CreateWindow("Candy crush",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 800, SDL_WINDOW_SHOWN);


	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create 600x480 window: %s\n",
			SDL_GetError());
		quit(2);
	}

	

	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

	if( gRenderer == NULL ) { 
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
		return 0; 
	} 

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	int imgFlags = IMG_INIT_PNG; 
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) { 
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); 
		return 0; 
	}


	accueil1=loadMaTexture2( "images/candyfdnoir.png",gRenderer,couleur_sprite_candy );
	if( accueil1->texture==NULL ) 
	{ 
		printf( "Failed to load Foo' texture image1!\n" ); 
		return 0; 
	}
	
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	gSpriteSheetTexture=loadMaTexture2( "images/candyfdnoir.png" ,gRenderer,couleur_sprite_candy);
	if( gSpriteSheetTexture->texture==NULL ) 
	{ 
		printf( "Failed to load Foo' texture image!\n" ); 
		return 0; 
	} 

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



    //////////////////fin initialisation//////////////////////////////

			done = 0;
			i=0;
			int mouvement=0;
			int accueil=0;
			while (!done && !accueil) {
				SDL_Delay(400);
				initGrid();
				SDL_RenderClear( gRenderer );
				for (i=0; i<5; i++) {
    					for (j=0; j<8; j++) {	
    						printf("%d",grid[i][j]);
						render( i*100,j*93 ,accueil1,gRenderer,&spritcandies[ grid[i][j]-1][0]);
					}
				}
				if (SDL_PollEvent(&e))
					if(e.type==SDL_KEYDOWN) {

						switch( e.key.keysym.sym ) { 
							case SDLK_SPACE:
            							{    // accleration
            								accueil=1;
            								break;
            							}
            						default: 
            							break; 
            					}
            				}
            				else if(e.type==SDL_QUIT){

            					done = 1;
            				}		
        			
        			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        			//SDL_RenderClear( gRenderer );
        
        			//render( 0,0 ,accueil1,gRenderer,&spritcandies[ 0][2]);
        
        			SDL_RenderPresent( gRenderer );
    			}



}

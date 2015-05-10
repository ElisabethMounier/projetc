#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


SDL_Surface* loadSurface( char* path,SDL_Surface* gScreenSurface) { 
	//The final optimized image 
	SDL_Surface* optimizedSurface = NULL; //Load image at specified path 
	//SDL_Surface* loadedSurface = SDL_LoadBMP( path); 
	SDL_Surface* loadedSurface = IMG_Load( path);
	if( loadedSurface == NULL ) { 
		printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() ); 
	}

	else { 
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL ); 
		if( optimizedSurface == NULL ) { 
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
		} //Get rid of old loaded surface 
			SDL_FreeSurface( loadedSurface ); 
	} 
	return optimizedSurface;
} 


SDL_Texture* loadTexture( char* path,SDL_Renderer* gRenderer ) { 
//The final texture 
	SDL_Texture* newTexture = NULL; 
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path ); 
	if( loadedSurface == NULL ) { 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() ); 
	} 
	else { 
	//Create texture from surface pixels 

		
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); 
		if( newTexture == NULL ) { 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() ); 
		} //Get rid of old loaded surface 
		SDL_FreeSurface( loadedSurface ); 
	} 
	return newTexture; 
}

MaTexture* loadMaTexture2( char* path,SDL_Renderer* gRenderer , RGB r1) { 
//The final texture 

	MaTexture* newTexture=(MaTexture*)malloc(sizeof(MaTexture));
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path ); 
	if( loadedSurface == NULL ) { 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() ); 
	} 
	else { 
	//Create texture from surface pixels 

		/*ColorKeying*/
		
			SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, r1.R, r1.G, r1.B ) );
		
		newTexture->texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); 
		newTexture->width = loadedSurface->w; 
		newTexture->height = loadedSurface->h;
		if( newTexture->texture == NULL ) { 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() ); 
		} //Get rid of old loaded surface 

		SDL_FreeSurface( loadedSurface ); 
	} 

	return newTexture; 
}
/*
int loadMedia(SDL_Surface* gKeyPressSurfaces[],SDL_Surface* gScreenSurface) { 
	int success = 1; //Load default surface 
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "images/sprite_sonic.png",gScreenSurface ); 
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL ) {
 		printf( "Failed to load default image!\n" ); success = 0; 
 	} 
 	//Load up surface 
 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "images/up.bmp" ,gScreenSurface); 
 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL ) { 
 		printf( "Failed to load up image!\n" ); 
 		success = 0; 
 	} 
 	//Load down surface 
 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "images/down.bmp",gScreenSurface ); 
 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL ) { 
 	printf( "Failed to load down image!\n" ); success = 0; 
 	} 
 	//Load left surface 
 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "images/left.bmp",gScreenSurface ); 
 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL ) { 
 	printf( "Failed to load left image!\n" ); success = 0; 
 	} 
 	//Load right surface 
 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "images/right.bmp",gScreenSurface ); 
 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL ) { 
 		printf( "Failed to load right image!\n" ); success = 0; 
 	} 
	return success; 
}
*/

MaTexture* loadFromRenderedText( char* textureText, SDL_Renderer* gRenderer,SDL_Color textColor ,TTF_Font* gFont) { 
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText, textColor ); 
	MaTexture* newTexture=(MaTexture*)malloc(sizeof(MaTexture));
	if( textSurface == NULL ) { 
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); 
		} 
	else { 
		
		newTexture->texture = SDL_CreateTextureFromSurface( gRenderer, textSurface ); 
		if( newTexture == NULL ) { 
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() ); 
		} 
		else { 
			//Get image dimensions 
			newTexture->width = textSurface->w; 
			newTexture->height = textSurface->h; 
		} //Get rid of old surface 
		SDL_FreeSurface( textSurface ); 
		} //Return success 
	return newTexture; 
}

 
 	 
void render( int x, int y ,MaTexture* mTexture,SDL_Renderer* gRenderer,SDL_Rect* clip) { //Set rendering space and render to screen 
	SDL_Rect renderQuad = { x, y, mTexture->width, mTexture->height }; 
	if( clip != NULL ) { 
		renderQuad.w = clip->w;
		renderQuad.h = clip->h; 
	} 
	SDL_RenderCopy( gRenderer, mTexture->texture, clip, &renderQuad ); 
}

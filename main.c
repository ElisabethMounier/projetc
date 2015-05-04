#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv){

  /* initialisation de la SDL */
  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
      fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
      return -1;
    }
  else
    {
      /* Création de la fenêtre */
      SDL_Window* window = NULL;
      //The surface contained by the window
      SDL_Surface* gScreenSurface = NULL;
      SDL_Surface* image = NULL;
      SDL_Event event;
      SDL_Renderer* renderer = NULL;
      SDL_Rect positionFond;

      int exit = 0;

      window = SDL_CreateWindow("Candy Crush Saga",SDL_WINDOWPOS_UNDEFINED, 
				SDL_WINDOWPOS_UNDEFINED,1280, 800, SDL_WINDOW_SHOWN);
      /*création du renderer */
        
        renderer =  SDL_CreateRenderer( window, 0, SDL_RENDERER_ACCELERATED); 
      /* Initialisations */
      //Get window surface
      gScreenSurface = SDL_GetWindowSurface( window );
    
      image = SDL_LoadBMP( "imageDeFond.bmp" );

      //Apply the image
      SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,image);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
      
      //Update the surface
      //SDL_UpdateWindowSurface( window );

      if(window)
        {
	  
	  
	  
	  /* Boucle principale */
	  while(!exit){

	    while(SDL_PollEvent(&event))
	      {
		switch(event.type)
		  {
		  case SDL_WINDOWEVENT:
		    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
		      exit = 1;
		    break;
	  
		  }
  
    
	      }
 

	  }

	 
	  /* Destructions */

	  /* Destruction de la fenêtre */
	  SDL_DestroyWindow(window);
        }
      else
        {
	  fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }
  /* Fermeture de la SDL */
  SDL_Quit();
    
  return 0;
}


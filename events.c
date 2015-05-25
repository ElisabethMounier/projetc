#include <SDL.h>
#include <stdbool.h>
#include "game.h"
#include "events.h"
#include "display.h" // car on utilise button et layout

static bool _click_is_in_button(int x, int y, SDL_Rect rect) // pas besoin d'écrire son prototype (car static) dans .h
{
	if(x > rect.x && x < (rect.x + rect.w) &&
	   y > rect.y && y < (rect.y + rect.h))
	{
		return true;
	}
	return false;
}

static int _get_button_clicked(int x, int y, Button * buttons) // x et y : coordoonnées du clic de la souris
{
	int i;
	for(i = 0; i < MAX_BUTTON_PER_VIEW; i++)
	{
		if(_click_is_in_button(x, y, buttons[i].attributs))
			return i;
	}
	return -1;
}

bool events_handler(SDL_Event e, Layout * l,int *click1,int *click2)
{
	int button_clicked;
	//printf("oui");
	while(SDL_PollEvent(&e)){
	
		switch(e.type)
		{
			case SDL_WINDOWEVENT:
				if(e.window.event == SDL_WINDOWEVENT_CLOSE)
					return true;
			break;

			case SDL_MOUSEBUTTONUP:
				
				if(e.button.button == SDL_BUTTON_LEFT)
				{
					if(l->current_layout==E_level1_menu){
						button_clicked = _get_button_clicked(e.motion.x, e.motion.y, l->buttons[l->current_layout]);

					if(button_clicked < 0)
						{if(!(*click1)){					
						SDL_GetMouseState( &x11, &y11 );
						*click1=1;
							//printf("x11=%d y11=%d\n",x11,y11);			
						}					
						else{
							SDL_GetMouseState( &x22, &y22 );
							*click2=1;
							//printf("x22=%d y22=%d\n",x22,y22);
						}
					break;}

					l->buttons[l->current_layout][button_clicked].handler(l,NULL);
						
						
					}
					else{
					button_clicked = _get_button_clicked(e.motion.x, e.motion.y, l->buttons[l->current_layout]);

					if(button_clicked < 0)
						break;

					l->buttons[l->current_layout][button_clicked].handler(l,NULL);
					}
				}
			break;

			default:
			break;
		}break;
	}
	return false;
}

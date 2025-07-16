#include "application.h"

void event_handler(App *app){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				app_cleanup(app, EXIT_SUCCESS);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode){
					case SDL_SCANCODE_ESCAPE:
						app_cleanup(app, EXIT_SUCCESS);
						break;
					case SDL_SCANCODE_SPACE:
						app->wallblock = !app->wallblock;
						printf("[ %s ] wallblock \n", (app->wallblock)?"ON":"OFF");
						break;
					case SDL_SCANCODE_RETURN:
						app->startautomata = !app->startautomata;
						printf("[ %s ] automata \n", (app->startautomata)?"ON":"OFF");
						break;
					case SDL_SCANCODE_J:
						app->mouse.tmplt_indx++;
						app->mouse.tmplt_indx %= MAX_TEMPLATES;
						break;
					case SDL_SCANCODE_K:
						app->mouse.tmplt_indx--;
						if (app->mouse.tmplt_indx == -1){ 
							app->mouse.tmplt_indx += MAX_TEMPLATES;
						}
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				app->mouse.buttondown = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				app->mouse.buttondown = 0;
				break;
			default:
				break;
		}
	}
}

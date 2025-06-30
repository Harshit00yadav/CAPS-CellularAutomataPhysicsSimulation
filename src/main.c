#include <stdio.h>
#include <stdbool.h>
#include "event_handlers.h"
#include "application.h"
#include "load_resources.h"

int main(){
	printf("Startin Application\n");
	App app;
	SDL_Rect rect;
	rect.x = 10;
	rect.y = 10;
	rect.w = 50;
	rect.h = 50;
	// Colors colors;
	if (sdl_init(&app)){
		app_cleanup(&app, EXIT_FAILURE);
		return 1;
	}
	if (load_media(&app)){
		app_cleanup(&app, EXIT_FAILURE);
		return 1;
	}
	// color_init(&colors);
	SDL_Event event;
	while (true){
		rect.x++;
		rect.y++;
		event_handler(&app, &event);
		SDL_SetRenderDrawColor(app.renderer, 15, 15, 15, 255);
		SDL_RenderClear(app.renderer);
		// SDL_RenderCopy(app.renderer, app.background, NULL, NULL);
		SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(app.renderer, &rect);
		SDL_RenderPresent(app.renderer);
		SDL_Delay(16);
	}
	app_cleanup(&app, EXIT_SUCCESS);
	printf("--[ FINISHED ]--\n");
	return 0;
}

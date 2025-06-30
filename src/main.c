#include <stdio.h>
#include <stdbool.h>
#include "event_handlers.h"
#include "application.h"

int main(){
	printf("Startin Application\n");
	App app;
	if (sdl_init(&app)){
		app_cleanup(&app, EXIT_FAILURE);
		return 1;
	}
	SDL_Event event;
	while (true){
		event_handler(&app, &event);
		SDL_RenderClear(app.renderer);
		SDL_RenderPresent(app.renderer);
		SDL_Delay(16);
	}
	app_cleanup(&app, EXIT_SUCCESS);
	printf("--[ FINISHED ]--\n");
	return 0;
}

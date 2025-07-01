#include <stdio.h>
#include <stdbool.h>
#include "event_handlers.h"
#include "application.h"

void initialize(App *app){
	if (sdl_init(app)){
		app_cleanup(app, EXIT_FAILURE);
	}
}

int main(){
	printf("Startin Application\n");
	Uint64 now, last;
	double delta=0, fps=0;
	now = SDL_GetPerformanceCounter();
	last = 0;
	App app;
	initialize(&app);
	while (true){
		last = now;
		now = SDL_GetPerformanceCounter();
		delta = (double)((now - last) * 1000) / SDL_GetPerformanceFrequency(); // in milliseconds
    fps = 1000.0 / delta;

		SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
		event_handler(&app);
		update(&app);
		render(&app);

		printf("FPS: %.2f\r", fps);
	}
	app_cleanup(&app, EXIT_SUCCESS);
	return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 600
#define SCREEN_HIGHT 400
#define SCREEN_TITLE "Cellular Automata"

typedef struct APP {
	SDL_Window *window;
	SDL_Renderer *renderer;
} App;

// functions
bool sdl_init(App *app);
void app_cleanup(App *app);

// start of program 
int main(){
	printf("Startin Application\n");
	App app;
	if (sdl_init(&app)){
		app_cleanup(&app);
		return 1;
	}
	SDL_RenderClear(app.renderer);
	SDL_RenderPresent(app.renderer);
	SDL_Delay(5000);

	app_cleanup(&app);
	printf("--[ FINISHED ]--\n");
	return 0;
}

// functions 
bool sdl_init(App *app){
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error Initializing SDL: %s\n", SDL_GetError());
		return true;
	}
	app->window = SDL_CreateWindow(
		SCREEN_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HIGHT,
		0
	);
	if (!app->window){
		fprintf(stderr, "Error Creating Window: %s\n", SDL_GetError());
		return true;
	}
	app->renderer = SDL_CreateRenderer(app->window, -1, 0);
	if (!app->renderer){
		fprintf(stderr, "Error Creating Renderer: %s\n", SDL_GetError());
		return true;
	}
	return false;
}

void app_cleanup(App *app){
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
}

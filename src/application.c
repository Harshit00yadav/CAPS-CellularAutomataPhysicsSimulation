#include "application.h"
#include "base.h"

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
	app->grid = grid_initialize(app->renderer, GRID_WIDTH, GRID_HIGHT, CELL_SIZE);
	if (!app->grid){
		return true;
	}
	app->startautomata = 0;
	app->mouse.buttondown = 0;
	app->mouse.x = 0;
	app->mouse.y = 0;
	return false;
}

void app_cleanup(App *app, int exit_status){
	grid_destroy(app->grid);
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
	printf("--[ FINISHED ]--\n");
	exit(exit_status);
}

void update(App *app){
	int j = app->mouse.y / (CELL_SIZE + CELL_SEPRATION);
	int i = app->mouse.x / (CELL_SIZE + CELL_SEPRATION);
	if (app->mouse.buttondown && i < app->grid->width && j < app->grid->hight){
		app->grid->cells[j][i].active = 1;
	}
}

void render(App *app){
	SDL_SetRenderDrawColor(app->renderer, 15, 15, 15, 255);
	SDL_RenderClear(app->renderer);
	grid_render(app->renderer, app->grid, app->startautomata);
	SDL_RenderPresent(app->renderer);
}

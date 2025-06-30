#include "application.h"

bool sdl_init(App *app){
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error Initializing SDL: %s\n", SDL_GetError());
		return true;
	}
	int img_init = IMG_Init(IMAGE_FLAG);
	if ((img_init & IMAGE_FLAG) != IMAGE_FLAG){
		fprintf(stderr, "Error Initializing SDL_image: %s\n", IMG_GetError());
		return true;
	}
	if (TTF_Init()){
		fprintf(stderr, "Error Initializing SDL_ttf: %s\n", TTF_GetError());
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

void app_cleanup(App *app, int exit_status){
	TTF_CloseFont(app->text_font);
	SDL_DestroyTexture(app->background);
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(exit_status);
}

void color_init(Colors *colors){
	colors->fg_text.a = 255;
	colors->fg_text.r = 255;
	colors->fg_text.g = 255;
	colors->fg_text.b = 155;
	colors->err_text.a = 255;
	colors->err_text.r = 255;
	colors->err_text.g = 0;
	colors->err_text.b = 0;
}

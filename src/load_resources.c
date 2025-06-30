#include "load_resources.h"

bool load_media(App *app){
	app->background = IMG_LoadTexture(app->renderer, "./assets/wallhaven-berserk.jpg");
	if (!app->background){
		fprintf(stderr, "Error creating texture: %s\n", IMG_GetError());
		return true;
	}
	app->text_font = TTF_OpenFont("./assets/fonts/ShureTechMonoNerdFont-Regular.ttf", FONT_SIZE);
	if (!app->text_font){
		fprintf(stderr, "Error creating ttf font: %s\n", TTF_GetError());
		return true;
	}
	return false;
}

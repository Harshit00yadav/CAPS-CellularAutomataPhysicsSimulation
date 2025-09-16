#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "grid.h"
#include "base.h"
#include "controlboard.h"

#ifndef APPLICATION_H
#define APPLICATION_H

typedef struct APP {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Grid *grid;
	Mouse mouse;
	int startautomata;
	int wallblock;
	CB_Vars *cbvars;
} App;

#endif

bool sdl_init(App *app);
void app_cleanup(App *app, int exit_status);
void update(App *app);
void render(App *app);

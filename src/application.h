#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "grid.h"
#include "base.h"

#ifndef APPLICATION_H
#define APPLICATION_H
typedef struct APP App;
typedef struct MOUSE Mouse;

typedef struct MOUSE {
	int x;
	int y;
	int buttondown;
	char *tmplts[MAX_TEMPLATES];
	int tmplt_indx;
} Mouse;

typedef struct APP {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Grid *grid;
	Mouse mouse;
	int startautomata;
	int wallblock;
} App;

#endif

bool sdl_init(App *app);
void app_cleanup(App *app, int exit_status);
void update(App *app);
void render(App *app);

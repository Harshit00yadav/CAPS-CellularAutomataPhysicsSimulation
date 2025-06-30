#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 600
#define SCREEN_HIGHT 400
#define SCREEN_TITLE "Cellular Automata"

#ifndef APPLICATION_H
#define APPLICATION_H
typedef struct APP App;

typedef struct APP {
	SDL_Window *window;
	SDL_Renderer *renderer;
} App;

#endif

bool sdl_init(App *app);
void app_cleanup(App *app, int exit_status);

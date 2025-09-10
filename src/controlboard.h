#include "base.h"

#ifndef CONTROLBOARD_H
#define CONTROLBOARD_H

typedef struct CONTROL_BOARD_VARIABLES {
	SDL_Surface *board_surface;
	SDL_Texture *board_texture;
	SDL_Rect surf_rect;
} CB_Vars;

CB_Vars *initialize_control_board(SDL_Renderer *renderer);
void destroy_control_board(CB_Vars *vars);
void cboard_render(SDL_Renderer *renderer, CB_Vars *vars);
#endif

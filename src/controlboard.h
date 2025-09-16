#include "base.h"

#ifndef CONTROLBOARD_H
#define CONTROLBOARD_H

#define NO_OF_BUTTONS 2
#define BUTTON_HOVER_STROKE 1

#define automata_btn_padding 10
#define automata_btn_w CONTROLBOARD_WIDTH - 2 * automata_btn_padding
#define automata_btn_h 20
#define automata_btn_x automata_btn_padding
#define automata_btn_y SCREEN_HIGHT - automata_btn_h - automata_btn_padding

#define wall_btn_padding 10
#define wall_btn_w CONTROLBOARD_WIDTH - 2 * wall_btn_padding
#define wall_btn_h 20
#define wall_btn_x wall_btn_padding
#define wall_btn_y SCREEN_HIGHT - wall_btn_h * 2 - wall_btn_padding * 2

#define CB_NAME_SIZE 25

typedef struct CB_BUTTON {
	char name[CB_NAME_SIZE];
	SDL_Rect rect;
	bool hover;
	bool clicked;
} CB_Button;

typedef struct CONTROL_BOARD_VARIABLES {
	SDL_Surface *board_surface;
	SDL_Texture *board_texture;
	SDL_Rect surf_rect;
	CB_Button *buttons;
	bool active;
} CB_Vars;

void init_button(CB_Button *btn, char *name, int x, int y, int w, int h);
CB_Vars *initialize_control_board(SDL_Renderer *renderer);
void destroy_control_board(CB_Vars *vars);
void cboard_update(CB_Vars *vars, Mouse mouse);
void cboard_render(SDL_Renderer *renderer, CB_Vars *vars);
#endif

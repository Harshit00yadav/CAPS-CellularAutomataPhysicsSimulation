#include "controlboard.h"

void init_button(CB_Button *btn, char *name, int x, int y, int w, int h){
	printf("* Initializing button %s.\r", name);
	btn->hover = false;
	btn->clicked = false;
	memcpy(btn->name, name, strlen(name));
	btn->rect.x = x;
	btn->rect.y = y;
	btn->rect.w = w;
	btn->rect.h = h;
	printf("\u2713\n");
}

CB_Vars *initialize_control_board(SDL_Renderer *renderer){
	printf("* Initializing Controll Board.\n");
	CB_Vars *vars = malloc(sizeof(CB_Vars));
	vars->active = true;
	vars->board_surface = SDL_CreateRGBSurface(
		0,
		CONTROLBOARD_WIDTH,
		SCREEN_HIGHT,
		32,
		0xFF000000,
		0x00FF0000,
		0x0000FF00,
		0x000000FF
	);
	vars->board_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, CONTROLBOARD_WIDTH, SCREEN_HIGHT);
	vars->surf_rect.x = 0;
	vars->surf_rect.y = 0;
	vars->surf_rect.w = CONTROLBOARD_WIDTH;
	vars->surf_rect.h = SCREEN_HIGHT;

	vars->buttons = malloc(sizeof(CB_Button) * NO_OF_BUTTONS);
	init_button(
		&vars->buttons[0],
		"START",
		automata_btn_x, 
		automata_btn_y, 
		automata_btn_w, 
		automata_btn_h 
	);
	init_button(
		&vars->buttons[1],
		"Wall",
		wall_btn_x, 
		wall_btn_y, 
		wall_btn_w, 
		wall_btn_h 
	);
	printf("\u2713 Initialized Controll Board.\n");
	return vars;
}

void destroy_control_board(CB_Vars *vars){
	printf("* Distroying contoll board variables\r");
	free(vars->buttons);
	SDL_FreeSurface(vars->board_surface);
	SDL_DestroyTexture(vars->board_texture);
	printf("\u2713\n");
}

void cboard_update(CB_Vars *vars, Mouse mouse){
	for (int i=0; i<NO_OF_BUTTONS; i++){
		CB_Button *btn = &vars->buttons[i];
		if (mouse.x >= btn->rect.x && mouse.x <= btn->rect.x+btn->rect.w && mouse.y >= btn->rect.y && mouse.y <= btn->rect.y+btn->rect.h){
			btn->hover = true;
			if (mouse.buttondown){
				btn->clicked = true;
			}
		} else {
			btn->hover = false;
		}
	}
}

void cboard_render(SDL_Renderer *renderer, CB_Vars *vars){
	SDL_FillRect(vars->board_surface, NULL, SDL_MapRGB(vars->board_surface->format, 0, 0, 0));
	// Draw buttons
	SDL_Rect outline;
	CB_Button *btn;
	for (int i=0; i<NO_OF_BUTTONS; i++){
		btn = &vars->buttons[i];
		if (btn->hover){
			outline.x = btn->rect.x - (BUTTON_HOVER_STROKE + 2);
			outline.y = btn->rect.y - (BUTTON_HOVER_STROKE + 2);
			outline.w = btn->rect.w + 2 * (BUTTON_HOVER_STROKE + 2);
			outline.h = btn->rect.h + 2 * (BUTTON_HOVER_STROKE + 2);
			SDL_FillRect(vars->board_surface, &outline, SDL_MapRGB(vars->board_surface->format, 255, 255, 255));
			outline.x = btn->rect.x - 2;
			outline.y = btn->rect.y - 2;
			outline.w = btn->rect.w + 2 * 2;
			outline.h = btn->rect.h + 2 * 2;
			SDL_FillRect(vars->board_surface, &outline, SDL_MapRGB(vars->board_surface->format, 0, 0, 0));
		}
		if (vars->active){
			SDL_FillRect(vars->board_surface, &btn->rect, SDL_MapRGB(vars->board_surface->format, 100, 0, 50));
		} else {
			SDL_FillRect(vars->board_surface, &btn->rect, SDL_MapRGB(vars->board_surface->format, 255, 0, 50));
		}
	}
	SDL_UpdateTexture(vars->board_texture, NULL, vars->board_surface->pixels, vars->board_surface->pitch);
	SDL_RenderCopy(renderer, vars->board_texture, NULL, &vars->surf_rect);
}

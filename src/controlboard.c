#include "controlboard.h"

CB_Vars *initialize_control_board(SDL_Renderer *renderer){
	printf("* Initializing Controll Board.\r");
	CB_Vars *vars = malloc(sizeof(CB_Vars));
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
	printf("\u2713\n");
	return vars;
}

void destroy_control_board(CB_Vars *vars){
	printf("* Distroying contoll board variables\r");
	SDL_FreeSurface(vars->board_surface);
	SDL_DestroyTexture(vars->board_texture);
	printf("\u2713\n");
}

void cboard_render(SDL_Renderer *renderer, CB_Vars *vars){
	SDL_FillRect(vars->board_surface, NULL, SDL_MapRGB(vars->board_surface->format, 255, 0, 100));
	SDL_UpdateTexture(vars->board_texture, NULL, vars->board_surface->pixels, vars->board_surface->pitch);
	SDL_RenderCopy(renderer, vars->board_texture, NULL, &vars->surf_rect);
}

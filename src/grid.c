#include "grid.h"

Grid *grid_initialize(SDL_Renderer *renderer, int width, int hight, int csize){
	Grid *G = (Grid *)malloc(sizeof(Grid));
	G->width = width;
	G->hight = hight;
	G->cell_size = csize;
	G->cells = (Cell **)malloc(hight*sizeof(Cell *));
	if (G->cells == NULL){
		fprintf(stderr, "Failed to allocate memory");
		return NULL;
	}
	for (int i=0; i<hight; i++){
		G->cells[i] = (Cell *)malloc(width*sizeof(Cell));
		if (G->cells[i] == NULL){
			fprintf(stderr, "Failed to allocate memory");
			return NULL;
		}
		for (int j=0; j<G->width; j++){
			G->cells[i][j].value = 0;
			G->cells[i][j].active = 0;
		}
	}
	G->surface = SDL_CreateRGBSurface(
		0,
		SCREEN_WIDTH,
		SCREEN_HIGHT,
		32,
		0xFF000000,
		0x00FF0000,
		0x0000FF00,
		0x000000FF
	);
	G->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HIGHT);
	return G;
}

void grid_destroy(Grid *G){
	SDL_DestroyTexture(G->texture);
	SDL_FreeSurface(G->surface);
	for (int i=0; i<G->hight; i++){
		free(G->cells[i]);
	}
	free(G->cells);
	free(G);
}

void grid_print_stdout(Grid *G){
	for (int i=0; i<G->hight; i++){
		for (int j=0; j<G->width; j++){
			printf("%d ", G->cells[i][j].value);
		}
		printf("\n");
	}
}

void grid_render(SDL_Renderer *renderer, Grid *G){
	SDL_FillRect(G->surface, NULL, SDL_MapRGB(G->surface->format, 0, 0, 0));
	for (int i=0; i<G->hight; i++){
		for (int j=0; j<G->width; j++){
			SDL_Rect r = {j*(G->cell_size+CELL_SEPRATION), i*(G->cell_size+CELL_SEPRATION), G->cell_size, G->cell_size};
			if (G->cells[i][j].active == 1){
				SDL_FillRect(G->surface, &r, SDL_MapRGB(G->surface->format, 255, 255, 255));
			} else{
				SDL_FillRect(G->surface, &r, SDL_MapRGB(G->surface->format, 15, 15, 15));
			}
		}
	}
	SDL_UpdateTexture(G->texture, NULL, G->surface->pixels, G->surface->pitch);
	SDL_RenderCopy(renderer, G->texture, NULL, NULL);
}

#include "grid.h"

Grid *grid_initialize(SDL_Renderer *renderer, int width, int hight, int csize){
	Grid *G = (Grid *)malloc(sizeof(Grid));
	G->width = width;
	G->hight = hight;
	G->cell_size = csize;
	G->cells = (Cell **)malloc(hight*sizeof(Cell *));
	G->buffer = (Cell **)malloc(hight*sizeof(Cell *));
	if (G->cells == NULL){
		fprintf(stderr, "Failed to allocate memory");
		return NULL;
	}
	if (G->buffer == NULL){
		fprintf(stderr, "Failed to allocate memory");
		return NULL;
	}
	for (int i=0; i<hight; i++){
		G->cells[i] = (Cell *)malloc(width*sizeof(Cell));
		G->buffer[i] = (Cell *)malloc(width*sizeof(Cell));
		if (G->cells[i] == NULL){
			fprintf(stderr, "Failed to allocate memory");
			return NULL;
		}
		if (G->buffer[i] == NULL){
			fprintf(stderr, "Failed to allocate memory");
			return NULL;
		}
		for (int j=0; j<G->width; j++){
			G->cells[i][j].value = 0;
			G->cells[i][j].active = 0;
			G->buffer[i][j].value = 0;
			G->buffer[i][j].active = 0;
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
		free(G->buffer[i]);
	}
	free(G->cells);
	free(G->buffer);
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

void grid_render(SDL_Renderer *renderer, Grid *G, int startautomata){
	SDL_FillRect(G->surface, NULL, SDL_MapRGB(G->surface->format, 0, 0, 0));
	for (int i=0; i<G->hight; i++){
		for (int j=0; j<G->width; j++){
			SDL_Rect r = {
				CONTROLBOARD_WIDTH + j*(G->cell_size+CELL_SEPRATION), 
				GRID_OFFSET + i*(G->cell_size+CELL_SEPRATION), 
				G->cell_size, 
				G->cell_size
			};
			if (G->cells[i][j].active == 1){
				SDL_FillRect(G->surface, &r, SDL_MapRGB(G->surface->format, 255, 255, 255));
			} else if (G->cells[i][j].active == -1){
				G->cells[i][j].active = 0;
				SDL_FillRect(G->surface, &r, SDL_MapRGB(G->surface->format, 115, 55, 15));
			} else if (G->cells[i][j].active == -9){
				G->cells[i][j].active = -9;
				SDL_FillRect(G->surface, &r, SDL_MapRGB(G->surface->format, 0, 0, 0));
			} else{
				SDL_FillRect(G->surface, &r, SDL_MapRGB(G->surface->format, 15, 15, 15));
			}
			// TODO: apply automata function
			int *neighbours[8];
			neighbours[0] = &G->cells[(i-1+G->hight)%G->hight][(j-1+G->width)%(G->width)].active;
			neighbours[1] = &G->cells[(i-1+G->hight)%(G->hight)][j].active;
			neighbours[2] = &G->cells[(i-1+G->hight)%(G->hight)][(j+1)%(G->width)].active;
			neighbours[3] = &G->cells[i][(j-1+G->width)%(G->width)].active;
			neighbours[4] = &G->cells[i][(j+1)%(G->width)].active;
			neighbours[5] = &G->cells[(i+1)%(G->hight)][(j-1+G->width)%(G->width)].active;
			neighbours[6] = &G->cells[(i+1)%(G->hight)][j].active;
			neighbours[7] = &G->cells[(i+1)%(G->hight)][(j+1)%(G->width)].active;
			// neighbours[1] = ((i-1)>=0)?&G->cells[(i-1)][(j)].active:NULL;
			// neighbours[2] = ((i-1)>=0 && (j+1)<G->width)?&G->cells[(i-1)][(j+1)].active:NULL;
			// neighbours[3] = ((j-1)>=0)?&G->cells[(i)][(j-1)].active:NULL;
			// neighbours[4] = ((j+1)<G->width)?&G->cells[(i)][(j+1)].active:NULL;
			// neighbours[5] = ((i+1)<G->hight && (j-1)>=0)?&G->cells[(i+1)][(j-1)].active:NULL;
			// neighbours[6] = ((i+1)<G->hight)?&G->cells[(i+1)][(j)].active:NULL;
			// neighbours[7] = ((i+1)<G->hight && (j+1)<G->width)?&G->cells[(i+1)][(j+1)].active:NULL;

			if (G->cells[i][j].value == -1){
				G->buffer[i][j].active = -9;
				continue;
			} else {
				G->buffer[i][j].active = 0;
			}
			G->buffer[i][j].active = cellular_automata_1depth(neighbours, &G->cells[i][j].active);
			// G->buffer[i][j].active = sand_simulation(neighbours, &G->cells[i][j].active);
		}
	}
	if (startautomata){
		for (int i=0; i<G->hight; i++){
			for (int j=0; j<G->width; j++){
				G->cells[i][j].active = G->buffer[i][j].active;
			}
		}
	}
	SDL_UpdateTexture(G->texture, NULL, G->surface->pixels, G->surface->pitch);
	SDL_RenderCopy(renderer, G->texture, NULL, NULL);
}

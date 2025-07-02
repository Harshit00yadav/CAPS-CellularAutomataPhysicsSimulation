#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "base.h"
#include "automata_functions.h"

#ifndef GRID
#define GRID

typedef struct grid Grid;
typedef struct cell Cell;

typedef struct cell{
	int value;
	int active;
} Cell;

typedef struct grid {
	int cell_size;
	int width;
	int hight;
	Cell **cells;
	Cell **buffer;
	SDL_Texture *texture;
	SDL_Surface *surface;
} Grid;

#endif

Grid *grid_initialize(SDL_Renderer *renderer, int w, int h, int csize);
void grid_destroy(Grid *G);
void grid_print_stdout(Grid *G);
void grid_render(SDL_Renderer *renderer, Grid *G, int startautomata);

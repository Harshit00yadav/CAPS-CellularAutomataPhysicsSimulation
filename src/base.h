#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <SDL2/SDL.h>

#ifndef BASE_H
#define BASE_H

#define SCREEN_WIDTH 800
#define SCREEN_HIGHT 600
#define CONTROLBOARD_WIDTH 200
#define BORDER_PADDING 2
#define FPS 60
#define MAX_TEMPLATES 9
#define SCREEN_TITLE "Cellular Automata"
#define CELL_SIZE 3
#define CELL_SEPRATION 1
#define GRID_OFFSET (CELL_SIZE * (BORDER_PADDING/2) * (CELL_SIZE + CELL_SEPRATION))
#define GRID_WIDTH (SCREEN_WIDTH - CONTROLBOARD_WIDTH - GRID_OFFSET/2)/(CELL_SIZE+CELL_SEPRATION)
#define GRID_HIGHT SCREEN_HIGHT/(CELL_SIZE+CELL_SEPRATION) - CELL_SIZE * BORDER_PADDING

typedef struct MOUSE {
	int x;
	int y;
	int buttondown;
	char *tmplts[MAX_TEMPLATES];
	int tmplt_indx;
} Mouse;

#endif

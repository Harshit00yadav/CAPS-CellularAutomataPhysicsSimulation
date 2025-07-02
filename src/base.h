#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SCREEN_WIDTH 600
#define SCREEN_HIGHT 400
#define SCREEN_TITLE "Cellular Automata"
#define CELL_SIZE 3
#define CELL_SEPRATION 1
#define GRID_WIDTH SCREEN_WIDTH/(CELL_SIZE+CELL_SEPRATION)
#define GRID_HIGHT SCREEN_HIGHT/(CELL_SIZE+CELL_SEPRATION) - CELL_SIZE

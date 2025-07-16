#include "automata_functions.h"

int cellular_automata_1depth(int neighbours[], int *self){
	int counter = 0;
	for (int i=0; i<8; i++){
		if (neighbours[i] == 1){
			counter++;
		}
	}
	if (*self == 1){
		return (counter==2 || counter==3)?1:0;
	} else {
		return (counter==3)?1:0;
	}
}

int sand_simulation(int neighbours[], int *self){
	if (*self == 1){
		if (
			(neighbours[6] == 1 || neighbours[6] == -9) &&
			(neighbours[5] == 1 || neighbours[5] == -9) &&
			(neighbours[7] == 1 || neighbours[7] == -9)
		){
			return 1;
		}
	} else {
		if (neighbours[1] == 1){
			return 1;
		}
		if (neighbours[0] == 1 && neighbours[3] == 1){
			*self = 0;
			return 1;
		} else if (neighbours[2] == 1 && neighbours[4] == 1){
			*self = 0;
			return 1;
		}
	}
	return 0;
}

#include "automata_functions.h"

int cellular_automata_1depth(int neighbours[], int self){
	int counter = 0;
	for (int i=0; i<8; i++){
		if (neighbours[i] == 1){
			counter++;
		}
	}
	if (self == 1){
		return (counter==2 || counter==3)?1:0;
	} else {
		return (counter==3)?1:0;
	}
}

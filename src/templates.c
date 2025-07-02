#include "templates.h"

char *load_templates(const char *path){
	FILE *tmplt_ptr;
	char buffer[500];
	char tmplt[500] = "";
	tmplt_ptr = fopen(path, "r");
	while (fgets(buffer, sizeof(buffer), tmplt_ptr) != NULL){
		strcat(tmplt, buffer);
	}
	fclose(tmplt_ptr);
	char *res = (char *)malloc(sizeof(tmplt));
	strcpy(res, tmplt);
	return res;
}

void activate_template(Grid *G, char *tmplt, int x, int y){
	int i = 0;
	int j = 0;
	int k = 0;
	while (tmplt[k] != '\0'){
		if (tmplt[k] == '\n'){
			i = -1;
			j++;
		} else if (tmplt[k] == 'o'){
			G->cells[y+j][x+i].active = 1;
		}
		k++;
		i++;
	}
}

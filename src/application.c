#include "application.h"
#include "templates.h"

bool sdl_init(App *app){
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error Initializing SDL: %s\n", SDL_GetError());
		return true;
	}
	app->window = SDL_CreateWindow(
		SCREEN_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HIGHT,
		0
	);
	if (!app->window){
		fprintf(stderr, "Error Creating Window: %s\n", SDL_GetError());
		return true;
	}
	app->renderer = SDL_CreateRenderer(app->window, -1, 0);
	if (!app->renderer){
		fprintf(stderr, "Error Creating Renderer: %s\n", SDL_GetError());
		return true;
	}
	app->grid = grid_initialize(app->renderer, GRID_WIDTH, GRID_HIGHT, CELL_SIZE);
	if (!app->grid){
		return true;
	}

	char *tmplt_path = "./assets/templates/";
	DIR *d = opendir(tmplt_path);
	if (!d) {
		fprintf(stderr, "Unable to open ./assets/templates\n");
		return true;
	}
	printf("Loading template files\n");
	struct dirent *dir;
	char path_tmplt[1024];
	int indx = 0;
	while ((dir = readdir(d)) != NULL){
		memset(path_tmplt, '\0', sizeof(path_tmplt));
		if (dir->d_type != DT_DIR){
			strcat(path_tmplt, tmplt_path);
			strcat(path_tmplt, dir->d_name);
			printf("%s\n", path_tmplt);
			app->mouse.tmplts[indx] = load_templates(path_tmplt);
			indx++;
		}
	}
	closedir(d);
	printf("Loading completed\n");
	app->startautomata = 0;
	app->wallblock = 0;
	app->mouse.buttondown = 0;
	app->mouse.x = 0;
	app->mouse.y = 0;
	app->mouse.tmplt_indx = 0;
	return false;
}

void app_cleanup(App *app, int exit_status){
	for (int i=0; i<MAX_TEMPLATES; i++){
		free(app->mouse.tmplts[i]);
	}
	grid_destroy(app->grid);
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
	printf("--[ FINISHED ]--\n");
	exit(exit_status);
}

void update(App *app){
	int j = app->mouse.y / (CELL_SIZE + CELL_SEPRATION);
	int i = app->mouse.x / (CELL_SIZE + CELL_SEPRATION);
	highlight_template(app->grid, app->mouse.tmplts[app->mouse.tmplt_indx], i, j);
	if (app->mouse.buttondown && i < app->grid->width && j < app->grid->hight){
		if (app->wallblock){
			activate_template(app->grid, app->mouse.tmplts[app->mouse.tmplt_indx], i, j, -1, -9);
		} else {
			activate_template(app->grid, app->mouse.tmplts[app->mouse.tmplt_indx], i, j, 0, 1);
		}
	}
}

void render(App *app){
	SDL_SetRenderDrawColor(app->renderer, 15, 15, 15, 255);
	SDL_RenderClear(app->renderer);
	grid_render(app->renderer, app->grid, app->startautomata);
	SDL_RenderPresent(app->renderer);
	SDL_Delay(64);
}

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 600
#define SCREEN_HIGHT 400
#define SCREEN_TITLE "Cellular Automata"
#define IMAGE_FLAG IMG_INIT_JPG
#define FONT_SIZE 80  // point size

#ifndef APPLICATION_H
#define APPLICATION_H
typedef struct APP App;
typedef struct COLORS Colors;

typedef struct APP {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background;
	TTF_Font *text_font;
} App;

typedef struct COLORS{
	SDL_Color fg_text;
	SDL_Color err_text;
} Colors;

#endif

bool sdl_init(App *app);
void color_init(Colors *colors);
void app_cleanup(App *app, int exit_status);

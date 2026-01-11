
#ifndef CHIP_8_SCREEN_H
#define CHIP_8_SCREEN_H

#include <SDL_events.h>
#include <SDL_render.h>

typedef struct  {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

} screen_t;

void screen_init(screen_t* screen);
void screen_close(screen_t* screen);
void render_rect(screen_t* screen, int x, int y, int w, int h);


#endif //CHIP_8_SCREEN_H
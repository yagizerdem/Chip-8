#include  "screen.h"
#include <SDL.h>
#include "chip8.h"
#include <stdbool.h>

void screen_init(screen_t* screen) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr,
				"SDL_Init failed\n"
				"Reason: %s\n",
				SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen->window = SDL_CreateWindow(
		"Chip-8 emulator",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_W, SCREEN_H,
		SDL_WINDOW_SHOWN
	);

	if (!screen->window) {
		fprintf(stderr,
				"SDL_CreateWindow failed\n"
				"Reason: %s\n",
				SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen->renderer = SDL_CreateRenderer(
		screen->window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	if (!screen->renderer) {
		fprintf(stderr,
				"SDL_CreateRenderer failed\n"
				"Reason: %s\n",
				SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_SetRenderDrawColor(screen->renderer, 0,0,0,255);
	SDL_RenderClear(screen->renderer);
	SDL_RenderPresent(screen->renderer);
}


void screen_close(screen_t* screen) {
	SDL_DestroyRenderer(screen->renderer);
	SDL_DestroyWindow(screen->window);
	SDL_Quit();
}

void render_rect(screen_t* screen, int x, int y, int w, int h)
{
	SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 255);

	SDL_Rect rect = {
		.x = x,
		.y = y,
		.w = w,
		.h = h
	};

	SDL_RenderFillRect(screen->renderer, &rect);
}
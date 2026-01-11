#include  "emulator.h"
#include <stdbool.h>
#include <stdio.h>
#include "chip8.h"
#include <unistd.h>

#include "screen.h"


void start(char* programPath) {

	chip8_t chip8;
	chip8_init(&chip8);
	loadRom(&chip8, programPath);

	screen_t screen;
	screen_init(&screen);

	bool quit = false;

	while (!quit) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					goto  CLEANUP_AND_QUIT;
				case SDL_KEYDOWN:
					for (int i = 0; i < 16; i++) {
						if (event.key.keysym.sym == KEYMAP[i]) {
							chip8.keypad[i] = 1;
						}
					}
					break;
				case SDL_KEYUP:
					for (int i = 0; i < 16; i++) {
						if (event.key.keysym.sym == KEYMAP[i]) {
							chip8.keypad[i] = 0;
						}
					}
					break;
			}

		}

		for (int i = 0; i < 10; i++) {
			uint16_t instruction = fetch(&chip8);
			execute(&chip8, instruction);
		}


		SDL_SetRenderDrawColor(screen.renderer, 0, 0, 0, 255);
		SDL_RenderClear(screen.renderer);

		// draw all pixels
		for (int i = 0; i < SCHIP_HEIGHT; i++) {
			for (int j = 0 ; j < SCHIP_WIDTH; j++) {
				if (chip8.display[i][j] > 0) {
					render_rect(&screen,
						j *SCREEN_W / SCHIP_WIDTH,
						i* SCREEN_W / SCHIP_WIDTH,
						SCREEN_W / SCHIP_WIDTH,
						SCREEN_H / SCHIP_HEIGHT);
				}
			}
		}

		SDL_RenderPresent(screen.renderer);

		SDL_Delay(16); // 60 FPS

		if (chip8.delayTimer > 0) {
			chip8.delayTimer--;
		}
		if (chip8.soundTimer > 0) {
			chip8.soundTimer--;
		}

	}

	CLEANUP_AND_QUIT:
	screen_close(&screen);
}

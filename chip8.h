#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>


#define SCHIP_WIDTH  64
#define SCHIP_HEIGHT 32
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define NUM_V_REGISTERS 16
#define TRUE 1
#define FALSE 0
#define PROGRAM_START_ADDR 0x200
#define FONTSET_SIZE 80
#define PROGRAM_END_ADDR  0x1000
#define  SCREEN_W 800
#define  SCREEN_H 400
#define NUM_KEYS 16
#define FONT_START_ADDR 0x050

#include <SDL2/SDL.h>

typedef struct {
	uint8_t memory[MEMORY_SIZE]; // 4 kb or memory with word size 16 bits (2 bytes)
	uint8_t display[SCHIP_HEIGHT][SCHIP_WIDTH];
	uint16_t programCounter; // word size 12 bits
	uint16_t indexRegister; // word size 16 bit
	uint16_t stack[STACK_SIZE]; // 16 word stack size with 16 bit words
	uint8_t stackPointer;  // points top of the stack
	uint8_t delayTimer; // 8 bit word size
	uint8_t soundTimer; // 8 bit word size
	uint8_t vRegister[NUM_V_REGISTERS]; // 16 general purpose registers with 8 bit word size

	bool draw_flag;
	uint8_t keypad[16];

} chip8_t;

void chip8_init(chip8_t *c);

/* memory */
uint8_t  chip8_get_memory(const chip8_t *c, uint16_t addr);
void     chip8_set_memory(chip8_t *c, uint16_t addr, uint8_t value);

/* display */
uint8_t  chip8_get_pixel(const chip8_t *c, uint8_t x, uint8_t y);
void     chip8_set_pixel(chip8_t *c, uint8_t x, uint8_t y, uint8_t value);

/* program counter */
uint16_t chip8_get_pc(const chip8_t *c);
void     chip8_set_pc(chip8_t *c, uint16_t value);

/* index register */
uint16_t chip8_get_I(const chip8_t *c);
void     chip8_set_I(chip8_t *c, uint16_t value);

/* stack */
uint16_t chip8_get_stack(const chip8_t *c, uint8_t index);
void     chip8_set_stack(chip8_t *c, uint8_t index, uint16_t value);

/* stack pointer */
uint8_t  chip8_get_sp(const chip8_t *c);
void     chip8_set_sp(chip8_t *c, uint8_t value);

/* stack pop push */
void chip8_stack_push(chip8_t *c, uint16_t addr);
uint16_t chip8_stack_pop(chip8_t *c);

/* timers */
uint8_t  chip8_get_delay_timer(const chip8_t *c);
void     chip8_set_delay_timer(chip8_t *c, uint8_t value);

uint8_t  chip8_get_sound_timer(const chip8_t *c);
void     chip8_set_sound_timer(chip8_t *c, uint8_t value);

/* V registers */
uint8_t  chip8_get_v(const chip8_t *c, uint8_t index);
void     chip8_set_v(chip8_t *c, uint8_t index, uint8_t value);


const static uint8_t FONTSET[FONTSET_SIZE] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

const static uint8_t KEYMAP[NUM_KEYS] = {
	SDLK_x, // 0
	SDLK_1, // 1
	SDLK_2, // 2
	SDLK_3, // 3
	SDLK_q, // 4
	SDLK_w, // 5
	SDLK_e, // 6
	SDLK_a, // 7
	SDLK_s, // 8
	SDLK_d, // 9
	SDLK_z, // A
	SDLK_c, // B
	SDLK_4, // C
	SDLK_r, // D
	SDLK_f, // E
	SDLK_v  // F
};

uint16_t fetch(const chip8_t *c);

void execute(chip8_t *c, uint16_t instruction);

void loadRom(chip8_t *c, const char *filePath);

#endif
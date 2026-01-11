#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>
#include  "chip8.h"

void opcode_00E0_clear_screen(chip8_t *c);

void opcode_00EE_subroutine(chip8_t *c);

void opcode_1NNN_jump(chip8_t *c, uint16_t nnn);

void opcode_2NNN_subroutine(chip8_t *c, uint16_t nnn);

void opcode_3XNN_skip(chip8_t *c, uint8_t x, uint8_t nn);

void opcode_4XNN_skip(chip8_t *c, uint8_t x, uint8_t nn);

void opcode_5XY0_skip(chip8_t *c, uint8_t x, uint8_t y);

void opcode_9XY0_skip(chip8_t *c, uint8_t x, uint8_t y);

void opcode_6XNN_set_vx(chip8_t *c, uint8_t x, uint8_t nn);

void opcode_7XNN_add_vx(chip8_t *c, uint8_t x, uint8_t nn);

void opcode_8XY0_set(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XY1_or(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XY2_or(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XY3_xor(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XY4_add(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XY5_subtract(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XY7_subtract(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XY6_shift(chip8_t *c, uint8_t x, uint8_t y);

void opcode_8XYE_shift(chip8_t *c, uint8_t x, uint8_t y);

void opcode_ANNN_set_i(chip8_t *c, uint16_t nnn);

void opcode_BNNN_jump_offset(chip8_t *c, uint16_t nnn);

void opcode_CXNN_random(chip8_t *c, uint8_t x, uint8_t nn);

void opcode_DXYN_draw(chip8_t *c, uint8_t x, uint8_t y, uint8_t n);

void opcode_EX9E_key(chip8_t *c, uint8_t x, uint8_t y, uint8_t n);

void opcode_EXA1_key(chip8_t *c, uint8_t x, uint8_t y, uint8_t n);

void opcode_FX07_timer(chip8_t *c, uint8_t x);

void opcode_FX15_timer(chip8_t *c, uint8_t x);

void opcode_FX18_timer(chip8_t *c, uint8_t x);

void opcode_FX1E_I(chip8_t *c, uint8_t x);

void opcode_FX0A_key(chip8_t *c, uint8_t x);

void opcode_FX29_font(chip8_t *c, uint8_t x);

void opcode_FX33_conversion(chip8_t *c, uint8_t x);

void opcode_FX55_memory(chip8_t *c, uint8_t x);

void opcode_FX65_memory(chip8_t *c, uint8_t x);

#endif

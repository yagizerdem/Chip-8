#include  "instruction.h"
#include  "chip8.h"
#include <stdbool.h>

void opcode_00E0_clear_screen(chip8_t *c) {
	for (int i = 0; i < SCHIP_WIDTH; i++) {
		for (int j = 0; j < SCHIP_HEIGHT; j++) {
			chip8_set_pixel(c,i,j,0);
		}
	}
	c->draw_flag = true;
}

void opcode_00EE_subroutine(chip8_t *c) {
	uint16_t item = chip8_stack_pop(c);
	chip8_set_pc(c, item);
}

void opcode_1NNN_jump(chip8_t *c, uint16_t nnn) {
	chip8_set_pc(c, nnn);
}

void opcode_2NNN_subroutine(chip8_t *c, uint16_t nnn)
{
	chip8_stack_push(c, chip8_get_pc(c));
	chip8_set_pc(c, nnn);
}

void opcode_3XNN_skip(chip8_t *c, uint8_t x, uint8_t nn) {
	uint8_t vx = chip8_get_v(c, x);
	if (vx == nn) {
		chip8_set_pc(c, chip8_get_pc(c) + 2);
	}
}

void opcode_4XNN_skip(chip8_t *c, uint8_t x, uint8_t nn) {
	uint8_t vx = chip8_get_v(c, x);
	if (vx != nn) {
		chip8_set_pc(c, chip8_get_pc(c) + 2);
	}
}

void opcode_5XY0_skip(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);
	if (vx == vy) {
		chip8_set_pc(c, chip8_get_pc(c) + 2);
	}
}

void opcode_9XY0_skip(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);
	if (vx != vy) {
		chip8_set_pc(c, chip8_get_pc(c) + 2);
	}
}

void opcode_6XNN_set_vx(chip8_t *c, uint8_t x, uint8_t nn) {
	chip8_set_v(c, x, nn);
}

void opcode_7XNN_add_vx(chip8_t *c, uint8_t x, uint8_t nn) {
	uint8_t value = chip8_get_v(c, x);
	value += nn;
	chip8_set_v(c, x, value);
}

void opcode_8XY0_set(chip8_t *c, uint8_t x, uint8_t y) {
	int vx = chip8_get_v(c, y);
	chip8_set_v(c, x, vx);
}

void opcode_8XY1_or(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);
	chip8_set_v(c, x, vx | vy);
}

void opcode_8XY2_or(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);
	chip8_set_v(c, x, vx & vy);
}

void opcode_8XY3_xor(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);
	chip8_set_v(c ,x, vx ^ vy);
}

void opcode_8XY4_add(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);
	uint16_t sum = vx + vy;
	chip8_set_v(c, 0xF, sum > 255);
	chip8_set_v(c, x, sum & 0xFF);
}

void opcode_8XY5_subtract(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);

	chip8_set_v(c, 0xF, vx >= vy);

	uint16_t sub = vx - vy;
	chip8_set_v(c, x, sub);
}

void opcode_8XY7_subtract(chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t vy = chip8_get_v(c, y);

	chip8_set_v(c, 0xF, vy >= vx);

	uint16_t sub = vy - vx;
	chip8_set_v(c, x, sub);
}

void opcode_8XY6_shift(chip8_t *c, uint8_t x, uint8_t y)
{
	uint8_t vx = chip8_get_v(c, x);
	chip8_set_v(c, 0xF, vx & 0x1);
	chip8_set_v(c, x, vx >> 1);
}

void opcode_8XYE_shift(chip8_t *c, uint8_t x, uint8_t y)
{
	uint8_t vx = chip8_get_v(c, x);
	chip8_set_v(c, 0xF, (vx & 0x80) >> 7);
	chip8_set_v(c, x, vx << 1);
}

void opcode_ANNN_set_i(chip8_t *c, uint16_t nnn) {
	chip8_set_I(c, nnn);
}

void opcode_BNNN_jump_offset(chip8_t *c, uint16_t nnn)
{
	uint8_t v0 = chip8_get_v(c, 0);
	chip8_set_pc(c, nnn + v0);
}

void opcode_CXNN_random(chip8_t *c, uint8_t x, uint8_t nn)
{
	uint8_t r = rand() & 0xFF;   // 8-bit random
	chip8_set_v(c, x, r & nn);
}

void opcode_DXYN_draw(chip8_t *c, uint8_t x, uint8_t y, uint8_t n) {
	c->draw_flag = true;
	uint8_t x_coord = chip8_get_v(c, x);
	uint8_t y_coord = chip8_get_v(c, y);

	chip8_set_v(c, 0xF, 0);
	uint16_t index = chip8_get_I(c);
	for (int j = 0; j < n; j++) {
		uint16_t cur_row_index = index + j; // row consist of 8 pixels
		uint8_t pixel_row = chip8_get_memory(c, cur_row_index) & 0xFF;
		uint8_t screen_y_coord =y_coord + j;
		if (screen_y_coord == SCHIP_HEIGHT) break; // stop if reach bottom of screen
		for (int i = 0; i < 8; i++) {
			uint8_t screen_x_coord =  (x_coord + i) % SCHIP_WIDTH;
			bool current_pixel = (pixel_row >> (7 -i)) &  0x1;
			bool screen_pixel = chip8_get_pixel(c, screen_x_coord, screen_y_coord);

			if (current_pixel && screen_pixel) {
				chip8_set_v(c, 0xF, 1);
				chip8_set_pixel(c, screen_x_coord, screen_y_coord, 0);
			}
			if (current_pixel && !screen_pixel) {
				chip8_set_pixel(c, screen_x_coord, screen_y_coord, 1);
			}
		}
	}
}

void opcode_EX9E_key(chip8_t *c, uint8_t x, uint8_t y, uint8_t n) {
	uint8_t vx = chip8_get_v(c, x);
	if (c->keypad[vx] == 1) {
		chip8_set_pc(c, chip8_get_pc(c) + 2);
	}
}

void opcode_EXA1_key(chip8_t *c, uint8_t x, uint8_t y, uint8_t n) {
	uint8_t vx = chip8_get_v(c, x);
	if (c->keypad[vx] == 0) {
		chip8_set_pc(c, chip8_get_pc(c) + 2);
	}
}

void opcode_FX07_timer(chip8_t *c, uint8_t x) {
	uint8_t delayTimer = chip8_get_delay_timer(c);
	chip8_set_v(c, x, delayTimer);
}

void opcode_FX15_timer(chip8_t *c, uint8_t x) {
	uint8_t vx = chip8_get_v(c, x);
	chip8_set_delay_timer(c, vx);
}

void opcode_FX18_timer(chip8_t *c, uint8_t x) {
	uint8_t vx = chip8_get_v(c, x);
	chip8_set_sound_timer(c, vx);
}

void opcode_FX1E_I(chip8_t *c, uint8_t x) {
	uint16_t I = chip8_get_I(c);
	uint8_t vx = chip8_get_v(c, x);
	chip8_set_I(c, I + vx);
}

void opcode_FX0A_key(chip8_t *c, uint8_t x)
{
	for (int i = 0; i < 16; i++) {
		if (c->keypad[i]) {
			chip8_set_v(c, x, i);
			return;
		}
	}

	chip8_set_pc(c, chip8_get_pc(c) - 2);
}

void opcode_FX29_font(chip8_t *c, uint8_t x) {
	uint8_t vx = chip8_get_v(c, x);
	chip8_set_I(c, FONT_START_ADDR + (vx * 5));
}

void opcode_FX33_conversion(chip8_t *c, uint8_t x) {
	uint8_t vx = chip8_get_v(c, x);
	uint8_t d1 = vx % 10;
	vx -= d1;
	vx /= 10;
	uint8_t d2 = vx % 10;
	vx -= d2;
	vx /= 10;
	uint8_t d3 = vx % 10;

	uint16_t I = chip8_get_I(c);

	chip8_set_memory(c, I, d3);
	chip8_set_memory(c, I + 1, d2);
	chip8_set_memory(c, I + 2, d1);
}

void opcode_FX55_memory(chip8_t *c, uint8_t x) {
	uint16_t I = chip8_get_I(c);

	for (uint8_t i = 0; i <= x; i++) {
		chip8_set_memory(c, I + i, chip8_get_v(c, i));
	}
}

void opcode_FX65_memory(chip8_t *c, uint8_t x) {
	uint16_t I = chip8_get_I(c);

	for (uint8_t i = 0; i <= x; i++) {
		chip8_set_v(c, i, chip8_get_memory(c, I + i));
	}
}

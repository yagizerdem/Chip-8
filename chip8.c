
#include  "chip8.h"

#include <string.h>
#include "instruction.h"
#include <errno.h>

void chip8_init(chip8_t *c) {
	memset(c, 0, sizeof(*c));
	c->programCounter = PROGRAM_START_ADDR;
	c->draw_flag = false;

	// load fonts
	int fontStart = FONT_START_ADDR;
	for (int i = 0; i < FONTSET_SIZE; i++) {
		c->memory[fontStart] = FONTSET[i];
		fontStart+=1;
	}

}

uint8_t  chip8_get_memory(const chip8_t *c, uint16_t addr) {
	uint16_t normalized_addr = addr & 0xFFF;
	return  c->memory[normalized_addr];
}
void  chip8_set_memory(chip8_t *c, uint16_t addr, uint8_t value) {
	uint16_t normalized_addr = addr & 0xFFF;
	c->memory[normalized_addr] = value;
}


uint8_t chip8_get_pixel(const chip8_t *c, uint8_t x, uint8_t y) {
	uint8_t nx = x % SCHIP_WIDTH;
	uint8_t ny = y % SCHIP_HEIGHT;
	return  c->display[ny][nx] & TRUE;
}
void  chip8_set_pixel(chip8_t *c, uint8_t x, uint8_t y, uint8_t value) {
	uint8_t nx = x % SCHIP_WIDTH;
	uint8_t ny = y % SCHIP_HEIGHT;
	c->display[ny][nx] = (value & TRUE);
}

uint16_t chip8_get_pc(const chip8_t *c) {
	return  c->programCounter & 0xFFF;
}
void chip8_set_pc(chip8_t *c, uint16_t value) {
	c->programCounter = value & 0xFFF;
}

uint16_t chip8_get_I(const chip8_t *c) {
	return  c->indexRegister & 0xFFF;
}
void  chip8_set_I(chip8_t *c, uint16_t value) {
	c->indexRegister = value & 0xFFF;
}

uint8_t chip8_get_sp(const chip8_t *c) {
	return c->stackPointer & 0xF;
}

void chip8_set_sp(chip8_t *c, uint8_t value) {
	c->stackPointer = (value & 0xF);
}

void chip8_stack_push(chip8_t *c, uint16_t addr) {
	if (c->stackPointer < STACK_SIZE)
		c->stack[c->stackPointer++] = addr;
}

uint16_t chip8_stack_pop(chip8_t *c) {
	if (c->stackPointer == 0)
		return 0;
	return c->stack[--c->stackPointer];
}

uint8_t  chip8_get_delay_timer(const chip8_t *c) {
	return c->delayTimer;
}
void     chip8_set_delay_timer(chip8_t *c, uint8_t value) {
	c->delayTimer = value;
}

uint8_t  chip8_get_sound_timer(const chip8_t *c) {
	return c->soundTimer;
}
void     chip8_set_sound_timer(chip8_t *c, uint8_t value) {
	c->soundTimer = value;
}

uint8_t chip8_get_v(const chip8_t *c, uint8_t index) {
	index = index & 0xF;
	return c->vRegister[index];
}

void chip8_set_v(chip8_t *c, uint8_t index, uint8_t value) {
	index = index & 0xF;
	c->vRegister[index] = value;
}


uint16_t fetch(const chip8_t *c) {
	uint16_t highByte = (chip8_get_memory(c, c->programCounter) << 8);
	uint16_t lowByte = chip8_get_memory(c, c->programCounter + 1);
	uint16_t instruction = highByte | lowByte;
	chip8_set_pc(c, c->programCounter + 2);
	return  instruction;
}


// decode and execute coupled in single function
void execute(chip8_t *c, uint16_t instruction) {
	uint8_t X = (instruction & 0x0F00) >> 8;
	uint8_t Y = (instruction & 0x00F0) >> 4;
	uint8_t N = instruction & 0x000F;
	uint16_t NN = instruction & 0x00FF;
	uint16_t NNN = instruction & 0x0FFF;
	switch ((instruction & 0xF000) >> 12) {
		case 0x0:
			 switch (instruction & 0x00FF) {
				case 0x00E0:
					opcode_00E0_clear_screen(c);
					break;
				case 0x00EE:
					opcode_00EE_subroutine(c);
					break;
			}
			break;
		case 0x1:
			opcode_1NNN_jump(c, NNN);
			break;
		case 0x2:
			opcode_2NNN_subroutine(c, NNN);
			break;
		case 0x3:
			opcode_3XNN_skip(c, X, NN);
			break;
		case 0x4:
			opcode_4XNN_skip(c,X,NN);
			break;
		case 0x5:
			opcode_5XY0_skip(c, X, Y);
			break;
		case 0x6:
			opcode_6XNN_set_vx(c, X, NN);
			break;
		case 0x7:
			opcode_7XNN_add_vx(c, X, NN);
			break;
		case 0x8:
			switch(instruction & 0x000F) {
				case 0x0000:
					opcode_8XY0_set(c,X,Y);
					break;
				case 0x0001:
					opcode_8XY1_or(c,X,Y);
					break;
				case 0x0002:
					opcode_8XY2_or(c,X,Y);
					break;
				case 0x0003:
					opcode_8XY3_xor(c,X,Y);
					break;
				case 0x0004:
					opcode_8XY4_add(c,X,Y);
					break;
				case 0x0005:
					opcode_8XY5_subtract(c,X,Y);
					break;
				case 0x0006:
					opcode_8XY6_shift(c,X,Y);
					break;
				case 0x0007:
					opcode_8XY7_subtract(c,X,Y);
					break;
				case 0x000E:
					opcode_8XYE_shift(c,X,Y);
					break;
			}
			break;
		case 0x9:
			opcode_9XY0_skip(c, X, Y);
			break;
		case 0xA:
			opcode_ANNN_set_i(c, NNN);
			break;
		case 0xB:
			opcode_BNNN_jump_offset(c, NNN);
			break;
		case 0xC:
			opcode_CXNN_random(c, X, NN);
			break;
		case 0xD:
			opcode_DXYN_draw(c,X, Y, N);
			break;
		case 0xE:
			switch(instruction & 0x00FF) {
				case 0x009E:
					opcode_EX9E_key(c,X, Y,NN);
					break;

			case 0x00A1:
					opcode_EXA1_key(c,X, Y,NN);
					break;
			}

		case 0xF:
			switch (instruction & 0x00FF) {
			case 0x0007:
					opcode_FX07_timer(c, X);
					break;
			case 0x000A:
					opcode_FX0A_key(c, X);
					break;
			case 0x0015:
					opcode_FX15_timer(c, X);
					break;
			case 0x0018:
					opcode_FX18_timer(c, X);
					break;
			case 0x001E:
					opcode_FX1E_I(c, X);
					break;
			case 0x0029:
					opcode_FX29_font(c, X);
					break;
			case 0x0033:
					opcode_FX33_conversion(c, X);
					break;
			case 0x0055:
					opcode_FX55_memory(c, X);
					break;
			case 0x0065:
					opcode_FX65_memory(c, X);
					break;
			}

			break;
	}

}

void loadRom(chip8_t *c, const char *filePath) {
	FILE *fptr = fopen(filePath, "rb");
	if (!fptr) {
		fprintf(stderr,
			"CHIP-8 ROM load failed\n"
			"  Path   : %s\n"
			"  Reason : %s\n",
			filePath,
			strerror(errno));
		exit(EXIT_FAILURE);
	}

	fseek(fptr, 0, SEEK_END);
	long rom_length = ftell(fptr);
	if (rom_length < 0) {
		perror("ftell failed");
		exit(EXIT_FAILURE);
	}
	rewind(fptr);

	if (rom_length > (PROGRAM_END_ADDR - PROGRAM_START_ADDR)) {
		fprintf(stderr,
			"CHIP-8 ROM too large\n"
			"  Size        : %ld bytes\n"
			"  Max allowed : %d bytes\n",
			rom_length,
			PROGRAM_END_ADDR - PROGRAM_START_ADDR);
		exit(EXIT_FAILURE);
	}

	uint8_t *rom_buffer = malloc(rom_length);
	if (!rom_buffer) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	fread(rom_buffer, 1, rom_length, fptr);

	for (int i = 0; i < rom_length; i++) {
		chip8_set_memory(c, PROGRAM_START_ADDR + i, rom_buffer[i]);
	}

	free(rom_buffer);
	fclose(fptr);
}
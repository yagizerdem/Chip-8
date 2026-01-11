
# CHIP-8 Emulator (Unix)

A minimal **CHIP-8 Emulator** written for Unix based systems. This project follows the classic CHIP-8 specification.

> Technically, this is an interpreter rather than a hardware emulator, since CHIP-8 is a virtual instruction set.

---

## Features

- Complete **CHIP-8 instruction set**
- 4 KB memory model (programs loaded at address `0x200`)
- Built-in hexadecimal **font sprites** (4×5)
- 64×32 monochrome display
- Stack-based subroutine handling
- Delay and sound timers running at 60 Hz
- Hex keypad input mapping
- Fetch / Decode / Execute execution loop
- Designed and tested on **Unix (Linux)** systems

---

## Usage

The emulator is executed from the shell and takes **two parameters**:

```bash
chip8 <programPath>

#Exapmle (adjust program path and call this from your unix shell)
Chip_8 ./roms/PONG.ch8
```

## Author
Yağız Erdem <br/>
yagizerdem819@gmail.com

## License
MIT License
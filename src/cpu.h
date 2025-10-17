#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define D_WIDTH 64
#define D_HEIGHT 32

typedef struct
{
    uint8_t memory[4096];
    uint8_t V[16];
    uint16_t I;         // 16-bit index register
    uint16_t pc;        // program counter
    uint16_t stack[16]; // stack
    uint8_t sp;         // stack pointer
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];                   // input keys
    uint32_t display[D_HEIGHT * D_WIDTH]; // pixel buffer
    uint8_t draw_flag;                    // redraw flag
} Chip8;

extern uint8_t sprits[80];

Chip8 *chip_init();
void load_rom(Chip8 *arch, char *path);
void decode_exec(Chip8 *chip, uint16_t opcode);

#endif
#ifndef INPUT_H
#define INPUT_H

#include "cpu.h"
#include "display.h"

uint8_t wait_input();
void handle_input(Chip8 *chip);

#endif
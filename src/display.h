#ifndef DISPLAY_H
#define DISPLAY_H
#include "cpu.h"
#include "input.h"

#include <SDL2/SDL.h>

int init_window();
void render_display(Chip8 *chip);
void cleanup_display();

#endif
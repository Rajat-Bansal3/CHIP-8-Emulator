#include "cpu.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <rom file>\n", argv[0]);
        exit(1);
    }
    Chip8 *arch = chip_init();
    load_rom(arch, argv[1]);
    return 0;
}
#include "display.h"

int main(int argc, char *argv[])
{
    init_random();
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <rom file>\n", argv[0]);
        exit(1);
    }
    Chip8 *chip = chip_init();
    load_rom(chip, argv[1]);
    if (!init_window())
    {
        fprintf(stderr, "Failed to initialize window\n");
        exit(1);
    }
    int running = 1;
    while (running)
    {
        handle_input(chip);
        for (int i = 0; i < 10; i++)
        {
            uint16_t opcode = (chip->memory[chip->pc] << 8) | chip->memory[chip->pc + 1];
            chip->pc += 2;
            decode_exec(chip, opcode);
        }

        if (chip->delay_timer > 0)
            chip->delay_timer--;
        if (chip->sound_timer > 0)
            chip->sound_timer--;

        if (chip->draw_flag)
        {
            render_display(chip);
            chip->draw_flag = 0;
        }

        SDL_Delay(16);
    }

    cleanup_display();
    return 0;
}
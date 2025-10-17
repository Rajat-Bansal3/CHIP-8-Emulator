#include "cpu.h"

void init_random()
{
    srand(time(NULL));
}

uint8_t random_byte()
{
    return rand() & 0xFF;
}
uint8_t sprits[80] = {
    0xF0,
    0x90,
    0x90,
    0x90,
    0xF0, // 0
    0x20,
    0x60,
    0x20,
    0x20,
    0x70, // 1
    0xF0,
    0x10,
    0xF0,
    0x80,
    0xF0, // 2
    0xF0,
    0x10,
    0xF0,
    0x10,
    0xF0, // 3
    0x90,
    0x90,
    0xF0,
    0x10,
    0x10, // 4
    0xF0,
    0x80,
    0xF0,
    0x10,
    0xF0, // 5
    0xF0,
    0x80,
    0xF0,
    0x90,
    0xF0, // 6
    0xF0,
    0x10,
    0x20,
    0x40,
    0x40, // 7
    0xF0,
    0x90,
    0xF0,
    0x90,
    0xF0, // 8
    0xF0,
    0x90,
    0xF0,
    0x10,
    0xF0, // 9
    0xF0,
    0x90,
    0xF0,
    0x90,
    0x90, // A
    0xE0,
    0x90,
    0xE0,
    0x90,
    0xE0, // B
    0xF0,
    0x80,
    0x80,
    0x80,
    0xF0, // C
    0xE0,
    0x90,
    0x90,
    0x90,
    0xE0, // D
    0xF0,
    0x80,
    0xF0,
    0x80,
    0xF0, // E
    0xF0,
    0x80,
    0xF0,
    0x80,
    0x80, // F
};
Chip8 *chip_init()
{

    Chip8 *arch = malloc(sizeof(Chip8));
    if (!arch)
    {
        perror("error allocating memory for arch");
        exit(1);
    };
    arch->pc = 0x200;
    arch->I = 0;
    arch->sp = 0;
    arch->delay_timer = 0;
    arch->sound_timer = 0;
    arch->draw_flag = 0;
    memset(arch->memory, 0, sizeof(arch->memory));
    memset(arch->V, 0, sizeof(arch->V));
    memset(arch->stack, 0, sizeof(arch->stack));
    memset(arch->keypad, 0, sizeof(arch->keypad));
    memset(arch->display, 0, sizeof(arch->display));
    memcpy(&arch->memory[0x50], sprits, sizeof(sprits));
    return arch;
}
void load_rom(Chip8 *arch, char *path)
{
    FILE *f;
    f = fopen(path, "rb");
    if (!f)
    {
        perror("error opening file");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    size_t rom_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (rom_size >= 4096 - 0x200)
    {
        perror("rom too large");
        exit(1);
    }
    size_t size = fread(&arch->memory[0x200], 1, rom_size, f);
    if (size != rom_size)
    {
        perror("error reading file");
        exit(1);
    }
    fclose(f);
    return;
}
void decode_exec(Chip8 *chip, uint16_t opcode)
{
    switch (opcode & 0xF000)
    {

    case 0x0000:
        switch (opcode & 0x00FF)
        {
        case 0x00E0:
            memset(chip->display, 0, sizeof(chip->display));
            chip->draw_flag = 1;
            break;
        case 0x00EE:
            chip->pc = chip->stack[--chip->sp];
            break;
        default:
            fprintf(stderr, "Unknown 0x0000 opcode: 0x%04X\n", opcode);
            exit(1);
        }
        break;
    case 0x1000:
        chip->pc = opcode & 0x0FFF;
        break;
    case 0x2000:
        chip->stack[chip->sp++] = chip->pc;
        chip->pc = opcode & 0x0FFF;
        break;
    case 0xA000:
        chip->I = opcode & 0x0FFF;
        break;
    case 0xB000:
        chip->pc = chip->V[0] + (opcode & 0x0FFF);
        break;
    case 0XC000:
        chip->V[(opcode & 0x0F00) >> 8] = random_byte() & (opcode & 0x00FF);
        break;
    case 0x3000:
        if (chip->V[(opcode & 0x0F00) >> 8] == opcode & 0x00FF)
        {
            chip->pc += 2;
        }
        break;
    case 0x4000:
        if (chip->V[(opcode & 0x0F00) >> 8] != opcode & 0x00FF)
        {
            chip->pc += 2;
        }
        break;
    case 0x5000:
        if (chip->V[(opcode & 0x0F00) >> 8] == chip->V[(opcode & 0x00F0) >> 4])
        {
            chip->pc += 2;
        }
        break;
    case 0x6000:
        chip->V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
        break;
    case 0x7000:
        chip->V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
        break;
    case 0x8000:
        switch (opcode & 0x000F)
        {
        case 0x0000:
            chip->V[(opcode & 0x0F00) >> 8] = chip->V[(opcode & 0x00F0) >> 4];
            break;
        case 0x0001:
            chip->V[(opcode & 0x0F00) >> 8] |= chip->V[(opcode & 0x00F0) >> 4];
            break;
        case 0x0002:
            chip->V[(opcode & 0x0F00) >> 8] &= chip->V[(opcode & 0x00F0) >> 4];
            break;
        case 0x0003:
            chip->V[(opcode & 0x0F00) >> 8] ^= chip->V[(opcode & 0x00F0) >> 4];
            break;
        case 0x0004:
            if (chip->V[(opcode & 0x0F00) >> 8] + chip->V[(opcode & 0x00F0) >> 4] > 0xFF)
            {
                chip->V[0xF] = 1;
            }
            else
            {
                chip->V[0xF] = 0;
            }
            chip->V[(opcode & 0x0F00) >> 8] += chip->V[(opcode & 0x00F0) >> 4];
            break;
        case 0x0005:
            if (chip->V[(opcode & 0x0F00) >> 8] > chip->V[(opcode & 0x00F0) >> 4])
            {
                chip->V[0xF] = 1;
            }
            else
            {
                chip->V[0xF] = 0;
            }
            chip->V[(opcode & 0x0F00) >> 8] -= chip->V[(opcode & 0x00F0) >> 4];
            break;
        case 0x0006:
            chip->V[0xF] = chip->V[(opcode & 0x0F00) >> 8] & 0x01;
            chip->V[(opcode & 0x0F00) >> 8] /= 2;
            break;
        case 0x0007:
            if (chip->V[(opcode & 0x00F0) >> 4] > chip->V[(opcode & 0x0F00) >> 8])
            {
                chip->V[0xF] = 1;
            }
            else
            {
                chip->V[0xF] = 0;
            }
            chip->V[(opcode & 0x0F00) >> 8] = chip->V[(opcode & 0x00F0) >> 4] - chip->V[(opcode & 0x0F00) >> 8];
            break;
        case 0x000E:
            chip->V[0xF] = chip->V[(opcode & 0x0F00) >> 8] & 0x80;
            chip->V[(opcode & 0x0F00) >> 8] *= 2;
            break;

        default:
            fprintf(stderr, "Unknown opcode: 0x%04X\n", opcode);
            exit(1);
        }
        break;
    case 0x9000:
        if (chip->V[(opcode & 0x0F00) >> 8] != chip->V[(opcode & 0x00F0) >> 4])
        {
            chip->pc += 2;
        }
        break;
    case 0xD000:
    {
        uint8_t x = chip->V[(opcode & 0x0F00) >> 8] % D_WIDTH;
        uint8_t y = chip->V[(opcode & 0x00F0) >> 4] % D_HEIGHT;
        uint8_t height = opcode & 0x000F;

        chip->V[0xF] = 0;

        for (int row = 0; row < height; row++)
        {
            uint8_t sprite_byte = chip->memory[chip->I + row];
            uint8_t current_y = (y + row) % D_HEIGHT;

            for (int col = 0; col < 8; col++)
            {
                uint8_t current_x = (x + col) % D_WIDTH;
                uint8_t sprite_pixel = (sprite_byte >> (7 - col)) & 0x1;
                uint32_t display_index = current_y * D_WIDTH + current_x;

                if (sprite_pixel == 1)
                {
                    if (chip->display[display_index] == 1)
                    {
                        chip->V[0xF] = 1;
                    }
                    chip->display[display_index] ^= 1;
                }
            }
        }
        chip->draw_flag = 1;
        break;
    }
    case 0xE000:
        switch (opcode & 0x00FF)
        {
        case 0x009E:
            if (chip->keypad[chip->V[(opcode & 0x0F00) >> 8]] == 1)
            {
                chip->pc += 2;
            }
            break;
        case 0x00A1:
            if (chip->keypad[chip->V[(opcode & 0x0F00) >> 8]] == 0)
            {
                chip->pc += 2;
            }
            break;

        default:
            fprintf(stderr, "Unknown opcode: 0x%04X\n", opcode);
            exit(1);
        }
        break;
    case 0xF000:
        switch (opcode & 0x00FF)
        {
        case 0x0007:
            chip->V[(opcode & 0x0F00) >> 8] = chip->delay_timer;
            break;
        case 0x000A:
            chip->V[(opcode & 0x0F00) >> 8] = wait_input();
            break;
        case 0x0015:
            chip->delay_timer = chip->V[(opcode & 0x0F00) >> 8];
            break;
        case 0x0018:
            chip->sound_timer = chip->V[(opcode & 0x0F00) >> 8];
            break;
        case 0x001E:
            chip->I += chip->V[(opcode & 0x0F00) >> 8];
            break;
        case 0x0029:
            chip->I = chip->V[(opcode & 0x0F00) >> 8] * 0x05;
            break;
        case 0x0033:
            uint8_t value = chip->V[(opcode & 0x0F00) >> 8];
            chip->memory[chip->I] = value / 100;
            chip->memory[chip->I + 1] = (value / 10) % 10;
            chip->memory[chip->I + 2] = value % 10;
            break;
        case 0x0055:
            for (int i = 0; i <= 0xF; i++)
            {
                chip->memory[chip->I + i] = chip->V[i];
            }
            break;
        case 0x0065:
            for (int i = 0; i <= 0xF; i++)
            {
                chip->V[i] = chip->memory[chip->I + i];
            }
            break;

        default:
            break;
        }
        break;

    default:
        fprintf(stderr, "Unknown opcode: 0x%04X\n", opcode);
        exit(1);
    }
}
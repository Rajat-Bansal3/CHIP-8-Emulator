#include "input.h"

void handle_input(Chip8 *chip)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            uint8_t value = (event.type == SDL_KEYDOWN) ? 1 : 0;
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                chip->keypad[0x1] = value;
                break;
            case SDLK_2:
                chip->keypad[0x2] = value;
                break;
            case SDLK_3:
                chip->keypad[0x3] = value;
                break;
            case SDLK_4:
                chip->keypad[0xC] = value;
                break;

            case SDLK_q:
                chip->keypad[0x4] = value;
                break;
            case SDLK_w:
                chip->keypad[0x5] = value;
                break;
            case SDLK_e:
                chip->keypad[0x6] = value;
                break;
            case SDLK_r:
                chip->keypad[0xD] = value;
                break;

            case SDLK_a:
                chip->keypad[0x7] = value;
                break;
            case SDLK_s:
                chip->keypad[0x8] = value;
                break;
            case SDLK_d:
                chip->keypad[0x9] = value;
                break;
            case SDLK_f:
                chip->keypad[0xE] = value;
                break;

            case SDLK_z:
                chip->keypad[0xA] = value;
                break;
            case SDLK_x:
                chip->keypad[0x0] = value;
                break;
            case SDLK_c:
                chip->keypad[0xB] = value;
                break;
            case SDLK_v:
                chip->keypad[0xF] = value;
                break;
            }
            break;
        }
        }
    }
}
uint8_t wait_input()
{
    SDL_Event event;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit(0);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_1:
                    return 0x1;
                case SDLK_2:
                    return 0x2;
                case SDLK_3:
                    return 0x3;
                case SDLK_4:
                    return 0xC;

                case SDLK_q:
                    return 0x4;
                case SDLK_w:
                    return 0x5;
                case SDLK_e:
                    return 0x6;
                case SDLK_r:
                    return 0xD;

                case SDLK_a:
                    return 0x7;
                case SDLK_s:
                    return 0x8;
                case SDLK_d:
                    return 0x9;
                case SDLK_f:
                    return 0xE;

                case SDLK_z:
                    return 0xA;
                case SDLK_x:
                    return 0x0;
                case SDLK_c:
                    return 0xB;
                case SDLK_v:
                    return 0xF;
                }
            }
        }
        SDL_Delay(10);
    }
}
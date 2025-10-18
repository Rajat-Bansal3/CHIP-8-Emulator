#include "display.h"
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

int init_window()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
    {
        fprintf(stderr, "SDL Init Error: %s\n", SDL_GetError());
        return 0;
    }
    int scale = 10;
    window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        D_WIDTH * scale,
        D_HEIGHT * scale,
        SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "SDL Window Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "SDL Renderer Error: %s\n", SDL_GetError());
        return 0;
    }
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        D_WIDTH,
        D_HEIGHT);
    if (!texture)
    {
        fprintf(stderr, "SDL Texture Error: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}
void render_display(Chip8 *chip)
{
    uint32_t pixels[D_WIDTH * D_HEIGHT];

    for (int i = 0; i < D_WIDTH * D_HEIGHT; i++)
    {
        pixels[i] = chip->display[i] ? 0xFFFFFFFF : 0x000000FF;
    }

    SDL_UpdateTexture(texture, NULL, pixels, D_WIDTH * sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
void cleanup_display()
{
    if (texture)
        SDL_DestroyTexture(texture);
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
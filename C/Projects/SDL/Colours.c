#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

int randCol()
{
    return rand() % 255 + 0;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Press Q to Exit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);

    bool running = true;
    Uint32 old_time = 0, change_color_time = 1000, new_time;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                if (strcmp(key, "Q") == 0 || strcmp(key, "Escape") == 0)
                {
                    running = false;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        new_time = SDL_GetTicks();
        if (new_time - old_time > change_color_time)
        {
            SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);
            old_time = new_time;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
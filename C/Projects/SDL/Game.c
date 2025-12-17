#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 480
#define GRAVITY 980 // An attempt to add gravity to the code

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("Error Initialisation SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Akshit ka Lauda", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window)
    {
        printf("error creating window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, render_flags);
    if (!render)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = IMG_Load("D:/JustFun/IMG_20241123_164303.jpg");
    if (!surface)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("error creating texture\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    float scale_factor = (float)WINDOW_WIDTH / (float)dest.w;
    if (scale_factor < 1.0f)
    {
        dest.w = WINDOW_WIDTH;
        dest.h = (int)(dest.h * scale_factor);
    }

    SDL_RenderClear(render);
    SDL_RenderCopy(render, tex, NULL, &dest);
    SDL_RenderPresent(render);
    SDL_Delay(1000 / 60);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

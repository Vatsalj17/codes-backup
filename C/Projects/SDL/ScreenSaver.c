#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 480
#define SCROLL_SPEED 300
#define SPEED 100

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s D:/JustFun/Anuv Jain - BAARISHEIN (ACOUSTIC).mp3\n", argv[0]);
        return -1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
    {
        printf("Error Initialisation SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS(argv[1]);
    if (!music)
    {
        printf("Error loading audio: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    if (Mix_PlayMusic(music, 1) == -1)
    {
        printf("Error playing audio: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
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

    dest.w /= 4;
    dest.h /= 4;
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
    float x_vel = SPEED;
    float y_vel = SPEED;

    bool run = true;

    while (run)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                run = false;
        }
        if (x_pos <= 0)
        {
            x_pos = 0;
            x_vel = -x_vel;
        }
        if (y_pos <= 0)
        {
            y_pos = 0;
            y_vel = -y_vel;
        }
        if (x_pos >= WINDOW_WIDTH - dest.w)
        {
            x_pos = WINDOW_WIDTH - dest.w;
            x_vel = -x_vel;
        }
        if (y_pos >= WINDOW_HEIGHT - dest.h)
        {
            y_pos = WINDOW_HEIGHT - dest.h;
            y_vel = -y_vel;
        }

        x_pos += x_vel / 60;
        y_pos += y_vel / 60;
        dest.y = (int)y_pos;
        dest.x = (int)x_pos;

        SDL_RenderClear(render);
        SDL_RenderCopy(render, tex, NULL, &dest);
        SDL_RenderPresent(render);
        SDL_Delay(1000 / 60);
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

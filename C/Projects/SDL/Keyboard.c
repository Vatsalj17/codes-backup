#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 480
#define SPEED 300

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

    SDL_Surface *surface2 = IMG_Load("D:/JustFun/IMG-20241129-WA0009.jpg");
    if (!surface2)
    {
        printf("error creating surface2\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(render, surface2);
    SDL_FreeSurface(surface2);
    if (!tex || !tex2)
    {
        printf("error creating texture\n");
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    SDL_Rect bg;
    SDL_QueryTexture(tex2, NULL, NULL, &bg.w, &bg.h);

    float scale_factor = (float)WINDOW_WIDTH / (float)dest.w;
    if (scale_factor < 1.0f)
    {
        dest.w = WINDOW_WIDTH;
        dest.h = (int)(dest.h * scale_factor);
    }

    float scale_factor2 = (float)WINDOW_WIDTH / (float)bg.w;
    if (scale_factor2 < 1.0f)
    {
        bg.w = WINDOW_WIDTH;
        bg.h = (int)(bg.h * scale_factor2);
    }

    dest.w /= 8;
    dest.h /= 8;
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
    float x_vel = 0;
    float y_vel = 0;

    int up = 0;
    int down = 0;
    int right = 0;
    int left = 0;

    bool run = true;

    while (run)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }

        x_vel = y_vel = 0;
        if (up && !down)
            y_vel = -SPEED;
        if (down && !up)
            y_vel = SPEED;
        if (left && !right)
            x_vel = -SPEED;
        if (right && !left)
            x_vel = SPEED;

        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        if (x_pos <= 0)
            x_pos = 0;
        if (y_pos <= 0)
            y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w)
            x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h)
            y_pos = WINDOW_HEIGHT - dest.h;

        dest.y = (int)y_pos;
        dest.x = (int)x_pos;

        SDL_RenderClear(render);
        SDL_RenderCopy(render, tex2, NULL, NULL);
        SDL_RenderCopy(render, tex, NULL, &dest);
        SDL_RenderPresent(render);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(tex2);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

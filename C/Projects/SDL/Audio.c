#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char *argv[])
{
    // Check if an audio file argument is provided
    if (argc < 2)
    {
        printf("Usage: %s \n", argv[0]);
        return -1;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    // Load the audio file
    Mix_Music *music = Mix_LoadMUS(argv[1]);
    if (!music)
    {
        printf("Error loading audio: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Play the audio (the '1' means play it once, -1 for infinite looping)
    if (Mix_PlayMusic(music, 1) == -1)
    {
        printf("Error playing audio: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Create an SDL window (optional, just for demonstration)
    SDL_Window *window = SDL_CreateWindow("Gaane Suno", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Event loop to keep the program running until the user closes the window
    SDL_Event e;
    int quit = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        SDL_Delay(100); // Delay to avoid 100% CPU usage
    }

    // Cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

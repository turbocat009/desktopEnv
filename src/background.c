// Background.c
//--------------------------
// This script creates the desktop background, and all related.
//-------------------------


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "renderText.c"
#include "readConfig.c"
#include "../include/data.h"

int main(int argc, char *argv[]) {
    //Init
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }

    if (TTF_Init() == -1) {
        printf("SDL_TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
    {
        printf("SDL_GetCurrentDisplayMode Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("background",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          displayMode.w, displayMode.h, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    const char *imagePath = loadGameConf();
    printf("%s", imagePath);
    SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, imagePath);
    if (!backgroundTexture)
    {
        printf("Unable to load background image! IMG_Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }


    TTF_Font *font = TTF_OpenFont("OpenSans.ttf", 24);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }

    //Main loop
    SDL_Event e;
    int quit = 0;
    int rendered = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
    
        if (!rendered) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

            char String[256];
            snprintf(String, sizeof(String), "Running at %dx%d", displayMode.w, displayMode.h);
            WriteToScreen(renderer, font, String, (displayMode.w - 260), (displayMode.h - 100));

            char Version[256];
            snprintf(Version, sizeof(Version), "%s %s (Build num. %d)", STATE, VER, BUILD_NUM);
            WriteToScreen(renderer, font, Version, (displayMode.w - 310), (displayMode.h - 150));
            WriteToScreen(renderer, font, YEAR, (displayMode.w - 100), (displayMode.h - 50));
            SDL_RenderPresent(renderer);

            rendered += 1;
        }
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    free((void*)imagePath);
    
    return 0;

}

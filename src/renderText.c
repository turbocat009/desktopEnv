#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>


void WriteToScreen(SDL_Renderer *renderer, TTF_Font *font, const char *Text, int x, int y) {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, Text, textColor);
    if (!textSurface) {
        printf("Unable to create text surface! TTF_Error: %s\n", TTF_GetError());
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

    SDL_RenderPresent(renderer);
}
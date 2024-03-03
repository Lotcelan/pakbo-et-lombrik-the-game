#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>

typedef struct {
    char* name;
    char* path;
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
} Texture;


/*
SDL_Surface* surface = IMG_Load("path_to_image.png");
if (!surface) {
    // handle error
}

SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
if (!texture) {
    // handle error
}

SDL_FreeSurface(surface); // we can free the surface after the texture is created

SDL_Rect srcRect = {0, 0, width_of_texture, height_of_texture};
SDL_Rect dstRect = {x_position_on_screen, y_position_on_screen, width_on_screen, height_on_screen};

SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);

// when done with the texture
SDL_DestroyTexture(texture);
*/
#endif
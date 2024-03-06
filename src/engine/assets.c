#include "include/assets.h"

SDL_Texture* loadTextureFromMemory(GameData* game, char* resource) {
    // Load texture from memory
    displayHashTableResource(game->resources);
    MemTexture* resource_texture = (MemTexture*)get(game->resources, resource, strcmp);
    if (resource_texture == NULL) {
        printf("Resource not found: %s\n", resource);
        return NULL;
    }
    SDL_RWops* rw = SDL_RWFromMem(resource_texture->data, resource_texture->size);
    SDL_Surface* surface = IMG_Load_RW(rw, 1);
    if (!surface) {
        printf("Unable to create surface from memory: %s\n", IMG_GetError());
        return NULL;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Unable to create texture from surface: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}
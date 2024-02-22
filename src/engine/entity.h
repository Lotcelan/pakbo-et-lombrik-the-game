#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// Exemple
 typedef enum Stats {
    HP,
    MaxHP,
    Armor,
    Attack,
    STATS_AMOUNT
 } Stats;


// On pourra en rajouter
typedef struct Entity {
    SDL_Texture* textures[4];
    Mix_Chunk* sounds[4];
    TTF_Font* font;
    SDL_Rect position;
    int stats[STATS_AMOUNT];
} Entity;

bool init_entity(Entity* e, const char* texture, const char* sound);
void free_entity(Entity* e);

#endif
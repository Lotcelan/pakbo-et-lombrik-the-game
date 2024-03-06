#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "scenes.h"
#include <stdbool.h>
#include "hashtable.h"

typedef struct Scene Scene;

typedef enum GameStatus {
    RUNNING,
    LOADING,
    PAUSED,
} GameStatus;

typedef struct GameData {
    GameStatus state;
    Scene* current_scene;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    HashTable* resources;
} GameData;

GameData* init_game(int width, int height, const char* title);
void free_game(GameData* game);

#endif
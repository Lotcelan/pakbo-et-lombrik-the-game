#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "scenes.h"
#include <stdbool.h>
#include "hashtable.h"
#include "framerate.h"

typedef struct Scene Scene;

typedef enum GameStatus {
    RUNNING,
    LOADING,
    PAUSED,
    CLOSING,
} GameStatus;

typedef struct GameData {
    GameStatus state;
    Scene* current_scene;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    HashTable* resources;

    FrameRateManager* frm;
} GameData;

GameData* init_game(int width, int height, const char* title, int capped_fps);
void event_handler(GameData* game);
void free_game(GameData* game);

#endif
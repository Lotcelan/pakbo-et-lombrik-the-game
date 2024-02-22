#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "scenes.h"

typedef enum GameStatus {
    RUNNING,
    PAUSED,
} GameStatus;

typedef struct  {
    GameStatus state;
    Scene current_scene;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

} GameData;

bool init_game(GameData* gameData);
void free_game(GameData* game);

#endif
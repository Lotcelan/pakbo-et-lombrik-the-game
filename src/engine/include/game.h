#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include <SDL2/SDL.h>
#include "scenes.h"
#include <stdbool.h>
#include "hashtable.h"
#include "framerate.h"

#define CELL_WIDTH 16
#define CELL_HEIGHT 16

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
    int width_amount;
    int height_amount;
    SDL_Renderer* renderer;
    SDL_Event event;

    HashTable* resources;
    HashTable* fonts;
    HashTable* scenes;

    FrameRateManager* frm;
} GameData;

GameData* init_game(int width_amount, int height_amount, int final_width, int final_height, const char* title, int capped_fps);
void event_handler(GameData* game);
void free_game(GameData* game);
void set_dir();


#endif
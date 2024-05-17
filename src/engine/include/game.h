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
#include "entity.h"
#include "modifiers.h"


#include <math.h>

#define CELL_WIDTH 16
#define CELL_HEIGHT 16

typedef struct Scene Scene;
typedef struct Dialog Dialog;

typedef enum GameStatus {
    RUNNING,
    CHANGING,
    PAUSED,
    CLOSING,
} GameStatus;


typedef struct GameData {
    GameStatus state;
    Scene* current_scene;
    Dialog* current_dialog;

    SDL_Window* window;
    int width_amount;
    int height_amount;
    SDL_Renderer* renderer;
    SDL_Event event;
    const Uint8* keyboardState;


    HashTable* resources;
    HashTable* fonts;
    HashTable* scenes;
    HashTable* entities; // FONCTIONS d'initialisation
    HashTable* weapons; // FONCTIONS d'initialisation

    Entity* player; // on sépare le joueur du reste des entités

    FrameRateManager* frm;
    float deltaT; // ajouté très tard dans la structure, donc bcp de fonctions le prenne encore en paramètre
} GameData;

GameData* init_game(int width_amount, int height_amount, int final_width, int final_height, const char* title, int capped_fps);
void event_handler(GameData* game);
void free_game(GameData* game);
void set_dir(void);


#endif

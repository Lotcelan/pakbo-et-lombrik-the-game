#ifndef SCENES_H
#define SCENES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <jansson.h>
#include "assets.h"
#include "entity.h"
#include "linked_list.h"
#include "hashtable.h"
#include "assets.h"


typedef struct ScreenShake {
    int duration;
    int intensity;
    int time;
} ScreenShake;

typedef struct GameData GameData;
typedef struct Structure Structure;

typedef struct Scene {
    char title[200];
    List* render_stack;
    List* structures;
    List* entities;
    char background[200];
    void (*update)(GameData* game);
    void (*populate)(GameData* game);
    void (*event_handler)(GameData* game);
    ScreenShake* screen_shake;

    HashTable* objects;

} Scene;

Scene* init_scene(GameData* game, char* title); // Title = nom de la scène = nom du dossier dans scenes/
void render_scene(GameData* game);
void free_scene(Scene* scene);
void change_scene(GameData* game, char* next);
SDL_Texture* load_texture(SDL_Renderer* renderer, char* path);

void free_structure(Structure* s);
void init_scene_with_json(GameData* game, json_t *root, Scene* scene);

void render_screen_shake(GameData* game);
ScreenShake* init_screen_shake(int duration, int intensity);
void destroy_screen_shake(GameData* game);

#endif
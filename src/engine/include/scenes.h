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
#include "dialogs.h"


typedef struct ScreenShake {
    int duration;
    int intensity;
    int time;
} ScreenShake;

typedef struct GameData GameData;
typedef struct Structure Structure;

typedef struct ObjectEntry {
    void* value;
    void (*destroy_value) (void* value);
} ObjectEntry;


typedef struct Scene {
    char title[200];
    List* render_stack;
    List* structures;
    List* entities;
    List* modifiers; // ceux qu'on peut récupérer en marchant dessus. Liste de SceneModifier*
    char background[200];
    void (*update)(GameData* game);
    void (*populate)(GameData* game);
    void (*event_handler)(GameData* game);
    ScreenShake* screen_shake;

    HashTable* objects;

} Scene;

typedef Scene* (*SceneInit)(GameData* game);

Scene* init_scene(GameData* game, char* title); // Title = nom de la scène = nom du dossier dans scenes/
void render_scene(GameData* game, float delta);
void free_scene(Scene* scene);
void free_scene_void(void* scene);
void change_scene(GameData* game, const char* next);
SDL_Texture* load_texture(SDL_Renderer* renderer, char* path);
void destroy_entities_list(List* entities);
void init_scene_with_json(GameData* game, json_t *root, Scene* scene);

void render_screen_shake(GameData* game);
ScreenShake* init_screen_shake(int duration, int intensity);
void destroy_screen_shake(GameData* game);

#endif

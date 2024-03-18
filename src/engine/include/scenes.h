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
#include "assets.h"

typedef struct GameData GameData;

typedef struct Structure {
    char* identifier;
    SDL_Texture* texture;
    SDL_Rect position;
    int allow_pass_through;
    char* teleport_to_scene;
} Structure;

typedef struct Scene {
    char title[200];
    List* entities;
    char background[200];
    List* structures;
    void (*update)(GameData* game);
    void (*event_handler)(GameData* game);

} Scene;

Scene* init_scene(GameData* game, char* title); // Title = nom de la scène = nom du dossier dans scenes/
void render_scene(GameData* game);
void free_scene(Scene* scene);
void change_scene(void (*next)(void));
SDL_Texture* load_texture(SDL_Renderer* renderer, char* path);

void free_structure(Structure* s);
void init_scene_with_json(GameData* game, json_t *root, Scene* scene);

#endif
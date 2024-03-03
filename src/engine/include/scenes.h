#ifndef SCENES_H
#define SCENES_H

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdio.h>

#include <jansson.h>
#include "assets.h"
#include "entity.h"
#include "linked_list.h"

typedef struct GameData GameData;

typedef struct Structure {
    char* name;
    char* path;
    SDL_Texture* texture;
    SDL_Rect position;
    int allow_pass_through;
    char* teleport_to_scene;
} Structure;

typedef struct Scene {
    char title[200];
    List* entities;
    Texture background;
    List* structures;
    void (*update)(GameData* game);

} Scene;

Scene* init_scene(char* title); // Title = nom de la scène = nom du dossier dans scenes/
void render_scene(GameData* game);
void free_scene(Scene* scene);
void change_scene(void (*next)(void));

void init_scene_with_json(json_t *root, Scene* scene);

#endif
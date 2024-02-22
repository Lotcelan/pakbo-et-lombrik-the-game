#ifndef SCENES_H
#define SCENES_H

#include <SDL2/SDL.h>

typedef struct Scene {
    char title[200];
} Scene;

bool init_scene(Scene* scene);
void free_scene(Scene* scene);
void change_scene(void (*next)(void));

#endif
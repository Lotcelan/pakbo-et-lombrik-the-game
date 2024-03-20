#ifndef SCENE01_H
#define SCENE01_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_scene01(GameData* game);
void populate_scene01(GameData* game);
void event_handler_scene01(GameData* game);
Scene* init_scene01();

#endif
#ifndef EWAN_FIRST_SCENE_H
#define EWAN_FIRST_SCENE_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_ewan_first_scene(GameData* game);
void event_handler_ewan_first_scene(GameData* game);
void populate_ewan_first_scene(GameData* game);
Scene* init_ewan_first_scene(GameData* game);

#endif

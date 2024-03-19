#ifndef SPAWN_LEVEL_H
#define SPAWN_LEVEL_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_spawn_level(GameData* game);
void event_handler_spawn_level(GameData* game);
Scene* init_spawn_level(GameData* game);

#endif
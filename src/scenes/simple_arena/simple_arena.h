#ifndef SIMPLE_ARENA_H
#define SIMPLE_ARENA_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_simple_arena(GameData* game);
void event_handler_simple_arena(GameData* game);
void populate_simple_arena(GameData* game);
Scene* init_simple_arena(GameData* game);

#endif

#ifndef CAVE_H
#define CAVE_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_cave(GameData* game);
void event_handler_cave(GameData* game);
void populate_cave(GameData* game);
Scene* init_cave(GameData* game);

#endif

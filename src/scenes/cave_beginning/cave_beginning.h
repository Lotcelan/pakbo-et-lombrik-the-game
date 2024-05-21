#ifndef CAVE_BEGINNING_H
#define CAVE_BEGINNING_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_cave_beginning(GameData* game);
void event_handler_cave_beginning(GameData* game);
void populate_cave_beginning(GameData* game);
Scene* init_cave_beginning(GameData* game);

#endif
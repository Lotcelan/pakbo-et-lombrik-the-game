#ifndef CAVE2_H
#define CAVE2_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_cave2(GameData* game);
void event_handler_cave2(GameData* game);
void populate_cave2(GameData* game);
Scene* init_cave2(GameData* game);

#endif

#ifndef HUB_LEVEL_H
#define HUB_LEVEL_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_hub_level(GameData* game);
void event_handler_hub_level(GameData* game);
void populate_hub_level(GameData* game);
Scene* init_hub_level(GameData* game);

#endif

#ifndef HUB_H
#define HUB_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_hub(GameData* game);
void event_handler_hub(GameData* game);
void populate_hub(GameData* game);
Scene* init_hub(GameData* game);

#endif

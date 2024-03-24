#ifndef ETAGERE_LEVEL_H
#define ETAGERE_LEVEL_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_etagere_level(GameData* game);
void event_handler_etagere_level(GameData* game);
void populate_etagere_level(GameData* game);
Scene* init_etagere_level(GameData* game);

#endif
#ifndef INTRO2_H
#define INTRO2_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_intro2(GameData* game);
void event_handler_intro2(GameData* game);
void populate_intro2(GameData* game);
Scene* init_intro2(GameData* game);

#endif

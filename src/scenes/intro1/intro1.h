#ifndef INTRO1_H
#define INTRO1_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_intro1(GameData* game);
void event_handler_intro1(GameData* game);
void populate_intro1(GameData* game);
Scene* init_intro1(GameData* game);

#endif

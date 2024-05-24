#ifndef FIRST_BOSS_ROOM_H
#define FIRST_BOSS_ROOM_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_first_boss_room(GameData* game);
void event_handler_first_boss_room(GameData* game);
void populate_first_boss_room(GameData* game);
Scene* init_first_boss_room(GameData* game);

#endif

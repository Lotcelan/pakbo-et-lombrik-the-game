#ifndef PING_PONG_H
#define PING_PONG_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_ping_pong(GameData* game);
void event_handler_ping_pong(GameData* game);
void populate_ping_pong(GameData* game);
Scene* init_ping_pong(GameData* game);

#endif

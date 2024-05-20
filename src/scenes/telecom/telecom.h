#ifndef TELECOM_H
#define TELECOM_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_telecom(GameData* game);
void event_handler_telecom(GameData* game);
void populate_telecom(GameData* game);
Scene* init_telecom(GameData* game);

#endif

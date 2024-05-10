#ifndef CAFET_CROSSING_COUNTERS_H
#define CAFET_CROSSING_COUNTERS_H

#include "../../engine/include/scenes.h"
#include "../../resources.h"

#include <stdio.h>

void update_cafet_crossing_counters(GameData* game);
void event_handler_cafet_crossing_counters(GameData* game);
void populate_cafet_crossing_counters(GameData* game);
Scene* init_cafet_crossing_counters(GameData* game);

#endif

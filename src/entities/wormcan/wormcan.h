#ifndef WORMCAN_H
#define WORMCAN_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_wormcan(GameData* game, Entity* canard01, float delta_t);
void event_handler_wormcan(Entity*, GameData* game);
void update_animation_wormcan(Entity* e, float delta);
Entity* init_wormcan(GameData* game, int x, int y);

#endif
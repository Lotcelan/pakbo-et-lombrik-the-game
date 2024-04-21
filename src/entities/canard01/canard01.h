#ifndef CANARD01_H
#define CANARD01_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_canard01(GameData* game, Entity* canard01, float delta_t);
void event_handler_canard01(Entity*, GameData* game);
void update_animation_canard01(Entity* e, float delta);
Entity* init_canard01(GameData* game, int x, int y);

#endif
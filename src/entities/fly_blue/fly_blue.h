#ifndef FLY_BLUE_H
#define FLY_BLUE_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_fly_blue(GameData* game, Entity* fly_blue, float delta_t);
void event_handler_fly_blue(Entity*, GameData* game);
void update_animation_fly_blue(Entity* e, float delta);
Entity* init_fly_blue(GameData* game, int x, int y);

#endif
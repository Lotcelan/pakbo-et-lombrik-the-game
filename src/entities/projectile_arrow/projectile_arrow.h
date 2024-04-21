#ifndef PROJECTILE_ARROW_H
#define PROJECTILE_ARROW_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_projectile_arrow(GameData* game, Entity* projectile_arrow, float delta_t);
void event_handler_projectile_arrow(Entity*, GameData* game);
void update_animation_projectile_arrow(Entity* e, float delta);
Entity* init_projectile_arrow(GameData* game, int x, int y);

#endif
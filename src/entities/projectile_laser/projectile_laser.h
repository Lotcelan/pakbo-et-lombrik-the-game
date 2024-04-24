#ifndef PROJECTILE_LASER_H
#define PROJECTILE_LASER_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_projectile_laser(GameData* game, Entity* projectile_laser, float delta_t);
void event_handler_projectile_laser(Entity*, GameData* game);
void update_animation_projectile_laser(Entity* e, float delta);
Entity* init_projectile_laser(GameData* game, int x, int y);

#endif
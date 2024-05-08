#ifndef PHYSICS_H
#define PHYSICS_H

#include "game.h"
#include "entity.h"
#include "collisions.h"


Structure* update_entity_movement(GameData* game, Entity* e, float delta_t, bool gravity_enabled);
void follow_player(GameData* game, Entity* e, int x_speed, int y_speed);
void update_gravity(GameData* game, Entity* e, float delta_t);

#endif

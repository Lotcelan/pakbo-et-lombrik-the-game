#ifndef PHYSICS_H
#define PHYSICS_H

#include "game.h"
#include "entity.h"
#include "collisions.h"


void update_entity_movement(GameData* game, Entity* e, float delta_t);
void follow_player(GameData* game, Entity* e);
void update_gravity(GameData* game, Entity* e, float delta_t);

#endif

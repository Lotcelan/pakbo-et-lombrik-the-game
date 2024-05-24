#ifndef GREG_H
#define GREG_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_greg(GameData* game, Entity* greg, float delta_t);
void event_handler_greg(Entity*, GameData* game);
void update_animation_greg(Entity* e, float delta);
Entity* init_greg(GameData* game, int x, int y);

#endif
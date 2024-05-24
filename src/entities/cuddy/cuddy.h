#ifndef CUDDY_H
#define CUDDY_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_cuddy(GameData* game, Entity* cuddy, float delta_t);
void event_handler_cuddy(Entity*, GameData* game);
void update_animation_cuddy(Entity* e, float delta);
Entity* init_cuddy(GameData* game, int x, int y);

#endif
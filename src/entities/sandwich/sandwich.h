#ifndef SANDWICH_H
#define SANDWICH_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_sandwich(GameData* game, Entity* sandwich, float delta_t);
void event_handler_sandwich(Entity*, GameData* game);
void update_animation_sandwich(Entity* e, float delta);
Entity* init_sandwich(GameData* game, int x, int y);

#endif
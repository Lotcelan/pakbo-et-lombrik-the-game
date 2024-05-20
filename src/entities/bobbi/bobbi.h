#ifndef BOBBI_H
#define BOBBI_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_bobbi(GameData* game, Entity* bobbi, float delta_t);
void event_handler_bobbi(Entity*, GameData* game);
void update_animation_bobbi(Entity* e, float delta);
Entity* init_bobbi(GameData* game, int x, int y);

#endif
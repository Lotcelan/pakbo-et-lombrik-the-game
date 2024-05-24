#ifndef JAMES_H
#define JAMES_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_james(GameData* game, Entity* james, float delta_t);
void event_handler_james(Entity*, GameData* game);
void update_animation_james(Entity* e, float delta);
Entity* init_james(GameData* game, int x, int y);

#endif
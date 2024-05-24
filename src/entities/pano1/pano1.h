#ifndef PANO1_H
#define PANO1_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_pano1(GameData* game, Entity* pano1, float delta_t);
void event_handler_pano1(Entity*, GameData* game);
void update_animation_pano1(Entity* e, float delta);
Entity* init_pano1(GameData* game, int x, int y);

#endif
#ifndef PANO2_H
#define PANO2_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_pano2(GameData* game, Entity* pano2, float delta_t);
void event_handler_pano2(Entity*, GameData* game);
void update_animation_pano2(Entity* e, float delta);
Entity* init_pano2(GameData* game, int x, int y);

#endif
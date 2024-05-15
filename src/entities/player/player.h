#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_player(GameData* game, Entity* player, float delta_t);
void event_handler_player(Entity*, GameData* game);
void update_animation_player(Entity* e, float delta);
Entity* init_player(GameData* game, int x, int y);

#endif
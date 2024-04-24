#ifndef DUCK_ORANGE_H
#define DUCK_ORANGE_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_duck_orange(GameData* game, Entity* duck_orange, float delta_t);
void event_handler_duck_orange(Entity*, GameData* game);
void update_animation_duck_orange(Entity* e, float delta);
Entity* init_duck_orange(GameData* game, int x, int y);

#endif
#ifndef DUCK_GREEN_H
#define DUCK_GREEN_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_duck_green(GameData* game, Entity* duck_green, float delta_t);
void event_handler_duck_green(Entity*, GameData* game);
void update_animation_duck_green(Entity* e, float delta);
Entity* init_duck_green(GameData* game, int x, int y);

#endif
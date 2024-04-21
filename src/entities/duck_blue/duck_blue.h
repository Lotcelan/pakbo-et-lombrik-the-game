#ifndef DUCK_BLUE_H
#define DUCK_BLUE_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_duck_blue(GameData* game, Entity* duck_blue, float delta_t);
void event_handler_duck_blue(Entity*, GameData* game);
void update_animation_duck_blue(Entity* e, float delta);
Entity* init_duck_blue(GameData* game, int x, int y);

#endif
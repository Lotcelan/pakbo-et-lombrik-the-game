#ifndef DUCK_PURPLE_H
#define DUCK_PURPLE_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_duck_purple(GameData* game, Entity* duck_purple, float delta_t);
void event_handler_duck_purple(Entity*, GameData* game);
void update_animation_duck_purple(Entity* e, float delta);
Entity* init_duck_purple(GameData* game, int x, int y);

#endif
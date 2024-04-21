#ifndef BLUE_CANARD_BOSS_H
#define BLUE_CANARD_BOSS_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_blue_canard_boss(GameData* game, Entity* blue_canard_boss, float delta_t);
void event_handler_blue_canard_boss(Entity*, GameData* game);
void update_animation_blue_canard_boss(Entity* e, float delta);
Entity* init_blue_canard_boss(GameData* game, int x, int y);

#endif
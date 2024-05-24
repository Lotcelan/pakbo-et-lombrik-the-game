#ifndef FIRST_FINAL_BOSS_H
#define FIRST_FINAL_BOSS_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_first_final_boss(GameData* game, Entity* first_final_boss, float delta_t);
void event_handler_first_final_boss(Entity*, GameData* game);
void update_animation_first_final_boss(Entity* e, float delta);
Entity* init_first_final_boss(GameData* game, int x, int y);

#endif
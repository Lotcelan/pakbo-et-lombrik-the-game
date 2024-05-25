#ifndef CANARD_LAQUE_ICED_H
#define CANARD_LAQUE_ICED_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_canard_laque_iced(GameData* game, Entity* canard_laque_iced, float delta_t);
void event_handler_canard_laque_iced(Entity*, GameData* game);
void update_animation_canard_laque_iced(Entity* e, float delta);
Entity* init_canard_laque_iced(GameData* game, int x, int y);

#endif
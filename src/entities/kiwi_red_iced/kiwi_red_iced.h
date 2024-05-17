#ifndef KIWI_RED_red_iced_H
#define KIWI_RED_ICED_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_kiwi_red_iced(GameData* game, Entity* kiwi_red_iced, float delta_t);
void event_handler_kiwi_red_iced(Entity*, GameData* game);
void update_animation_kiwi_red_iced(Entity* e, float delta);
Entity* init_kiwi_red_iced(GameData* game, int x, int y);

#endif
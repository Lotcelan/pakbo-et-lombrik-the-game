#ifndef KIWI_YELLOW_yellow_iced_H
#define KIWI_YELLOW_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_kiwi_yellow_iced(GameData* game, Entity* kiwi_yellow_iced, float delta_t);
void event_handler_kiwi_yellow_iced(Entity*, GameData* game);
void update_animation_kiwi_yellow_iced(Entity* e, float delta);
Entity* init_kiwi_yellow_iced(GameData* game, int x, int y);

#endif
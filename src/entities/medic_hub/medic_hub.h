#ifndef MEDIC_HUB_H
#define MEDIC_HUB_H

#include<SDL2/SDL.h>

#include"../../engine/include/game.h"
#include"../../engine/include/entity.h"
#include"../../engine/include/physics.h"

void update_medic_hub(GameData* game, Entity* medic_hub, float delta_t);
void event_handler_medic_hub(Entity*, GameData* game);
void update_animation_medic_hub(Entity* e, float delta);
Entity* init_medic_hub(GameData* game, int x, int y);

#endif
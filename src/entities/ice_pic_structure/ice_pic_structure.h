#ifndef ice_pic_structure_H
#define ice_pic_structure_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_ice_pic_structure(GameData* game, Entity* icePicStructure, float delta_t);
void event_handler_ice_pic_structure(Entity*, GameData* game);
void update_animation_ice_pic_structure(Entity* e, float delta);
Entity* init_ice_pic_structure(GameData* game, int x, int y);

#endif
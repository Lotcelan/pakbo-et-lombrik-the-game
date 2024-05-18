#ifndef LA_MOUCHE_BLEUE_H
#define LA_MOUCHE_BLEUE_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_la_mouche_bleue(GameData* game, Entity* la_mouche_bleue, float delta_t);
void event_handler_la_mouche_bleue(Entity*, GameData* game);
void update_animation_la_mouche_bleue(Entity* e, float delta);
Entity* init_la_mouche_bleue(GameData* game, int x, int y);

#endif
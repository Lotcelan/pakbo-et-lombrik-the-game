#ifndef LA_MOUCHE_H
#define LA_MOUCHE_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_la_mouche(GameData* game, Entity* la_mouche, float delta_t);
void event_handler_la_mouche(Entity*, GameData* game);
void update_animation_la_mouche(Entity* e, float delta);
Entity* init_la_mouche(GameData* game, int x, int y);

#endif
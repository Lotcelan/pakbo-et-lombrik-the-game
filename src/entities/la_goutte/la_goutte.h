#ifndef LA_GOUTTE_H
#define LA_GOUTTE_H

#include <SDL2/SDL.h>

#include "../../engine/include/entity.h"
#include "../../engine/include/game.h"
#include "../../engine/include/physics.h"

void update_la_goutte(GameData* game, Entity* la_goutte, float delta_t);
void event_handler_la_goutte(Entity*, GameData* game);
void update_animation_la_goutte(Entity* e, float delta);
Entity* init_la_goutte(GameData* game, int x, int y);

#endif
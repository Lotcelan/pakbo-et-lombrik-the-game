#ifndef ARBALETE_H
#define ARBALETE_H

#include "../../engine/include/weapon.h"

void update_arbalete(GameData* game, Entity* e, float delta_t);
void event_handler_arbalete(GameData* game, Weapon* weapon, Entity* e);
void render_arbalete(GameData* game, Entity* e, float delta_t);

Weapon* init_arbalete(GameData* game);

#endif
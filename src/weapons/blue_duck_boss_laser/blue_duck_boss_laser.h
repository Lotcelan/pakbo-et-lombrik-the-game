#ifndef BLUE_DUCK_BOSS_LASER_H
#define BLUE_DUCK_BOSS_LASER_H

#include "../../engine/include/weapon.h"

void update_blue_duck_boss_laser(GameData* game, Entity* e, float delta_t);
void event_handler_blue_duck_boss_laser(GameData* game, Weapon* weapon, Entity* e);
void render_blue_duck_boss_laser(GameData* game, Entity* e, float delta_t);

Weapon* init_blue_duck_boss_laser(GameData* game);

#endif
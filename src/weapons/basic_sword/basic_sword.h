#ifndef BASIC_SWORD_H
#define BASIC_SWORD_H

#define BASIC_SWORD_ATTACK_DURATION 250

#include "../../engine/include/weapon.h"

void update_basic_dword(GameData* game, Entity* e, float delta_t);
void event_handler_basic_sword(GameData* game, Weapon* weapon, Entity* e);
void render_basic_sword(GameData* game, Entity* e, float delta_t);

Weapon* init_basic_sword(GameData* game);

#endif
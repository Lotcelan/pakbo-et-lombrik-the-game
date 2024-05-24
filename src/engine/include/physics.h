#ifndef PHYSICS_H
#define PHYSICS_H

#include "game.h"
#include "entity.h"
#include "collisions.h"
#include "linked_list.h"
#include "binary_heap.h"
#include "grid_graph.h"

Structure* update_entity_movement(GameData* game, Entity* e, float delta_t, bool gravity_enabled);
Structure* do_the_moves(GameData* game, Entity* e, int delta_x, int delta_y);
void follow_player(GameData* game, Entity* e, int x_speed, int y_speed);
void update_gravity(GameData* game, Entity* e, float delta_t);
GridGraph* a_star(Entity* entity_from, Entity* entity_to, GameData* game);
void follow_player_using_a_star(GameData* game, Entity* e, int x_speed, int y_speed);
GridGraph* create_grid_graph_from_game(GameData* game, Entity* entity_from);
float heuristic_a_star(int x1, int y1, int x2, int y2);
bool detect_player(GameData* game, Entity* e, int radius);
#endif

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SDL2/SDL.h>
#include "game.h"
#include "entity.h"
#include "assets.h"
#include "linked_list.h"

typedef struct GameData GameData;
typedef struct Structure Structure;
typedef struct Entity Entity;

typedef struct Box {
    SDL_Rect zone;
} Box;

Box* init_rect_box(int x, int y, int w, int h);
Box* init_rect_box_from_entity(GameData* game, Entity* e);
Box* init_rect_box_from_structure(GameData* game, Structure* s);
bool are_colliding(Box* a, Box* b);
Structure* is_entity_colliding_with_structures(Entity* e, List* structures);
Box* copy_box(Box* a);
void free_box(Box* box);
void update_entity_boxes(Entity* e);
void enlarge_entity_hitbox(Entity* e, Box* new_hitbox);
void change_structure_coordinates(GameData* game, Structure* s, int x, int y);
Structure* is_entity_touching_the_top_of_a_structure(Entity* e, List* s_list);

#endif

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
bool is_entity_colliding_with_structures(Entity* e, List* structures);
void free_box(Box* box);
void update_entity_boxes(Entity* e);
#endif

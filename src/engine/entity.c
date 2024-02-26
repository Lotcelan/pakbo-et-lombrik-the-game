#include "include/entity.h"

void update_self(Entity* e) {
    // Update the entity
    e->update(e);
}

Entity* init_entity(char* entity, int respawn_delay, int x, int y) {
    return NULL;
}

void update_entities(List* entities) {
    // Map to each entity the update function contained in the Entity struct
    map(update_self, entities);
}
#include "./include/physics.h"

void update_entity_movement(GameData* game, Entity* e, float delta_t) {
    if (game->current_scene == NULL) {
        return;
    }
    int prev_x = e->x_position;
    int prev_y = e->y_position;
    
    int delta_x = floor(delta_t * e->x_velocity);
    int delta_y = floor(delta_t * e->y_velocity);

    e->x_position = e->x_position + delta_x;
    e->y_position = e->y_position + delta_y;
    update_entity_boxes(e);

    if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
        
        e->x_position = prev_x;
        e->y_position = prev_y;
        update_entity_boxes(e);
    }

}
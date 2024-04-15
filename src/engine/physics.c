#include "./include/physics.h"

void update_entity_movement(GameData* game, Entity* e, float delta_t, bool gravity_enabled) {
    if (gravity_enabled) {
        update_gravity(game, e, delta_t);
    }
    if (game->current_scene == NULL) {
        return;
    }
    int prev_x = e->x_position;
    int prev_y = e->y_position;
    
    // todo : normalisation de la vitesse en diagonale avec un /sqrt(2)
    int delta_x = floor(delta_t * e->x_velocity / 1000); // delta_t en ms
    int delta_y = floor(delta_t * e->y_velocity / 1000);

    e->x_position = e->x_position + delta_x;
    e->y_position = e->y_position + delta_y;
    update_entity_boxes(e);

    if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
        
        e->x_position = prev_x;
        e->x_velocity = 0;
        e->y_position = prev_y;
        e->y_velocity = 0;
        update_entity_boxes(e);
    }

}

void update_gravity(GameData* game, Entity* e, float delta_t) {
    if (game->current_scene == NULL) {
        return;
    }

    float gravity = 250;
    int prev_y = e->y_position;
    e->y_velocity += gravity * delta_t / 1000;
    if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
        e->y_position = prev_y;
    }
    
}

void follow_player(GameData* game, Entity* e) {
    if (game->current_scene == NULL) {
        return;
    }
    Entity* player = game->player;
    if (player == NULL) {
        return;
    }
    int player_x = player->x_position;
    int player_y = player->y_position;
    int e_x = e->x_position;
    int e_y = e->y_position;
    if (player_x > e_x) {
        e->x_velocity = 50;
    } else if (player_x < e_x) {
        e->x_velocity = -50;
    } else {
        e->x_velocity = 0;
    }
    if (player_y > e_y) {
        e->y_velocity = 50;
    } else if (player_y < e_y) {
        e->y_velocity = -50;
    } else {
        e->y_velocity = 0;
    }

}

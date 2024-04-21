#include "./include/physics.h"

bool update_entity_movement(GameData* game, Entity* e, float delta_t, bool gravity_enabled) {
    // returns true if it has collided with something
    
    if (gravity_enabled) {
        update_gravity(game, e, delta_t);
    }
    if (game->current_scene == NULL) {
        return false;
    }

    if ((e->x_velocity == 0 && e->y_velocity == 0) || (e->x_position == -1 && e->y_position == -1)) {
        return false;
    }

    // int prev_x = e->x_position;
    // int prev_y = e->y_position;
    
    // todo : normalisation de la vitesse en diagonale avec un /sqrt(2)
    // int delta_x = floor(delta_t * e->x_velocity / 1000); // delta_t en ms
    // int sign_x = delta_x > 0 ? 1 : -1;
    // for (int current = 0; current < delta_x; current++) {
    //     e->x_position = e->x_position + delta_x + sign_x * current;
    //     update_entity_boxes(e);
        
    //     if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
    //         e->x_position = prev_x;
    //         update_entity_boxes(e);
    //         continue;
    //     }
    //     break;
    // }
    // int delta_y = floor(delta_t * e->y_velocity / 1000); // delta_t en ms
    // int sign_y = delta_y > 0 ? 1 : -1;
    // for (int current = 0; current < delta_y; current++) {
    //     e->y_position = e->y_position + delta_y + sign_y * current;
    //     printf("Prev : %d, Current : %d, Delta : %d\n", prev_y, e->y_position, delta_y);
    //     update_entity_boxes(e);
    //     if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
    //         e->y_position = prev_y;
    //         update_entity_boxes(e);
    //         continue;
    //     }
    //     break;
    // }
    bool is_colliding = false;
    int delta_x, delta_y;
    bool result = false;
    // double velocityMagnitude = sqrt(e->x_velocity * e->x_velocity + e->y_velocity * e->y_velocity);
    // if (velocityMagnitude > 0) {
    //     double normalizedXVelocity = e->x_velocity / velocityMagnitude;
    //     double normalizedYVelocity = e->y_velocity / velocityMagnitude;

    //     delta_x = delta_t * normalizedXVelocity / 1000; // delta_t en ms
    //     delta_y = delta_t * normalizedYVelocity / 1000; // delta_t en ms
    // }
    // printf("Delta X : %d, Delta Y : %d\n", delta_x, delta_y);

    delta_x = delta_t * e->x_velocity / 1000; // delta_t en ms
    delta_y = delta_t * e->y_velocity / 1000; // delta_t en ms
    int sign_x = delta_x > 0 ? 1 : -1;
    int sign_y = delta_y > 0 ? 1 : -1;
    delta_x = abs(delta_x);
    delta_y = abs(delta_y);
    bool has_collided = false;

    while (delta_x >= 0) {
        // e->x_position = e->x_position + sign_x * delta_x;
        // printf("Je pourrai être en X : %d\n", e->x_position);
        // update_entity_boxes(e, prev_x, prev_y);
        // temp_prev = e->x_position;
        change_entity_coordinates(e, e->x_position + sign_x * delta_x, e->y_position);

        if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
            is_colliding = true;
            has_collided = true;
        } else {
            break;
        }
        if (is_colliding) {
            change_entity_coordinates(e, e->prev_collision_box->zone.x, e->prev_collision_box->zone.y);

            // update_entity_boxes(e, temp_prev, prev_y);
            // prev_x = e->x_position;
            delta_x--; // d'ici a ce qu'on fasse du raymarching :)
            is_colliding = false;
            
        }
    }
    if (has_collided) {
        e->x_velocity = 0;
    }
    result = result || has_collided;
    has_collided = false;
    is_colliding = false;

    while (delta_y >= 0) {
        // e->y_position = e->y_position + sign_y * delta_y;
        // printf("Je pourrai être en Y : %d, delta = %d\n", e->y_position, delta_y);
        // update_entity_boxes(e, prev_x, prev_y);
        // temp_prev = e->y_position;
        change_entity_coordinates(e, e->x_position, e->y_position + sign_y * delta_y);

        if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
            is_colliding = true;
            has_collided = true;
        } else {
            break;
        }
        if (is_colliding) {
            // e->y_position = prev_y;
            // update_entity_boxes(e, prev_x, temp_prev);
            change_entity_coordinates(e, e->x_position, e->prev_collision_box->zone.y);
            // prev_y = e->y_position;
            delta_y--; // d'ici a ce qu'on fasse du raymarching :)
            is_colliding = false;
            
        }
    }
    if (has_collided) {
        e->y_velocity = 0;
    }
    result = result || has_collided;

    return result;

}

void update_gravity(GameData* game, Entity* e, float delta_t) {
    if (game->current_scene == NULL) {
        return;
    }

    float gravity = 250;
    e->y_velocity += gravity * delta_t / 1000;
    // if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
    //     e->y_position = prev_y;
    //     update_entity_boxes(e, e->x_position, prev_y);
    // }
    
}

void follow_player(GameData* game, Entity* e, int x_speed, int y_speed) {
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
        e->x_velocity = x_speed;
    } else if (player_x < e_x) {
        e->x_velocity = -x_speed;
    } else {
        e->x_velocity = 0;
    }
    // if (player_y > e_y) {
    //     e->y_velocity = y_speed;
    // } else if (player_y < e_y) {
    //     e->y_velocity = -y_speed;
    // } else {
    //     e->y_velocity = 0;
    // }

}

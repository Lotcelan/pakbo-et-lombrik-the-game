#include "blue_duck_boss_laser.h"

void update_blue_duck_boss_laser(GameData* game, Entity* e, float delta_t) {
    if (e == NULL) {
        return;
    }

    bool* is_shooting = get(e->weapon->objects, "is_shooting", strcmp);
    int* attack_duration = get(e->weapon->objects, "attack_duration", strcmp);
    List* projectiles = get(e->weapon->objects, "projectiles", strcmp);

    if (is_shooting == NULL || attack_duration == NULL) {
        return;
    }



    if (*is_shooting) {
        if (*attack_duration == -1) {
            *attack_duration = 1000;
            
            EntityInitFunc* projectile_func = get(game->entities, "projectile_laser", strcmp);
            if (projectile_func == NULL) {
                return;
            }
            Entity* projectile = (*projectile_func)(game, e->x_position + 16, e->y_position + 16);
            projectile->parent = e;
            // int sign = 1;
            if (e->sprite->orientation == SDL_FLIP_HORIZONTAL) {
                // sign = -1;
                projectile->sprite->orientation = SDL_FLIP_HORIZONTAL;
            }
            int player_x = game->player->x_position;
            int player_y = game->player->y_position;
            int e_x = e->x_position + 16;
            int e_y = e->y_position + 16;
            // compute the x and y velocity to reach the player

            float distance = sqrt(pow(player_x - e_x, 2) + pow(player_y - e_y, 2));
            projectile->y_velocity = (player_y - e_y) / distance * 100;
            projectile->x_velocity = (player_x - e_x) / distance * 100;

            replace(e->weapon->objects, "projectiles", append_first(projectile, projectiles), free, strcmp);
        } else {
            *attack_duration -= delta_t;
            if (*attack_duration <= 0) {
                *attack_duration = -1;
            }
        }
        *is_shooting = false;
    } else {
        *attack_duration -= delta_t;
        if (*attack_duration <= 0) {
            *attack_duration = -1;
            *is_shooting = true;
        }
    }

    // // Check if the attack hit an enemy
    // if (is_attacking != NULL) {
    //     if (*is_attacking) {
    //         List* current = game->current_scene->entities;
    //         while (current != NULL) {
    //             if (current->value != e) { // inutile si c'est le joueur qui a l'épée
    //                 if (are_colliding(e->hit_box, ((Entity*)(current->value))->hurt_box)) {
    //                     bool should_delay = e != game->player;
    //                     damage_entity(game, (Entity*)current->value, e->weapon->damage_value, should_delay);
    //                 }
    //             }
    //             current = current->next;
    //         }
    //     }
    // }


    List* current = get(e->weapon->objects, "projectiles", strcmp);
    while (current != NULL) {
        Entity* projectile = (Entity*)(current->value);
        if (projectile != NULL) {
            projectile->update(game, projectile, delta_t);
            // projectile->update_animation(projectile, delta_t);
        }
        current = current->next;
    }

    current = get(e->weapon->objects, "projectiles", strcmp);
    while (current != NULL){
        Entity* entity = (Entity*)current->value;
        if (entity->current_hp <= 0){
            replace(e->weapon->objects, "projectiles", delete_compare(get(e->weapon->objects, "projectiles", strcmp), entity, compare_entities, free_entity), free, strcmp);
            current = get(e->weapon->objects, "projectiles", strcmp);
            continue;
        }
        current = current->next;
    }

    return;
}

void event_handler_blue_duck_boss_laser(GameData* game, Weapon* weapon, Entity* e) {
    (void)game;
    (void)e;
    (void)weapon;
}

void render_blue_duck_boss_laser(GameData* game, Entity* e, float delta_t) {
    // Do nothing
    // for now just draw a rectangle
    if (e == NULL) {
        return;
    }

    List* projectiles = get(e->weapon->objects, "projectiles", strcmp);
    if (projectiles != NULL) {
        List* current = projectiles;
        while (current != NULL) {
            render_entity(game, (Entity*)(current->value), delta_t);
            current = current->next;
        }

    }


    return;
}

Weapon* init_blue_duck_boss_laser(GameData* game) {
    (void)game;
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    weapon->name = "blue_duck_boss_laser";
    weapon->damage_value = 2;
    weapon->max_durability = -1; // Infinite durability
    weapon->current_durability = -1;
    weapon->update = update_blue_duck_boss_laser;
    weapon->event_handler = event_handler_blue_duck_boss_laser;
    weapon->render = render_blue_duck_boss_laser;
    weapon->objects = createHashTable(10);

    bool* is_shooting = (bool*)malloc(sizeof(bool));
    *is_shooting = false;
    insert(weapon->objects, "is_shooting", is_shooting, free);

    int* attack_duration = (int*)malloc(sizeof(int));
    *attack_duration = -1;
    insert(weapon->objects, "attack_duration", attack_duration, free);

    List* projectiles = NULL;
    insert(weapon->objects, "projectiles", projectiles, free_entity_list);

    return weapon;
}
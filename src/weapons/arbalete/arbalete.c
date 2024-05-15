#include "arbalete.h"

void update_arbalete(GameData* game, Entity* e, float delta_t) {
    if (e == NULL) {
        return;
    }

    bool* is_shooting = get(e->weapon->objects, "is_shooting", strcmp);
    int* attack_duration = get(e->weapon->objects, "attack_duration", strcmp);
    // List* projectiles = get(e->weapon->objects, "projectiles", strcmp);

    if (is_shooting == NULL || attack_duration == NULL) {
        return;
    }



    if (*is_shooting) {
        if (*attack_duration == -1) {
            *attack_duration = 1000;
            
            EntityInitFunc* projectile_func = get(game->entities, "projectile_arrow", strcmp);
            if (projectile_func == NULL) {
                return;
            }
            Entity* projectile = (*projectile_func)(game, e->x_position, e->y_position);
            projectile->parent = e;
            game->current_scene->entities = append_first(projectile, game->current_scene->entities);
            
            int sign = 1;
            if (e->sprite->orientation == SDL_FLIP_HORIZONTAL) {
                sign = -1;
                projectile->sprite->orientation = SDL_FLIP_HORIZONTAL;
            }
            projectile->x_velocity = e->x_velocity + sign * 100;
            
            // List* copy_projectiles = copy_list(projectiles, copy_entity);
            // replace(e->weapon->objects, "projectiles", append_first(projectile, copy_projectiles), free_entity_list, strcmp);
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


    // List* current = (List*)get(e->weapon->objects, "projectiles", strcmp);
    // while (current != NULL) {
    //     Entity* projectile = (Entity*)(current->value);
    //     if (projectile != NULL) {
    //         projectile->update(game, projectile, delta_t);
    //     }
    //     current = current->next;
    // }

    // current = get(e->weapon->objects, "projectiles", strcmp);
    // while (current != NULL){
    //     Entity* entity = (Entity*)current->value;
    //     if (entity->current_hp <= 0){
    //         List* projectiles_without_dead_one = delete_compare(get(e->weapon->objects, "projectiles", strcmp), entity, compare_entities, free_entity);
    //         replace(e->weapon->objects, "projectiles", projectiles_without_dead_one, free_entity_list, strcmp);
    //         current = get(e->weapon->objects, "projectiles", strcmp);
    //         continue;
    //     }
    //     current = current->next;
    // }

    return;
}

void event_handler_arbalete(GameData* game, Weapon* weapon, Entity* e) {
    // If "x" pressed, attack
    (void)e;
    // int* attack_duration = get(weapon->objects, "attack_duration", strcmp);
    bool* is_shooting = get(weapon->objects, "is_shooting", strcmp);
    switch (game->event.type) {
        case SDL_KEYDOWN:
            if (game->event.key.keysym.sym == SDLK_x) {
                // Attack
                if (is_shooting != NULL) {
                    *is_shooting = true;
                    
                }

            }
            break;
    }
}

void render_arbalete(GameData* game, Entity* e, float delta_t) {

    if (e == NULL) {
        return;
    }

    // List* projectiles = get(e->weapon->objects, "projectiles", strcmp);
    // if (projectiles != NULL) {
    //     List* current = projectiles;
    //     while (current != NULL) {
    //         render_entity(game, (Entity*)(current->value), delta_t);
    //         current = current->next;
    //     }

    // }


    return;
}

Weapon* init_arbalete(GameData* game) {
    (void)game;
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    weapon->name = "arbalete";
    weapon->damage_value = 1;
    weapon->max_durability = -1; // Infinite durability
    weapon->current_durability = -1;
    weapon->update = update_arbalete;
    weapon->event_handler = event_handler_arbalete;
    weapon->render = render_arbalete;
    weapon->objects = createHashTable(10);

    bool* is_shooting = (bool*)malloc(sizeof(bool));
    *is_shooting = false;
    insert(weapon->objects, "is_shooting", is_shooting, free);

    int* attack_duration = (int*)malloc(sizeof(int));
    *attack_duration = -1;
    insert(weapon->objects, "attack_duration", attack_duration, free);

    // List* projectiles = NULL;
    // insert(weapon->objects, "projectiles", projectiles, free);

    return weapon;
}
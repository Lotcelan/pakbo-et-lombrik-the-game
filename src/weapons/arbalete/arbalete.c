#include "arbalete.h"

void update_arbalete(GameData* game, Entity* e, float delta_t) {
    if (e == NULL) {
        return;
    }

    bool* is_shooting = get(e->weapon->objects, "is_shooting", strcmp);
    int* attack_duration = get(e->weapon->objects, "attack_duration", strcmp);

    if (is_shooting == NULL || attack_duration == NULL) {
        return;
    }



    if (*is_shooting) {
        if (*attack_duration == -1) {
            *attack_duration = 1000;
            List* projectiles = get(e->weapon->objects, "projectiles", strcmp);
            if (projectiles == NULL) {
                return;
            }
            EntityInitFunc* projectile_func = get(game->entities, "projectile_arrow", strcmp);
            if (projectile_func == NULL) {
                return;
            }
            Entity* projectile = (*projectile_func)(game, e->x_position, e->y_position);
            replace(e->weapon->objects, "projectiles", append_first(projectile, projectiles), strcmp);
            *is_shooting = false;
        } else {
            *attack_duration -= delta_t;
            if (*attack_duration <= 0) {
                *attack_duration = -1;
            }
        }
    } else {
        *attack_duration = -1;
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

    clear_entities(game);


    return;
}

void event_handler_arbalete(GameData* game, Weapon* weapon, Entity* e) {
    // If "x" pressed, attack
    int* attack_duration = get(weapon->objects, "attack_duration", strcmp);
    bool* is_shooting = get(weapon->objects, "is_shooting", strcmp);
    switch (game->event.type) {
        case SDL_KEYDOWN:
            if (game->event.key.keysym.sym == SDLK_x) {
                // Attack
                if (is_shooting != NULL) {
                    if (!(*is_shooting)) {
                        *is_shooting = true;
                    }
                }

            }
            break;
    }
}

void render_arbalete(GameData* game, Entity* e, float delta_t) {
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

Weapon* init_arbalete(GameData* game) {
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
    insert(weapon->objects, "is_shooting", is_shooting);

    int* attack_duration = (int*)malloc(sizeof(int));
    *attack_duration = -1;
    insert(weapon->objects, "attack_duration", attack_duration);

    List* projectiles = NULL;
    insert(weapon->objects, "projectiles", projectiles);

    return weapon;
}
#include "blue_duck_boss_laser.h"

void update_blue_duck_boss_laser(GameData* game, Entity* e, float delta_t) {
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
            
            EntityInitFunc* projectile_func = get(game->entities, "projectile_laser", strcmp);
            if (projectile_func == NULL) {
                return;
            }
            Entity* projectile = (*projectile_func)(game, e->x_position + 16, e->y_position + 8);
            projectile->parent = e;
            game->current_scene->entities = append_first(projectile, game->current_scene->entities);
            
            int player_x = game->player->x_position + 8;
            int player_y = game->player->y_position + 8;
            int e_x = e->x_position + 16;
            int e_y = e->y_position + 8;
            // compute the x and y velocity to reach the player

            float distance = sqrt(pow(player_x - e_x, 2) + pow(player_y - e_y, 2));
            projectile->y_velocity = (player_y - e_y) / distance * 100;
            projectile->x_velocity = (player_x - e_x) / distance * 100;



            // int sign = 1;
            // if (e->sprite->orientation == SDL_FLIP_HORIZONTAL) {
            //     sign = -1;
            //     projectile->sprite->orientation = SDL_FLIP_HORIZONTAL;
            // }
            // projectile->x_velocity = e->x_velocity + sign * 100;
            
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
            *is_shooting = true;
        }
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



    return;
}

Weapon* init_blue_duck_boss_laser(GameData* game) {
    (void)game;
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    weapon->name = "blue_duck_boss_laser";
    weapon->damage_value = 1;
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


    return weapon;
}
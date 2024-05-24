#include <SDL2/SDL.h>
#include "projectile_laser.h"


void update_projectile_laser(GameData* game, Entity* projectile_laser, float delta_t) {
    if (projectile_laser == NULL) {
        return;
    }

    bool* is_exploding = get(projectile_laser->objects, "is_exploding", strcmp);

    if (*is_exploding) {
        
        printf("%d\n", ((int*)(projectile_laser->sprite->currentFrame->value))[0]);
    }

    if (is_exploding != NULL) {
        if (*is_exploding && ((int*)(projectile_laser->sprite->currentFrame->value))[0]  == 3) {
            // printf("je dead ca\n");
            projectile_laser->current_hp = -1;
            
            return;
        }
    }

    // follow_player(game, projectile_laser, 200, 200);
    Structure* has_collided = update_entity_movement(game, projectile_laser, delta_t, false);


    if (has_collided != NULL) {
        if (is_exploding != NULL) {
            *is_exploding = true;
            projectile_laser->x_velocity = 0;
            projectile_laser->y_velocity = 0;
            return;
        }
    }
    // if (are_colliding(projectile_laser->hit_box, game->player->hurt_box)) {
    //     damage_entity(game, game->player, 1, true);
    // }
    

    // List* current_entity = append_first(game->player, game->current_scene->entities);
    // while (current_entity != NULL && projectile_laser->current_hp > 0) {
    //     Entity* entity = (Entity*)(current_entity->value);
    //     if (!compare_entities(entity, projectile_laser->parent)) {
    //         if (are_colliding(projectile_laser->hit_box, entity->hurt_box)) {
    //             damage_entity(game, entity, projectile_laser->parent->weapon->damage_value, 100, 100, false, projectile_laser);
    //             if (is_exploding != NULL) {
    //                 printf("exploding\n");
    //                 *is_exploding = true;
    //                 projectile_laser->x_velocity = 0;
    //                 projectile_laser->y_velocity = 0;
    //                 return;
    //             }
    //             break;
    //         }
    //     }
    //     current_entity = current_entity->next;
    // }
    if (are_colliding(projectile_laser->hit_box, game->player->hurt_box) || projectile_laser->x_velocity == 0 || projectile_laser->y_velocity == 0 ) {
        if (are_colliding(projectile_laser->hit_box, game->player->hurt_box)) damage_entity(game, game->player, projectile_laser->parent->weapon->damage_value, 100, 100, false, projectile_laser);
        if (is_exploding != NULL) {
            *is_exploding = true;
            projectile_laser->x_velocity = 0;
            projectile_laser->y_velocity = 0;
            return;
        }
    }

    

    return;
}
void event_handler_projectile_laser(Entity* projectile_laser, GameData* game) {
    (void)projectile_laser;
    (void)game;
    return;
}

void update_animation_projectile_laser(Entity* e, float delta) {
    (void)delta;
    bool* is_exploding = get(e->objects, "is_exploding", strcmp);
    if (is_exploding != NULL) {
        if (*is_exploding) {
            e->etat = 1;
        }
    }

    return;
}

Entity* init_projectile_laser(GameData* game, int x, int y) {
    printf("initiating projectile_laser\n");
    int* nbs = malloc(2*sizeof(int));
    nbs[0] = 1;
    nbs[1] = 4;
    int* lock = malloc(2*sizeof(int));
    lock[0] = 0;
    lock[1] = 4;
    
    SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_projectiles_projectile_laser"); // to change

    Entity* projectile_laser = init_entity(x, y, 14, spritesheet, 5, 5, nbs, lock, update_projectile_laser, event_handler_projectile_laser, update_animation_projectile_laser, 9999, true);

    bool* is_exploding = malloc(sizeof(bool));
    *is_exploding = false;
    insert(projectile_laser->objects, "is_exploding", is_exploding, free);

    projectile_laser->hurt_box = NULL;

    return projectile_laser;
}

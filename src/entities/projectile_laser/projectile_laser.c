#include <SDL2/SDL.h>
#include "projectile_laser.h"


void update_projectile_laser(GameData* game, Entity* projectile_laser, float delta_t) {
    if (projectile_laser == NULL) {
        return;
    }

    bool* is_exploding = get(projectile_laser->objects, "is_exploding", strcmp);
    if (is_exploding != NULL) {
        if (*is_exploding) {
            projectile_laser->current_hp = -1;
            return;
        }
    }

    follow_player(game, projectile_laser, 200, 200);
    bool has_collided = update_entity_movement(game, projectile_laser, delta_t, false);


    if (has_collided) {
        if (is_exploding != NULL) {
            *is_exploding = true;
            return;
        }
    }
    // if (are_colliding(projectile_laser->hit_box, game->player->hurt_box)) {
    //     damage_entity(game, game->player, 1, true);
    // }
    

    List* current_entity = append_first(game->player, game->current_scene->entities);
    while (current_entity != NULL && projectile_laser->current_hp > 0) {
        Entity* entity = (Entity*)(current_entity->value);
        if (!compare_entities(entity, projectile_laser->parent)) {
            if (are_colliding(projectile_laser->hit_box, entity->hurt_box)) {
                damage_entity(game, entity, projectile_laser->parent->weapon->damage_value, 100, 100);
                if (is_exploding != NULL) {
                    printf("exploding\n");
                    *is_exploding = true;
                    return;
                }
                break;
            }
        }
        current_entity = current_entity->next;
    }

    return;
}
void event_handler_projectile_laser(Entity* projectile_laser, GameData* game) {
    return;
}

void update_animation_projectile_laser(Entity* e, float delta) {
    bool* is_exploding = get(e->objects, "is_exploding", strcmp);
    if (is_exploding != NULL) {
        if (*is_exploding) {
            e->etat = 2;
        }
    }

    return;
}

Entity* init_projectile_laser(GameData* game, int x, int y) {
    printf("initiating projectile_laser\n");
    int* nbs = malloc(2*sizeof(int));
    nbs[0] = 1;
    nbs[1] = 1;
    int* lock = malloc(2*sizeof(int));
    lock[0] = 0;
    lock[0] = 1;
    
    SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_projectile_laser"); // to change

    Entity* projectile_laser = init_entity(x, y, 1, spritesheet, 5, 5, nbs, lock, update_projectile_laser, event_handler_projectile_laser, update_animation_projectile_laser, 9999, true);

    bool* is_exploding = malloc(sizeof(bool));
    *is_exploding = false;
    insert(projectile_laser->objects, "is_exploding", is_exploding);

    return projectile_laser;
}

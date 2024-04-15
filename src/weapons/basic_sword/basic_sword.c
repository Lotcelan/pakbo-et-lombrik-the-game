#include "basic_sword.h"

void update_basic_dword(GameData* game, Entity* e, float delta_t) {
    if (e == NULL) {
        return;
    }

    bool* is_attacking = get(e->weapon->objects, "is_attacking", strcmp);
    int* attack_duration = get(e->weapon->objects, "attack_duration", strcmp);

    if (is_attacking != NULL) {
        if (*is_attacking) {
            if (attack_duration != NULL) {
                if (*attack_duration > 0) {
                    *attack_duration -= delta_t;
                    printf("Attack duration: %d\n", *attack_duration);
                } else {
                    *is_attacking = false;
                    *attack_duration = -1;
                }
            }
        }
    }

    // Check if the attack hit an enemy
    if (is_attacking != NULL) {
        if (*is_attacking) {
            List* current = game->current_scene->entities;
            while (current != NULL) {
                if (current->value != e) { // inutile si c'est le joueur qui a l'épée
                    if (are_colliding(e->hit_box, ((Entity*)(current->value))->hurt_box)) {
                        bool should_delay = e != game->player;
                        damage_entity(game, (Entity*)current->value, e->weapon->damage_value, should_delay);
                    }
                }
                current = current->next;
            }
        }
    }



    return;
}

void event_handler_basic_sword(GameData* game, Weapon* weapon, Entity* e) {
    // If "x" pressed, attack
    int* attack_duration = get(weapon->objects, "attack_duration", strcmp);
    bool* is_attacking = get(weapon->objects, "is_attacking", strcmp);
    if (is_attacking == NULL) {
        return;
    }
    
    switch (game->event.type) {
        case SDL_KEYDOWN:
            if (game->event.key.keysym.sym == SDLK_x) {
                // Attack
                if (is_attacking != NULL) {
                    if (!(*is_attacking)) {
                        *is_attacking = true;
                        *attack_duration = 250;
                    }
                }
            }
            break;
    }
}

void render_basic_sword(GameData* game, Entity* e, float delta_t) {
    // Do nothing
    // for now just draw a rectangle
    if (e == NULL) {
        return;
    }

    bool* is_attacking = get(e->weapon->objects, "is_attacking", strcmp);
    if (is_attacking != NULL) {
            // printf("Attacking\n");
        if (*is_attacking) {
            SDL_Rect rect;
            if (e->sprite->orientation == SDL_FLIP_NONE) {
                rect = (SDL_Rect){.x = e->x_position + 16, .y = e->y_position + 8, .w=24, .h=4};
            } else  {
                rect = (SDL_Rect){.x=e->x_position-24,.y= e->y_position + 8, .w=24, .h=4};
            }

            Box* sword_box = init_rect_box(rect.x, rect.y, rect.w, rect.h);
            enlarge_entity_hitbox(e, sword_box);
            free_box(sword_box);

            SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(game->renderer, &rect);
        }

    }
    return;
}

Weapon* init_basic_sword(GameData* game) {
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    weapon->name = "basic_sword";
    weapon->damage_value = 1;
    weapon->max_durability = -1; // Infinite durability
    weapon->current_durability = -1;
    weapon->update = update_basic_dword;
    weapon->event_handler = event_handler_basic_sword;
    weapon->render = render_basic_sword;
    weapon->objects = createHashTable(10);

    bool* is_attacking = (bool*)malloc(sizeof(bool));
    *is_attacking = false;
    insert(weapon->objects, "is_attacking", is_attacking);

    int* attack_duration = (int*)malloc(sizeof(int));
    *attack_duration = -1;
    insert(weapon->objects, "attack_duration", attack_duration);

    return weapon;
}
#include <SDL2/SDL.h>
#include "player.h"

// SECTION ENTITE
void update_player(GameData* game, Entity* player, float delta_t) {
    if (player == NULL) {
        return;
    }
    // bool* is_going_down = get(player->objects, "is_going_down", strcmp);
    // bool* is_going_up = get(player->objects, "is_going_up", strcmp);
    // bool* is_going_left = get(player->objects, "is_going_left", strcmp);
    // bool* is_going_right = get(player->objects, "is_going_right", strcmp);

    // if (is_going_down == NULL || is_going_up == NULL || is_going_left == NULL || is_going_right == NULL) {
    //     return;
    // }

    // if (*is_going_down) {
    //     player->y_position += 1;
    // }
    // if (*is_going_up) {
    //     player->y_position -= 1;
    // }
    // if (*is_going_left) {
    //     player->x_position -= 1;
    // }
    // if (*is_going_right) {
    //     player->x_position += 1;
    // }
    // return;

    if (player->current_hp <= 0) {
        player->current_hp = player->max_hp;
        change_scene(game, "game_over_-1_-1");
        player->damage_delay = -1;
        return;
    }
    
    update_entity_movement(game, player, delta_t, true);

    int* jump_amount = get(player->objects, "jump_amount", strcmp);
    if (jump_amount != NULL) {
        printf("Jump amount : %d\n", *jump_amount);
        if (*jump_amount <= 0) {   
            Structure* s = is_entity_touching_the_top_of_a_structure(player, game->current_scene->structures);
            printf("aled\n");
            if (s != NULL) {
                printf("tu peux sauter %s\n", s->identifier);
                Modifier* m = get_entity_modifier(player, N_JUMP);
                if (m != NULL) {
                    *jump_amount = 1+m->quantity;
                } else {
                    *jump_amount = 1;
                }
            }
        }
    }
}
void event_handler_player(Entity* player, GameData* game) {
    // SDL_Event event = game->event; // potentiellement avec switch
    // bool* is_going_down = get(player->objects, "is_going_down", strcmp);
    // bool* is_going_up = get(player->objects, "is_going_up", strcmp);
    // bool* is_going_left = get(player->objects, "is_going_left", strcmp);
    // bool* is_going_right = get(player->objects, "is_going_right", strcmp);
    if (game->keyboardState[SDL_SCANCODE_SPACE] && game->keyboardState[SDL_SCANCODE_RIGHT]) {
        printf("dash\n");
        player->x_velocity += 100;
    } else if (game->keyboardState[SDL_SCANCODE_SPACE] && game->keyboardState[SDL_SCANCODE_LEFT]) {
        player->x_velocity += -100;
    }   
    
    
    int* jump_amount = get(player->objects, "jump_amount", strcmp);
    if (jump_amount != NULL) {
        if (*jump_amount > 0) {
            if (game->keyboardState[SDL_SCANCODE_UP]) {
                player->y_velocity = -165; // 165 ca fait pile 32 pixels de saut (qu'on peut franchir)
                *jump_amount--;
            }
        }
    }
    // else if (game->keyboardState[SDL_SCANCODE_DOWN]) {
    //     player->y_velocity = 100;
    // }

    if (game->keyboardState[SDL_SCANCODE_LEFT]) {
        player->x_velocity = -100;
        player->sprite->orientation = SDL_FLIP_HORIZONTAL;
    } else if (game->keyboardState[SDL_SCANCODE_RIGHT]) {
        player->x_velocity = 100;
        player->sprite->orientation = SDL_FLIP_NONE;
    } else {
        player->x_velocity = 0;
    }

    if (game->keyboardState[SDL_SCANCODE_U]) {
        player->current_hp += 1;
    }

    if (game->keyboardState[SDL_SCANCODE_D]) {
        player->current_hp -= 1;
    }

    if (game->keyboardState[SDL_SCANCODE_T] && game->event.type == SDL_KEYDOWN) {
        printf("tentacula T\n");
        bool* is_tentacula = get(player->objects, "is_tentacula", strcmp);
        if (is_tentacula != NULL) {
            *is_tentacula = !(*is_tentacula);
        }
    }
}

void update_animation_player(Entity* e, float delta) {
    (void)delta;
    bool* is_tentacula = get(e->objects, "is_tentacula", strcmp);
    if (is_tentacula != NULL) {
        if (*is_tentacula) {
            printf("tentacula\n");
            e->etat = 5;
            return;
        }
    }
    
    
    if (strcmp(e->weapon->name, "basic_sword") == 0) {
        bool* is_attacking = get(e->weapon->objects, "is_attacking", strcmp);
        int* attack_duration = get(e->weapon->objects, "attack_duration", strcmp);
        if (is_attacking != NULL) {
            // printf("%d, %d\n", *is_attacking, *attack_duration);
            if (*is_attacking) {
                if (attack_duration != NULL) {
                    if (*attack_duration > 0) {
                        e->etat = 2;
                        return;
                    } 
                }
            }
        }
    }
    if (e->current_hp <= 0){
        e->etat = 4;
        e->damage_delay = -1;
        return;
    }
    
    if (e->x_velocity != 0){
        e->etat = 1;
        return;
    }
        
    e->etat = 0;
    return;
}

Entity* init_player(GameData* game, int x, int y) {
    int* nbs = malloc(6*sizeof(int));
    nbs[0] = 7;
    nbs[1] = 8;
    nbs[2] = 4;
    nbs[3] = 1;
    nbs[4] = 9;
    nbs[5] = 6;
    int* lock = malloc(6*sizeof(int));
    lock[0] = 0;
    lock[1] = 0;
    lock[2] = 4;
    lock[3] = 0;
    lock[5] = 6;
    
    SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_lombric"); // to change

    Entity* player = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_player, event_handler_player, update_animation_player, 6, true);

    // WeaponInitFunc* arbalete = get(game->weapons, "arbalete", strcmp);
    WeaponInitFunc* basic_sword = get(game->weapons, "basic_sword", strcmp);
    if (basic_sword == NULL) {
        printf("Error: weapon not found\n");
        return NULL;
    }
    player->weapon = (*basic_sword)(game);

    bool* is_tentacula = malloc(sizeof(bool));
    *is_tentacula = false;
    insert(player->objects, "is_tentacula", is_tentacula, free);

    int* jump_amount = malloc(sizeof(int));
    *jump_amount = 1;
    insert(player->objects, "jump_amount", jump_amount, free);

    return player;
}

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

    update_entity_movement(game, player, delta_t, true);
}
void event_handler_player(Entity* player, GameData* game) {
    SDL_Event event = game->event;
    // bool* is_going_down = get(player->objects, "is_going_down", strcmp);
    // bool* is_going_up = get(player->objects, "is_going_up", strcmp);
    // bool* is_going_left = get(player->objects, "is_going_left", strcmp);
    // bool* is_going_right = get(player->objects, "is_going_right", strcmp);
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // *is_going_up = true;
                    player->y_velocity = -100;
                    player->etat = 0;
                    break;
                case SDLK_DOWN:
                    // *is_going_down = true;
                    player->y_velocity = 100;
                    player->etat = 0;
                    break;
                case SDLK_LEFT:
                    // *is_going_left = true;
                    player->x_velocity = -100;
                    player->sprite->orientation = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_RIGHT:
                    player->x_velocity = 100;    
                    player->sprite->orientation = SDL_FLIP_NONE;
                    // *is_going_right = true;
                    break;
                case SDLK_u:
                    player->current_hp += 1;
                    break;
                case SDLK_d:
                    player->current_hp -= 1;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // *is_going_up = true;
                    player->y_velocity = 0;
                    break;
                case SDLK_DOWN:
                    // *is_going_down = true;
                    player->y_velocity = 0;
                    break;
                case SDLK_LEFT:
                    // *is_going_left = true;
                    player->x_velocity = 0;
                    break;
                case SDLK_RIGHT:
                    player->x_velocity = 0;    
                    // *is_going_right = true;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void update_animation_player(Entity* e, float delta) {
    if (e->x_velocity != 0){
        e->etat = 1;
    }
    else{
        e->etat = 0;
    }

    return;
}

Entity* init_player(GameData* game, int x, int y) {
    int* nbs = malloc(2*sizeof(int));
    nbs[0] = 7;
    nbs[1] = 8;
    int* lock = malloc(2*sizeof(int));
    lock[0] = 0;
    lock[1] = 1;
    
    SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_lombric"); // to change

    Entity* player = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_player, event_handler_player, update_animation_player, 6);

    WeaponInitFunc* arbalete = get(game->weapons, "arbalete", strcmp);
    if (arbalete == NULL) {
        printf("Error: weapon not found\n");
        return NULL;
    }
    player->weapon = (*arbalete)(game);

    return player;
}
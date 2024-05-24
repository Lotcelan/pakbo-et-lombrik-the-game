#include "cafet_ping_pong_beginning.h"

void update_cafet_ping_pong_beginning(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.x > game->width_amount * CELL_WIDTH) {
        change_scene(game, "ping_pong_1_4");
        return;
    }
    
    if (game->player->y_position > game->height_amount * CELL_HEIGHT) {
        change_scene(game, "cave_beginning_1_0");
        return;
    }

    if (game->player->collision_box->zone.x < 0) {
        change_scene(game, "cafet_second_counter_end_15_3");
        return;
    }

    return;
}

void event_handler_cafet_ping_pong_beginning(GameData* game) {
    switch (game->event.type) {
        case SDL_KEYDOWN:
            switch (game->event.key.keysym.sym) {
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            game->state = CLOSING;
            break;
        default:
            break;
    }
    return;
}

void populate_cafet_ping_pong_beginning(GameData* game) {
    push_background_structures(game);
}

Scene* init_cafet_ping_pong_beginning(GameData* game) {
    Scene* scene = init_scene(game, "cafet_ping_pong_beginning");

    scene->update = update_cafet_ping_pong_beginning;
    scene->event_handler = event_handler_cafet_ping_pong_beginning;
    scene->populate = populate_cafet_ping_pong_beginning;


    return scene;
}

#include "hub.h"

void update_hub(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.y < 0) {
        // change_scene(game, "main_menu_-1_-1");
        change_scene(game, "cafet_beginning_2_4");
        return;
    }
    else if (game->player->collision_box->zone.x < 0) {
        change_scene(game, "intro5_15_6");
        return;
    }
    return;
}

void event_handler_hub(GameData* game) {
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

void populate_hub(GameData* game) {
    push_background_structures(game);
}

Scene* init_hub(GameData* game) {
    Scene* scene = init_scene(game, "hub");

    scene->update = update_hub;
    scene->event_handler = event_handler_hub;
    scene->populate = populate_hub;


    return scene;
}

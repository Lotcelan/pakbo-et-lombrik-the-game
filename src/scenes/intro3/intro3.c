#include "intro3.h"

void update_intro3(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.x > 256) {
        change_scene(game, "main_menu_-1_-1");
        return;
    }
    else if (game->player->collision_box->zone.x < 0) {
        change_scene(game, "intro2_15_4");
        return;
    }
    return;
}

void event_handler_intro3(GameData* game) {
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

void populate_intro3(GameData* game) {
    push_background_structures(game);
}

Scene* init_intro3(GameData* game) {
    Scene* scene = init_scene(game, "intro3");

    scene->update = update_intro3;
    scene->event_handler = event_handler_intro3;
    scene->populate = populate_intro3;


    return scene;
}
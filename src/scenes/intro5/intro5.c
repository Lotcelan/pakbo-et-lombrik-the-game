#include "intro5.h"

void update_intro5(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.x > 256) {
        change_scene(game, "hub_0_6");
        return;
    }
    else if (game->player->collision_box->zone.x < 0) {
        change_scene(game, "intro4_15_6");
        return;
    }
    return;
}

void event_handler_intro5(GameData* game) {
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

void populate_intro5(GameData* game) {
    push_background_structures(game);
}

Scene* init_intro5(GameData* game) {
    Scene* scene = init_scene(game, "intro5");

    scene->update = update_intro5;
    scene->event_handler = event_handler_intro5;
    scene->populate = populate_intro5;


    return scene;
}

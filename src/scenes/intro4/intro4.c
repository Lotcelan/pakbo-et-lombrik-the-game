#include "intro4.h"

void update_intro4(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.x > 256) {
        change_scene(game, "intro5_0_6");
        return;
    }
    else if (game->player->collision_box->zone.x < 0) {
        change_scene(game, "intro3_15_6");
        return;
    }
    return;
}

void event_handler_intro4(GameData* game) {
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

void populate_intro4(GameData* game) {
    push_background_structures(game);
}

Scene* init_intro4(GameData* game) {
    Scene* scene = init_scene(game, "intro4");

    scene->update = update_intro4;
    scene->event_handler = event_handler_intro4;
    scene->populate = populate_intro4;


    return scene;
}

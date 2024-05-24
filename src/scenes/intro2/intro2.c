#include "intro2.h"

void update_intro2(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.x > 256) {
        change_scene(game, "intro3_0_4");
        return;
    }
    else if (game->player->collision_box->zone.y < -10) {
        change_scene(game, "intro2bis_7_7");
        return;
    }
    else if (game->player->collision_box->zone.x < 0) {
        change_scene(game, "intro1_15_2");
        return;
    }
    return;
}

void event_handler_intro2(GameData* game) {
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

void populate_intro2(GameData* game) {
    push_background_structures(game);
}

Scene* init_intro2(GameData* game) {
    Scene* scene = init_scene(game, "intro2");

    scene->update = update_intro2;
    scene->event_handler = event_handler_intro2;
    scene->populate = populate_intro2;


    return scene;
}

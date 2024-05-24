#include "intro2bis.h"

void update_intro2bis(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.y > 128) {
        change_scene(game, "intro2_8_0");
        return;
    }
    return;
}

void event_handler_intro2bis(GameData* game) {
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

void populate_intro2bis(GameData* game) {
    push_background_structures(game);
    game->player->y_velocity = -165;
}

Scene* init_intro2bis(GameData* game) {
    Scene* scene = init_scene(game, "intro2bis");

    scene->update = update_intro2bis;
    scene->event_handler = event_handler_intro2bis;
    scene->populate = populate_intro2bis;


    return scene;
}

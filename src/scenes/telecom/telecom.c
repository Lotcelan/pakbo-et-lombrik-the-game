#include "telecom.h"

void update_telecom(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.y > 130) {
        change_scene(game, "main_menu_-1_-1");
        return;
    }
    
    return;
}

void event_handler_telecom(GameData* game) {
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

void populate_telecom(GameData* game) {
    push_background_structures(game);
}

Scene* init_telecom(GameData* game) {
    Scene* scene = init_scene(game, "telecom");

    scene->update = update_telecom;
    scene->event_handler = event_handler_telecom;
    scene->populate = populate_telecom;


    return scene;
}

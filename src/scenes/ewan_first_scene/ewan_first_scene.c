#include "ewan_first_scene.h"

void update_ewan_first_scene(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.x > game->width_amount * CELL_WIDTH) {
        change_scene(game, "cafet_crossing_counters_1_4");
        return;
    }
    
    return;
}

void event_handler_ewan_first_scene(GameData* game) {
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

void populate_ewan_first_scene(GameData* game) {
    push_background_structures(game);
}

Scene* init_ewan_first_scene(GameData* game) {
    Scene* scene = init_scene(game, "ewan_first_scene");

    scene->update = update_ewan_first_scene;
    scene->event_handler = event_handler_ewan_first_scene;
    scene->populate = populate_ewan_first_scene;


    return scene;
}

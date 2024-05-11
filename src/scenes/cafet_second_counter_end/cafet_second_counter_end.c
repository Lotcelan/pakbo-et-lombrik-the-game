#include "cafet_second_counter_end.h"

void update_cafet_second_counter_end(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    if (game->player->collision_box->zone.x > game->width_amount * CELL_WIDTH) {
        change_scene(game, "cafet_crossing_counters_1_4");
        return;
    }
    
    return;
}

void event_handler_cafet_second_counter_end(GameData* game) {
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

void populate_cafet_second_counter_end(GameData* game) {
    push_background_structures(game);
}

Scene* init_cafet_second_counter_end(GameData* game) {
    Scene* scene = init_scene(game, "cafet_second_counter_end");

    scene->update = update_cafet_second_counter_end;
    scene->event_handler = event_handler_cafet_second_counter_end;
    scene->populate = populate_cafet_second_counter_end;


    return scene;
}

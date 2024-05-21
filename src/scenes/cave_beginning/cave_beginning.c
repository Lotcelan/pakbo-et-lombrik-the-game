#include "cave_beginning.h"

void update_cave_beginning(GameData* game) {
    //if (game->player->collision_box->zone.x > game->width_amount * CELL_WIDTH) {
    //    change_scene(game, "cafet_crossing_counters_1_4");
    //    return;
    //}
    
    if (game->player->collision_box->zone.y > game->height_amount * CELL_WIDTH) {
        change_scene(game, "cave_beginning_1_0");
        return;
    }
 
    return;
}

void event_handler_cave_beginning(GameData* game) {
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

void populate_cave_beginning(GameData* game) {
    push_background_structures(game);
}

Scene* init_cave_beginning(GameData* game) {
    Scene* scene = init_scene(game, "cave_beginning");

    scene->update = update_cave_beginning;
    scene->event_handler = event_handler_cave_beginning;
    scene->populate = populate_cave_beginning;


    return scene;
}

#include "cafet_second_counter_beginning.h"

void update_cafet_second_counter_beginning(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);

    
    
    return;
}

void event_handler_cafet_second_counter_beginning(GameData* game) {
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

void populate_cafet_second_counter_beginning(GameData* game) {
    push_background_structures(game);
}

Scene* init_cafet_second_counter_beginning(GameData* game) {
    Scene* scene = init_scene(game, "cafet_second_counter_beginning");

    scene->update = update_cafet_second_counter_beginning;
    scene->event_handler = event_handler_cafet_second_counter_beginning;
    scene->populate = populate_cafet_second_counter_beginning;


    return scene;
}

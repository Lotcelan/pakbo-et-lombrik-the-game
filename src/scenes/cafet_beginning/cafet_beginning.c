#include "cafet_beginning.h"

void update_cafet_beginning(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);

    return;
}

void event_handler_cafet_beginning(GameData* game) {
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

void populate_cafet_beginning(GameData* game) {
    push_background_structures(game);

    // for (int i = 0; i < 3; i++) add_modifier_to_entity(game, game->player, N_JUMP, 1, -1);
    // for (int i = 0; i < 15; i++) add_modifier_to_entity(game, game->player, POISON_EFFECT, 1, 5000);

    // spawn_modifier_in_scene(game, game->current_scene, create_modifier(N_JUMP, 1, -1), 8, 4);
}

Scene* init_cafet_beginning(GameData* game) {
    Scene* scene = init_scene(game, "cafet_beginning");

    scene->update = update_cafet_beginning;
    scene->event_handler = event_handler_cafet_beginning;
    scene->populate = populate_cafet_beginning;


    return scene;
}

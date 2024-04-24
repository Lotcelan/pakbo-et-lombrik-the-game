#include "hub_level.h"

void update_hub_level(GameData* game) {
    (void)game;
    return;
}

void event_handler_hub_level(GameData* game) {
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

void populate_hub_level(GameData* game) {
    push_background_structures(game);
    change_entity_coordinates(game->player, 50, 10);
}

// void test(Entity* e, float delta){
//     return;
// }

Scene* init_hub_level(GameData* game) {
    Scene* scene = init_scene(game, "hub_level");

    scene->update = update_hub_level;
    scene->event_handler = event_handler_hub_level;
    scene->populate = populate_hub_level;


    return scene;
}

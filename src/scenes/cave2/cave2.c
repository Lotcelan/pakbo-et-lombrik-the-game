#include "cave2.h"

void update_cave2(GameData* game) {
    if (game->player->y_position > game->height_amount * CELL_HEIGHT) {
        game->player->current_hp = -1;
        return;
    }

    return;
}

void event_handler_cave2(GameData* game) {
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

void populate_cave2(GameData* game) {
    push_background_structures(game);   
    for (int i = 0; i < 3; i++) add_modifier_to_entity(game, game->player, N_JUMP, 1, -1);

}

Scene* init_cave2(GameData* game) {
    Scene* scene = init_scene(game, "cave2");

    scene->update = update_cave2;
    scene->event_handler = event_handler_cave2;
    scene->populate = populate_cave2;


    return scene;
}

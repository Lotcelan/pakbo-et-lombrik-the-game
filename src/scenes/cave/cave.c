#include "cave.h"

void update_cave(GameData* game) {
    if (game->player->collision_box->zone.y > game->height_amount * CELL_HEIGHT) {
        game->player->current_hp = -1;
        return;
    }

    return;
}

void event_handler_cave(GameData* game) {
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

void populate_cave(GameData* game) {
    push_background_structures(game);   
    for (int i = 0; i < 3; i++) add_modifier_to_entity(game, game->player, N_JUMP, 1, -1);

}

Scene* init_cave(GameData* game) {
    Scene* scene = init_scene(game, "cave");

    scene->update = update_cave;
    scene->event_handler = event_handler_cave;
    scene->populate = populate_cave;


    return scene;
}

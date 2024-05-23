#include "first_boss_room.h"

void update_first_boss_room(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    
    Structure* moving_platform_left = get(game->current_scene->objects, "moving_platform_left", strcmp);
    Structure* moving_platform_right = get(game->current_scene->objects, "moving_platform_right", strcmp);

    if (moving_platform_left == NULL || moving_platform_right == NULL) {
        return;
    }

    if (moving_platform_left->position.x < 0) {
        change_structure_coordinates(game, moving_platform_left, moving_platform_left->position.x + 3, moving_platform_left->position.y);
    } else {
        change_structure_coordinates(game, moving_platform_left, 0, moving_platform_left->position.y);   
    }
    if (moving_platform_right->position.x > game->width_amount * CELL_WIDTH / 2) {
        change_structure_coordinates(game, moving_platform_right, moving_platform_right->position.x - 3, moving_platform_right->position.y); 
    } else {
        change_structure_coordinates(game, moving_platform_right, game->width_amount * CELL_WIDTH / 2, moving_platform_right->position.y); 
    }

    return;
}

void event_handler_first_boss_room(GameData* game) {
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

void populate_first_boss_room(GameData* game) {
    push_background_structures(game);
    if (game->player) game->player->y_velocity = -250;

    Structure* moving_platform_left = init_structure(game, "moving_platform_left", "src_assets_cafet_tablePingPongHalf", -8, 6, 0, "none");
    insert(game->current_scene->objects, "moving_platform_left", moving_platform_left,NULL);
    game->current_scene->structures = append_first(moving_platform_left, game->current_scene->structures);
    push_render_stack_structure(game, moving_platform_left, false);

    Structure* moving_platform_right = init_structure(game, "moving_platform_right", "src_assets_cafet_tablePingPongHalf", 16, 6, 0, "none");
    insert(game->current_scene->objects, "moving_platform_right", moving_platform_right,NULL);
    game->current_scene->structures = append_first(moving_platform_right, game->current_scene->structures);
    push_render_stack_structure(game, moving_platform_right, false);

}

Scene* init_first_boss_room(GameData* game) {
    Scene* scene = init_scene(game, "first_boss_room");

    scene->update = update_first_boss_room;
    scene->event_handler = event_handler_first_boss_room;
    scene->populate = populate_first_boss_room;


    return scene;
}

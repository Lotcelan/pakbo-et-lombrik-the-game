#include "cafet_crossing_counters.h"

void update_cafet_crossing_counters(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);

    Structure* moving_platform = get(game->current_scene->objects, "moving_platform", strcmp);
    change_structure_coordinates(game, moving_platform, CELL_WIDTH * 8 + (CELL_WIDTH * 5 * sin(2*3.14*SDL_GetTicks()/1000/8)), moving_platform->position.y);

    if (game->player->collision_box->zone.x > game->width_amount * CELL_WIDTH) {
        change_scene(game, "cafet_second_counter_beginning_3_4");
        return;
    }

    if (game->player->collision_box->zone.y > game->height_amount * CELL_WIDTH) {
        change_scene(game, "cave_beginning_1_0");
        return;
    }
    
    return;
}

void event_handler_cafet_crossing_counters(GameData* game) {
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

void populate_cafet_crossing_counters(GameData* game) {
    push_background_structures(game);

    Structure* moving_platform = init_structure(game, "moving_platform", "src_assets_cafet_comptoireMiddle", 2, 5, 8, "none");
    insert(game->current_scene->objects, "moving_platform", moving_platform,NULL);
    
    game->current_scene->structures = append_first(moving_platform, game->current_scene->structures);
    push_render_stack_structure(game, moving_platform, false);
}

Scene* init_cafet_crossing_counters(GameData* game) {
    Scene* scene = init_scene(game, "cafet_crossing_counters");

    scene->update = update_cafet_crossing_counters;
    scene->event_handler = event_handler_cafet_crossing_counters;
    scene->populate = populate_cafet_crossing_counters;


    return scene;
}

#include "cafet_second_counter_beginning.h"

void update_cafet_second_counter_beginning(GameData* game) {
    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);

    int remaining_flies = 0;
    
    Entity* mouche1 = (Entity*)get(game->current_scene->objects, "mouche1", strcmp);
    Entity* mouche3 = (Entity*)get(game->current_scene->objects, "mouche3", strcmp);

    List* current = game->current_scene->entities;
    while (current != NULL) {
        Entity* e = (Entity*)(current->value);
        if (e == mouche1 || e == mouche3) {
            remaining_flies++;
        }
        current = current->next;
    }

    if (remaining_flies > 0) {
        Structure* left_fork = init_structure(game, "left_fork", "src_assets_cafet_giganticFork", 0, 0, 0, "none");
        Structure* right_fork = init_structure(game, "right_fork", "src_assets_cafet_giganticFork", 14, 0, 0, "none");

        push_render_stack_structure(game, left_fork, true);
        push_render_stack_structure(game, right_fork, true);
        
        if (game->player->x_position <= 32) {
            game->player->x_velocity = (- game->player->x_velocity > 0) ? - game->player->x_velocity : 0;
        }
        if (game->player->x_position >= game->width_amount * CELL_WIDTH - 48) {
            game->player->x_velocity = (- game->player->x_velocity < 0) ? - game->player->x_velocity : 0;
        }

        char text[50];
        sprintf(text, "Il reste %d mouches !", remaining_flies);
        
        Text* t = init_text(game, text, (SDL_Color){255, 0, 0, 255}, CELL_WIDTH * 5, CELL_HEIGHT, (TTF_Font*)get(game->fonts, "suifak_small", strcmp));
        push_render_stack_text(game, t, true);
    }

    if (game->player->x_position > game->width_amount * CELL_WIDTH) {
        change_scene(game, "cafet_second_counter_end_2_4");
    }

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

    EntityInitFunc* mouche = get(game->entities, "la_mouche", strcmp);

    Entity* mouche1 = (*mouche)(game, CELL_WIDTH * 10,CELL_HEIGHT *  1);
    Entity* mouche3 = (*mouche)(game, CELL_WIDTH * 12,CELL_HEIGHT *  3);
    insert(game->current_scene->objects, "mouche1", mouche1, NULL); // le systeme d'entité se gère du free
    insert(game->current_scene->objects, "mouche3", mouche3, NULL);
    game->current_scene->entities = append_first(mouche1, game->current_scene->entities);
    game->current_scene->entities = append_first(mouche3, game->current_scene->entities);

    

    Dialog* warning_dialog = get_dialog_from_json("second_counter_fork_blocking");
    game->current_dialog = warning_dialog;
    
}

Scene* init_cafet_second_counter_beginning(GameData* game) {
    Scene* scene = init_scene(game, "cafet_second_counter_beginning");

    scene->update = update_cafet_second_counter_beginning;
    scene->event_handler = event_handler_cafet_second_counter_beginning;
    scene->populate = populate_cafet_second_counter_beginning;

    

    return scene;
}

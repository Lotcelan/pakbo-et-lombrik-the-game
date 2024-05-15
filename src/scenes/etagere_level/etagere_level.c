#include "etagere_level.h"

void update_etagere_level(GameData* game) {
    SDL_Point* toolbox_position = get(game->current_scene->objects, "toolbox_position", strcmp);

    Texture* toolbox = init_texture_from_memory(game, "src_assets_toolbox", toolbox_position->x, toolbox_position->y);
    push_render_stack_texture(game, toolbox, true);  // volontaire que ce soit true ici
    return;
}

void event_handler_etagere_level(GameData* game) {
    ScreenShake* screen_shake;
    SDL_Point* toolbox_position;
    Dialog* dialog;
    switch (game->event.type) {
        case SDL_KEYDOWN:
            switch (game->event.key.keysym.sym) {
                // case SDLK_ESCAPE:
                //     game->running = 0;
                //     break;
                case SDLK_h:
                    screen_shake = init_screen_shake(10, 100);
                    printf("Screen shake: %p\n", (void*)&screen_shake);
                    game->current_scene->screen_shake = screen_shake;
                    break;
                case SDLK_r:
                    toolbox_position = get(game->current_scene->objects, "toolbox_position", strcmp);
                    toolbox_position->x = (rand() % game->width_amount) * 16;
                    toolbox_position->y = (rand() % game->height_amount) * 16;
                    break;
                case SDLK_t:
                    dialog = get_dialog_from_json("test");
                    game->current_dialog = dialog;
                    break;
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

void populate_etagere_level(GameData* game) {
    push_background_structures(game);

    SDL_Point* toolbox_position = get(game->current_scene->objects, "toolbox_position", strcmp);

    Texture* toolbox = init_texture_from_memory(game, "src_assets_toolbox", toolbox_position->x, toolbox_position->y);
    push_render_stack_texture(game, toolbox, true);  // volontaire que ce soit true ici


    // On s'occupe de ça dans populate
    change_entity_coordinates(game->player, 50, 10);
}

// void test(Entity* e, float delta){
//     return;
// }

Scene* init_etagere_level(GameData* game) {
    Scene* scene = init_scene(game, "etagere_level");


    scene->update = update_etagere_level;
    scene->event_handler = event_handler_etagere_level;
    scene->populate = populate_etagere_level;

    SDL_Point* toolbox_position = malloc(sizeof(SDL_Point));
    toolbox_position->x = 0;
    toolbox_position->y = 0;



    insert(scene->objects, "toolbox_position", toolbox_position, free);

    return scene;
}

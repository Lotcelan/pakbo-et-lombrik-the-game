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
    game->player->x_position = 50;
    game->player->y_position = 10;
    update_entity_boxes(game->player);
}

// void test(Entity* e, float delta){
//     return;
// }

Scene* init_etagere_level(GameData* game) {
    Scene* scene = init_scene(game, "etagere_level");

    // test pour l'affichage des entités
    // début tests Sacha
    // int* nbs = malloc(sizeof(int));
    // nbs[0] = 8;
    // int* lock = malloc(sizeof(int));
    // lock[0] = 0;
    // SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_lombric_walk");
    // // Sprite* lb_sprite = init_sprite(12, spritesheet, 16, 16, nbs, lock);
    // Entity* lombric = init_entity(15, 10, 15, spritesheet, 16, 16, nbs, lock);
    // lombric->update_animation = test;
    // int* t = lombric->sprite->frames[0]->value;
    // int* cf = lombric->sprite->currentFrame->next->value;
    // printf("\n\n%d, %d\nnext frame : %d, %d\n\n", t[0], t[1], cf[0], cf[1]);
    // scene->entities = append_first(lombric, scene->entities);
    // fin tests Sacha

    scene->update = update_etagere_level;
    scene->event_handler = event_handler_etagere_level;
    scene->populate = populate_etagere_level;

    SDL_Point* toolbox_position = malloc(sizeof(SDL_Point));
    toolbox_position->x = 0;
    toolbox_position->y = 0;



    insert(scene->objects, "toolbox_position", toolbox_position);

    return scene;
}

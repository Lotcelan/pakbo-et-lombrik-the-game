#include "simple_arena.h"

void update_simple_arena(GameData* game) {
    (void)game;

    Structure* moving_platform = get(game->current_scene->objects, "moving_platform", strcmp);
    change_structure_coordinates(game, moving_platform, CELL_WIDTH * 6 + (50 * sin(2*3.14*SDL_GetTicks()/1000/4)), moving_platform->position.y);

    // printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);
    return;
}

void event_handler_simple_arena(GameData* game) {
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

void populate_simple_arena(GameData* game) {
    push_background_structures(game);
    // change_entity_coordinates(game->player, 50, 10);

    // for (int i = 0; i < 1; i++) {
    //     EntityInitFunc* duck = get(game->entities, "duck_green", strcmp);
    //     Entity* e = (*duck)(game, (rand() %  16) * CELL_WIDTH, (rand() % 4) * CELL_HEIGHT);
    //     game->current_scene->entities = append_first(e, game->current_scene->entities);
    // }

    Structure* moving_platform = init_structure(game, "moving_platform", "src_assets_structures_sol", 8, 4, 8, "none");
    insert(game->current_scene->objects, "moving_platform", moving_platform,NULL);
    
    game->current_scene->structures = append_first(moving_platform, game->current_scene->structures);
    push_render_stack_structure(game, moving_platform, false);
}

// void test(Entity* e, float delta){
//     return;
// }

Scene* init_simple_arena(GameData* game) {
    Scene* scene = init_scene(game, "simple_arena");

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

    scene->update = update_simple_arena;
    scene->event_handler = event_handler_simple_arena;
    scene->populate = populate_simple_arena;


    return scene;
}

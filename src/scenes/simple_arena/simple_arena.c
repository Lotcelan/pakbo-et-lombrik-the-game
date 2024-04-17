#include "simple_arena.h"

void update_simple_arena(GameData* game) {

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
    change_entity_coordinates(game->player, 50, 10);
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

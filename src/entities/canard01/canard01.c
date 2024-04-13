#include <SDL2/SDL.h>
#include "canard01.h"


void update_canard01(GameData* game, Entity* canard01, float delta_t) {
    if (canard01 == NULL) {
        return;
    }

    follow_player(game, canard01);
    update_entity_movement(game, canard01, delta_t);
    return;
}
void event_handler_canard01(Entity* canard01, GameData* game) {
    return;
}

void update_animation_canard01(Entity* e, float delta) {
    return;
}

Entity* init_canard01(GameData* game, int x, int y) {
    int* nbs = malloc(sizeof(int));
    nbs[0] = 8;
    int* lock = malloc(sizeof(int));
    lock[0] = 0;
    
    SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_random_lombric_walk"); // to change

    Entity* canard01 = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_canard01, event_handler_canard01, update_animation_canard01);

    return canard01;
}

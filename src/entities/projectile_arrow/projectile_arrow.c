#include <SDL2/SDL.h>
#include "projectile_arrow.h"


void update_projectile_arrow(GameData* game, Entity* projectile_arrow, float delta_t) {
    if (projectile_arrow == NULL) {
        return;
    }

    // follow_player(game, projectile_arrow);
    update_entity_movement(game, projectile_arrow, delta_t);
    // if (are_colliding(projectile_arrow->hit_box, game->player->hurt_box)) {
    //     damage_entity(game, game->player, 1, true);
    // }
    
    return;
}
void event_handler_projectile_arrow(Entity* projectile_arrow, GameData* game) {
    return;
}

void update_animation_projectile_arrow(Entity* e, float delta) {
    return;
}

Entity* init_projectile_arrow(GameData* game, int x, int y) {
    int* nbs = malloc(sizeof(int));
    nbs[0] = 1;
    int* lock = malloc(sizeof(int));
    lock[0] = 0;
    
    SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_projectile_arrow"); // to change

    Entity* projectile_arrow = init_entity(x, y, 1, spritesheet, 16, 16, nbs, lock, update_projectile_arrow, event_handler_projectile_arrow, update_animation_projectile_arrow, -1);

    return projectile_arrow;
}

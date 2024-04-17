#include <SDL2/SDL.h>
#include "blue_canard_boss.h"


void update_blue_canard_boss(GameData* game, Entity* blue_canard_boss, float delta_t) {
    if (blue_canard_boss == NULL) {
        return;
    }

    follow_player(game, blue_canard_boss, 50, 50);
    update_entity_movement(game, blue_canard_boss, delta_t, true);
    if (are_colliding(blue_canard_boss->hit_box, game->player->hurt_box)) {
        damage_entity(game, game->player, 2, 1000, -1);
    }



    return;
}
void event_handler_blue_canard_boss(Entity* blue_canard_boss, GameData* game) {
    return;
}

void update_animation_blue_canard_boss(Entity* e, float delta) {
    return;
}

Entity* init_blue_canard_boss(GameData* game, int x, int y) {
    int* nbs = malloc(sizeof(int));
    nbs[0] = 15;
    int* lock = malloc(sizeof(int));
    lock[0] = 0;
    
    SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_blue_canard_boss"); // to change

    Entity* blue_canard_boss = init_entity(x, y, 14, spritesheet, 32, 32, nbs, lock, update_blue_canard_boss, event_handler_blue_canard_boss, update_animation_blue_canard_boss, 12, true);

    WeaponInitFunc* weapon_init = get(game->weapons, "blue_duck_boss_laser", strcmp);
    if (weapon_init == NULL) {
        printf("Error: weapon not found\n");
        return NULL;
    }
    blue_canard_boss->weapon = (*weapon_init)(game);

    return blue_canard_boss;
}

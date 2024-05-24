#include "canard01.h"

#include <SDL2/SDL.h>

void update_canard01(GameData* game, Entity* canard01, float delta_t) {
	if (canard01 == NULL) {
		return;
	}

	follow_player(game, canard01, 50, 50);
	update_entity_movement(game, canard01, delta_t, true);
	if (are_colliding(canard01->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, 1, 1000, -1, false, canard01);
	}
	if (canard01->x_position < game->player->x_position){
		canard01->sprite->orientation = SDL_FLIP_HORIZONTAL;
	}
	else{
		canard01->sprite->orientation = SDL_FLIP_NONE;
	}
	return;
}
void event_handler_canard01(Entity* canard01, GameData* game) {
	(void)canard01;
	(void)game;
	return;
}

void update_animation_canard01(Entity* e, float delta) {
	(void)e;
	(void)delta;
	return;
}

Entity* init_canard01(GameData* game, int x, int y) {
	int* nbs = malloc(sizeof(int));
	nbs[0] = 3;
	int* lock = malloc(sizeof(int));
	lock[0] = 0;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_duck_purple");  // to change

	Entity* canard01 = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_canard01, event_handler_canard01, update_animation_canard01, 6, true);

	return canard01;
}

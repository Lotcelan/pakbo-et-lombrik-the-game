#include "sandwich.h"

// SECTION ENTITE
void update_sandwich(GameData* game, Entity* sandwich, float delta_t) {
	(void) delta_t;
	if (sandwich == NULL) {
		return;
	}

	if (sandwich->x_position > game->player->x_position){
		sandwich->sprite->orientation = SDL_FLIP_NONE;
	}
	else{
		sandwich->sprite->orientation = SDL_FLIP_HORIZONTAL;
	}

	Box* interact_box = init_rect_box_from_entity(game, sandwich);
	// pour l'instant on suppose
	interact_box->zone.x = sandwich->x_position - 10;
	interact_box->zone.y = sandwich->y_position - 10;
	interact_box->zone.w = sandwich->collision_box->zone.w + 10;
	interact_box->zone.h = sandwich->collision_box->zone.h + 10;

	if (are_colliding(interact_box, game->player->collision_box)) {
		game->player->current_hp += 2;
		if (game->player->current_hp > game->player->max_hp){
			game->player->current_hp = game->player->max_hp;
		}
		sandwich->x_position = -100;
	}
	free(interact_box);
}
void event_handler_sandwich(Entity* sandwich, GameData* game) {
	return;
}

void update_animation_sandwich(Entity* e, float delta) {
    (void)delta;
    (void)e;
	return;
}

Entity* init_sandwich(GameData* game, int x, int y) {
	int* nbs = malloc(sizeof(int));
	nbs[0] = 10;
	int* lock = malloc(sizeof(int));
	lock[0] = 0;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_sandwich");  // to change

	Entity* sandwich = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_sandwich, event_handler_sandwich, update_animation_sandwich, 9999, false);


	return sandwich;
}

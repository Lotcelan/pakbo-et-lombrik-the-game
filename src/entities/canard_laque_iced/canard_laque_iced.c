#include "canard_laque_iced.h"

#include <SDL2/SDL.h>

void update_canard_laque_iced(GameData* game, Entity* canard_laque_iced, float delta_t) {
	if (canard_laque_iced == NULL) {
		return;
	}

	int* damage = get(canard_laque_iced->objects, "damage", strcmp);
	if (damage == NULL) {
		return;
	}

	bool* is_attacking = get(canard_laque_iced->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	

	follow_player(game, canard_laque_iced, 50, 50);
	update_entity_movement(game, canard_laque_iced, delta_t, true);
	if (are_colliding(canard_laque_iced->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1, false, canard_laque_iced);
		*is_attacking = true;
	}
	else {
		*is_attacking = false;
	}

	
}
void event_handler_canard_laque_iced(Entity* canard_laque_iced, GameData* game) {
	(void)canard_laque_iced;
	(void)game;
	return;
}

void update_animation_canard_laque_iced(Entity* e, float delta) {
	(void)delta;
	bool* is_attacking = get(e->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	if (*is_attacking) {
		e->etat = 1;
	} else if (e->x_velocity == 0 && e->y_velocity == 0) {
		e->etat = 0;
	}
	else {
		e->etat = 0;
	}

	if (e->x_velocity > 0) {
		e->sprite->orientation = SDL_FLIP_HORIZONTAL;
	} else if (e->x_velocity < 0) {
		e->sprite->orientation = SDL_FLIP_NONE;
	}

	return;
}

Entity* init_canard_laque_iced(GameData* game, int x, int y) {
	int* nbs = malloc(2 * sizeof(int));
	nbs[0] = 5;	 // idle
	nbs[1] = 5;	 // walk
	
	int* lock = malloc(3 * sizeof(int));
	lock[0] = 0;
	lock[1] = 0;
	lock[2] = 3;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_ducks_fullCanardLaqueIced");	// to change

	Entity* canard_laque_iced = init_entity(x, y, 14, spritesheet, 46, 24, nbs, lock, update_canard_laque_iced, event_handler_canard_laque_iced, update_animation_canard_laque_iced, 20, true);

	int* duck_damage = malloc(sizeof(int));
	*duck_damage = 2;
	insert(canard_laque_iced->objects, "damage", duck_damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(canard_laque_iced->objects, "is_attacking", is_attacking, free);

	return canard_laque_iced;
}

#include "kiwi_iced.h"

#include <SDL2/SDL.h>

void update_kiwi_iced(GameData* game, Entity* kiwi_iced, float delta_t) {
	if (kiwi_iced == NULL) {
		return;
	}

	int* damage = get(kiwi_iced->objects, "damage", strcmp);
	if (damage == NULL) {
		return;
	}

	bool* is_attacking = get(kiwi_iced->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	

	follow_player(game, kiwi_iced, 50, 50);
	update_entity_movement(game, kiwi_iced, delta_t, true);
	if (are_colliding(kiwi_iced->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1, false, kiwi_iced);
		*is_attacking = true;
	}
	else {
		*is_attacking = false;
	}
	return;
}
void event_handler_kiwi_iced(Entity* kiwi_iced, GameData* game) {
	(void)kiwi_iced;
	(void)game;
	return;
}

void update_animation_kiwi_iced(Entity* e, float delta) {
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

Entity* init_kiwi_iced(GameData* game, int x, int y) {
	int* nbs = malloc(2 * sizeof(int));
	nbs[0] = 3;	 // walk
	nbs[1] = 3;	 // attack
	
	int* lock = malloc(3 * sizeof(int));
	lock[0] = 0;
	lock[1] = 0;
	lock[2] = 3;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_kiwis_fullKiwiIced");	// to change

	Entity* kiwi_iced = init_entity(x, y, 14, spritesheet, 20, 16, nbs, lock, update_kiwi_iced, event_handler_kiwi_iced, update_animation_kiwi_iced, 6, true);

	int* kiwi_damage = malloc(sizeof(int));
	*kiwi_damage = 1;
	insert(kiwi_iced->objects, "damage", kiwi_damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(kiwi_iced->objects, "is_attacking", is_attacking, free);

	return kiwi_iced;
}

#include "duck_purple.h"

#include <SDL2/SDL.h>

void update_duck_purple(GameData* game, Entity* duck_purple, float delta_t) {
	if (duck_purple == NULL) {
		return;
	}

	int* damage = get(duck_purple->objects, "damage", strcmp);
	if (damage == NULL) {
		return;
	}

	bool* is_attacking = get(duck_purple->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	

	follow_player(game, duck_purple, 50, 50);
	update_entity_movement(game, duck_purple, delta_t, true);
	if (are_colliding(duck_purple->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1, false, duck_purple);
		*is_attacking = true;
	}
	else {
		*is_attacking = false;
	}
	return;
}
void event_handler_duck_purple(Entity* duck_purple, GameData* game) {
	(void)duck_purple;
	(void)game;
	return;
}

void update_animation_duck_purple(Entity* e, float delta) {
	(void)delta;
	bool* is_attacking = get(e->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	if (*is_attacking) {
		e->etat = 2;
	} else if (e->x_velocity == 0 && e->y_velocity == 0) {
		e->etat = 0;
	}
	else {
		e->etat = 1;
	}

	if (e->x_velocity > 0) {
		e->sprite->orientation = SDL_FLIP_HORIZONTAL;
	} else if (e->x_velocity < 0) {
		e->sprite->orientation = SDL_FLIP_NONE;
	}

	return;
}

Entity* init_duck_purple(GameData* game, int x, int y) {
	int* nbs = malloc(3 * sizeof(int));
	nbs[0] = 2;	 // idle
	nbs[1] = 5;	 // walk
	nbs[2] = 3;	 // atack
	int* lock = malloc(3 * sizeof(int));
	lock[0] = 0;
	lock[1] = 0;
	lock[2] = 3;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_ducks_fullDuckPurple");	// to change

	Entity* duck_purple = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_duck_purple, event_handler_duck_purple, update_animation_duck_purple, 6, true);

	int* duck_damage = malloc(sizeof(int));
	*duck_damage = 1;
	insert(duck_purple->objects, "damage", duck_damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(duck_purple->objects, "is_attacking", is_attacking, free);

	return duck_purple;
}

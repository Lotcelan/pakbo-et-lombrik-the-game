#include "duck_blue.h"

#include <SDL2/SDL.h>

void update_duck_blue(GameData* game, Entity* duck_blue, float delta_t) {
	if (duck_blue == NULL) {
		return;
	}

	int* damage = get(duck_blue->objects, "damage", strcmp);
	if (damage == NULL) {
		return;
	}

	bool* is_attacking = get(duck_blue->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	

	follow_player(game, duck_blue, 50, 50);
	update_entity_movement(game, duck_blue, delta_t, true);
	if (are_colliding(duck_blue->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1);
		*is_attacking = true;
	}
	else {
		*is_attacking = false;
	}
	return;
}
void event_handler_duck_blue(Entity* duck_blue, GameData* game) {
	(void)duck_blue;
	(void)game;
	return;
}

void update_animation_duck_blue(Entity* e, float delta) {
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

	return;
}

Entity* init_duck_blue(GameData* game, int x, int y) {
	int* nbs = malloc(3 * sizeof(int));
	nbs[0] = 2;	 // idle
	nbs[1] = 5;	 // walk
	nbs[2] = 3;	 // atack
	int* lock = malloc(3 * sizeof(int));
	lock[0] = 0;
	lock[1] = 0;
	lock[2] = 3;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_ducks_fullDuckDlue");	// to change

	Entity* duck_blue = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_duck_blue, event_handler_duck_blue, update_animation_duck_blue, 6, true);

	int* duck_damage = malloc(sizeof(int));
	*duck_damage = 1;
	insert(duck_blue->objects, "damage", duck_damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(duck_blue->objects, "is_attacking", is_attacking, free);

	return duck_blue;
}

#include "fly_blue.h"

#include <SDL2/SDL.h>

void update_fly_blue(GameData* game, Entity* fly_blue, float delta_t) {
	if (fly_blue == NULL) {
		return;
	}

	int* damage = get(fly_blue->objects, "damage", strcmp);
	if (damage == NULL) {
		return;
	}

	bool* is_attacking = get(fly_blue->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	

	follow_player_using_a_star(game, fly_blue, 50, 50);
	update_entity_movement(game, fly_blue, delta_t, false);
	if (are_colliding(fly_blue->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1);
		*is_attacking = true;
	}
	else {
		*is_attacking = false;
	}

	// c'est le tank donc on fait briller une aura autour de lui
	return;
}
void event_handler_fly_blue(Entity* fly_blue, GameData* game) {
	(void)fly_blue;
	(void)game;
	return;
}

void update_animation_fly_blue(Entity* e, float delta) {
	(void)delta;
	(void)e;
	// bool* is_attacking = get(e->objects, "is_attacking", strcmp);
	// if (is_attacking == NULL) {
	// 	return;
	// }
	// if (*is_attacking) {
	// 	e->etat = 2;
	// } else if (e->x_velocity == 0 && e->y_velocity == 0) {
	// 	e->etat = 0;
	// }
	// else {
	// 	e->etat = 1;
	// }

	// if (e->x_velocity > 0) {
	// 	e->sprite->orientation = SDL_FLIP_HORIZONTAL;
	// } else if (e->x_velocity < 0) {
	// 	e->sprite->orientation = SDL_FLIP_NONE;
	// }

	return;
}

Entity* init_fly_blue(GameData* game, int x, int y) {
	int* nbs = malloc(1 * sizeof(int));
	nbs[0] = 10;	 // idle
	int* lock = malloc(1 * sizeof(int));
	lock[0] = 10;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_flyBlue");

	Entity* fly_blue = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_fly_blue, event_handler_fly_blue, update_animation_fly_blue, 9, true);

	int* fly_damage = malloc(sizeof(int));
	*fly_damage = 1;
	insert(fly_blue->objects, "damage", fly_damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(fly_blue->objects, "is_attacking", is_attacking, free);

	return fly_blue;
}

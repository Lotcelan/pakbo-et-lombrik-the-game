#include "la_mouche.h"

#include <SDL2/SDL.h>

void update_la_mouche(GameData* game, Entity* la_mouche, float delta_t) {
	if (la_mouche == NULL) {
		return;
	}

	int* damage = get(la_mouche->objects, "damage", strcmp);
	if (damage == NULL) {
		return;
	}

	bool* is_attacking = get(la_mouche->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	

	follow_player_using_a_star(game, la_mouche, 30, 30);
	update_entity_movement(game, la_mouche, delta_t, true);
	if (are_colliding(la_mouche->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1);
		*is_attacking = true;
	}
	else {
		*is_attacking = false;
	}

	// c'est le tank donc on fait briller une aura autour de lui
	int glow_freq = 50;
	Circle* aura = init_circle(la_mouche->x_position + 8, la_mouche->y_position + 8, 15, (SDL_Color){50, 50, 158, 150 + 75 * sin(2 * 3.14 * SDL_GetTicks() / 1000)});
	push_render_stack_circle(game, aura, true);
	return;
}
void event_handler_la_mouche(Entity* la_mouche, GameData* game) {
	(void)la_mouche;
	(void)game;
	return;
}

void update_animation_la_mouche(Entity* e, float delta) {
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

Entity* init_la_mouche(GameData* game, int x, int y) {
	int* nbs = malloc(3 * sizeof(int));
	nbs[0] = 2;	 // idle
	nbs[1] = 5;	 // walk
	nbs[2] = 3;	 // atack
	int* lock = malloc(3 * sizeof(int));
	lock[0] = 0;
	lock[1] = 0;
	lock[2] = 3;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_ducks_fullDuckBlue");	// to change

	Entity* la_mouche = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_la_mouche, event_handler_la_mouche, update_animation_la_mouche, 9, true);

	int* duck_damage = malloc(sizeof(int));
	*duck_damage = 1;
	insert(la_mouche->objects, "damage", duck_damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(la_mouche->objects, "is_attacking", is_attacking, free);

	return la_mouche;
}

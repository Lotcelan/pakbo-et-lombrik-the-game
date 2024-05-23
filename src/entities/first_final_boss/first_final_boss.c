#include "first_final_boss.h"

#include <SDL2/SDL.h>

void update_first_final_boss(GameData* game, Entity* first_final_boss, float delta_t) {
	if (first_final_boss == NULL) {
		return;
	}

	int* damage = get(first_final_boss->objects, "damage", strcmp);
	if (damage == NULL) {
		return;
	}

	bool* is_attacking = get(first_final_boss->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}
	

	follow_player(game, first_final_boss, 50, 50);
	update_entity_movement(game, first_final_boss, delta_t, true);
	if (are_colliding(first_final_boss->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1, false, first_final_boss);
		*is_attacking = true;
	}
	else {
		*is_attacking = false;
	}

	int* phase = get(first_final_boss->objects, "phase", strcmp);
	if (!phase) return;
	printf("*phase : %i\n", *phase);
	if (first_final_boss->current_hp <= 0) {
		bool* DO_NOT_CLEAR = get(first_final_boss->objects, "DO_NOT_CLEAR", strcmp);
		if (!DO_NOT_CLEAR) return;
		if (*DO_NOT_CLEAR) {
			*phase = *phase + 1;
			first_final_boss->current_hp = first_final_boss->max_hp;
		}
	}

	if (game->current_scene) {
		int percent = first_final_boss->current_hp * 100 / first_final_boss->max_hp; // insh max != 0
		Rectangle* max_bar = init_rectangle(CELL_WIDTH, CELL_HEIGHT, (game->width_amount - 2) * CELL_WIDTH, CELL_HEIGHT / 4, (SDL_Color){ .r = 255, .g = 20, .b = 20, .a = 255}, (SDL_Color){ .r = 255, .g = 20, .b = 20, .a = 255});
		Rectangle* current_bar = init_rectangle(CELL_WIDTH, CELL_HEIGHT, percent * (game->width_amount - 2) * CELL_WIDTH / 100, CELL_HEIGHT / 4, (SDL_Color){ .r = 20, .g = 255, .b = 20, .a = 255}, (SDL_Color){ .r = 20, .g = 255, .b = 20, .a = 255});

		push_render_stack_rect(game, max_bar, true);
		push_render_stack_rect(game, current_bar, true);
		
	}

	
}
void event_handler_first_final_boss(Entity* first_final_boss, GameData* game) {
	(void)first_final_boss;
	(void)game;
	return;
}

void update_animation_first_final_boss(Entity* e, float delta) {
	(void)delta;
	bool* is_attacking = get(e->objects, "is_attacking", strcmp);
	int* phase = get(e->objects, "phase", strcmp);
	if (!phase) return;
	if (*phase == 1) {
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

	} else {
		e->etat=0;
	}
	if (e->x_velocity > 0) {
		e->sprite->orientation = SDL_FLIP_HORIZONTAL;
	} else if (e->x_velocity < 0) {
		e->sprite->orientation = SDL_FLIP_NONE;
	}
	return;
}

Entity* init_first_final_boss(GameData* game, int x, int y) {
	int* nbs = malloc(2 * sizeof(int));
	nbs[0] = 5;	 // idle
	nbs[1] = 5;	 // walk
	
	int* lock = malloc(3 * sizeof(int));
	lock[0] = 0;
	lock[1] = 0;
	lock[2] = 3;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_ducks_fullCanardLaque");	// to change

	// Entity* first_final_boss = init_entity(x, y, 14, spritesheet, 46, 24, nbs, lock, update_first_final_boss, event_handler_first_final_boss, update_animation_first_final_boss, 40, true);
	Entity* first_final_boss = init_entity(x, y, 14, spritesheet, 46, 24, nbs, lock, update_first_final_boss, event_handler_first_final_boss, update_animation_first_final_boss, 8, true);

	int* duck_damage = malloc(sizeof(int));
	*duck_damage = 2;
	insert(first_final_boss->objects, "damage", duck_damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(first_final_boss->objects, "is_attacking", is_attacking, free);


	int* phase = malloc(sizeof(int));
	*phase = 1;
	insert(first_final_boss->objects, "phase", phase, free);
	
	bool* DO_NOT_CLEAR = malloc(sizeof(bool));
	*DO_NOT_CLEAR = true;
	insert(first_final_boss->objects, "DO_NOT_CLEAR", DO_NOT_CLEAR, free);

	return first_final_boss;
}

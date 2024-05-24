#include "cuddy.h"

// SECTION ENTITE
void update_cuddy(GameData* game, Entity* cuddy, float delta_t) {
	(void) delta_t;
	if (cuddy == NULL) {
		return;
	}

	if (cuddy->x_position > game->player->x_position){
		cuddy->sprite->orientation = SDL_FLIP_NONE;
	}
	else{
		cuddy->sprite->orientation = SDL_FLIP_HORIZONTAL;
	}

	Box* interact_box = init_rect_box_from_entity(game, cuddy);
	// pour l'instant on suppose
	interact_box->zone.x = cuddy->x_position - 10;
	interact_box->zone.y = cuddy->y_position - 10;
	interact_box->zone.w = cuddy->collision_box->zone.w + 10;
	interact_box->zone.h = cuddy->collision_box->zone.h + 10;

	// if (game->current_scene->name == "hub_level") {
	if (are_colliding(interact_box, game->player->collision_box)) {
		Text* press_text = init_text(game, "Press E", (SDL_Color){255, 255, 255, 255}, cuddy->x_position, cuddy->y_position - 20, get(game->fonts, "suifak_small", strcmp));
		push_render_stack_text(game, press_text, true);
	}
	// }

	free(interact_box);
}
void event_handler_cuddy(Entity* cuddy, GameData* game) {
	Box* interact_box = init_rect_box_from_entity(game, cuddy);
	interact_box->zone.x = cuddy->x_position - 10;
	interact_box->zone.y = cuddy->y_position - 10;
	interact_box->zone.w = cuddy->collision_box->zone.w + 10;
	interact_box->zone.h = cuddy->collision_box->zone.h + 10;

	if (game->keyboardState[SDL_SCANCODE_E]) {
		// if (game->current_scene->name == "hub_level") {
		if (are_colliding(interact_box, game->player->collision_box)) {
			Dialog* dialog = get_dialog_from_json("cuddy");
			if (dialog != NULL) {
				game->current_dialog = dialog;
			}
		}
		// }
	}
	free(interact_box);
}

void update_animation_cuddy(Entity* e, float delta) {
    (void)delta;
    (void)e;
	return;
}

Entity* init_cuddy(GameData* game, int x, int y) {
	int* nbs = malloc(sizeof(int));
	nbs[0] = 7;
	int* lock = malloc(sizeof(int));
	lock[0] = 0;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_cuddy");  // to change

	Entity* cuddy = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_cuddy, event_handler_cuddy, update_animation_cuddy, 9999, false);


	return cuddy;
}

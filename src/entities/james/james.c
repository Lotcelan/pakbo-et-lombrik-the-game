#include "james.h"

// SECTION ENTITE
void update_james(GameData* game, Entity* james, float delta_t) {
	(void) delta_t;
	if (james == NULL) {
		return;
	}

	if (james->x_position > game->player->x_position){
		james->sprite->orientation = SDL_FLIP_NONE;
	}
	else{
		james->sprite->orientation = SDL_FLIP_HORIZONTAL;
	}

	Box* interact_box = init_rect_box_from_entity(game, james);
	// pour l'instant on suppose
	interact_box->zone.x = james->x_position - 10;
	interact_box->zone.y = james->y_position - 10;
	interact_box->zone.w = james->collision_box->zone.w + 10;
	interact_box->zone.h = james->collision_box->zone.h + 10;

	// if (game->current_scene->name == "hub_level") {
	if (are_colliding(interact_box, game->player->collision_box)) {
		Text* press_text = init_text(game, "Press E", (SDL_Color){255, 255, 255, 255}, james->x_position, james->y_position - 20, get(game->fonts, "suifak_small", strcmp));
		push_render_stack_text(game, press_text, true);
	}
	// }

	free(interact_box);
}
void event_handler_james(Entity* james, GameData* game) {
	Box* interact_box = init_rect_box_from_entity(game, james);
	interact_box->zone.x = james->x_position - 10;
	interact_box->zone.y = james->y_position - 10;
	interact_box->zone.w = james->collision_box->zone.w + 10;
	interact_box->zone.h = james->collision_box->zone.h + 10;

	if (game->keyboardState[SDL_SCANCODE_E]) {
		// if (game->current_scene->name == "hub_level") {
		if (are_colliding(interact_box, game->player->collision_box)) {
			Dialog* dialog = get_dialog_from_json("james");
			if (dialog != NULL) {
				game->current_dialog = dialog;
			}
		}
		// }
	}
	free(interact_box);
}

void update_animation_james(Entity* e, float delta) {
    (void)delta;
    (void)e;
	return;
}

Entity* init_james(GameData* game, int x, int y) {
	int* nbs = malloc(sizeof(int));
	nbs[0] = 7;
	int* lock = malloc(sizeof(int));
	lock[0] = 0;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_james");  // to change

	Entity* james = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_james, event_handler_james, update_animation_james, 9999, false);


	return james;
}

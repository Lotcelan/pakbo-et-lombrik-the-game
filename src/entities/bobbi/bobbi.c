#include "bobbi.h"

// SECTION ENTITE
void update_bobbi(GameData* game, Entity* bobbi, float delta_t) {
	(void) delta_t;
	if (bobbi == NULL) {
		return;
	}

	Box* interact_box = init_rect_box_from_entity(game, bobbi);
	// pour l'instant on suppose
	interact_box->zone.x = bobbi->x_position - 10;
	interact_box->zone.y = bobbi->y_position - 10;
	interact_box->zone.w = bobbi->collision_box->zone.w + 10;
	interact_box->zone.h = bobbi->collision_box->zone.h + 10;

	// if (game->current_scene->name == "hub_level") {
	if (are_colliding(interact_box, game->player->collision_box)) {
		Text* press_text = init_text(game, "Press E", (SDL_Color){255, 255, 255, 255}, bobbi->x_position, bobbi->y_position - 20, get(game->fonts, "suifak_small", strcmp));
		push_render_stack_text(game, press_text, true);
	}
	// }

	free(interact_box);
}
void event_handler_bobbi(Entity* bobbi, GameData* game) {
	Box* interact_box = init_rect_box_from_entity(game, bobbi);
	interact_box->zone.x = bobbi->x_position - 10;
	interact_box->zone.y = bobbi->y_position - 10;
	interact_box->zone.w = bobbi->collision_box->zone.w + 10;
	interact_box->zone.h = bobbi->collision_box->zone.h + 10;

	if (game->keyboardState[SDL_SCANCODE_E]) {
		// if (game->current_scene->name == "hub_level") {
		if (are_colliding(interact_box, game->player->collision_box)) {
			Dialog* dialog = get_dialog_from_json("bobbi");
			if (dialog != NULL) {
				game->current_dialog = dialog;
			}
		}
		// }
	}
	free(interact_box);
}

void update_animation_bobbi(Entity* e, float delta) {
    (void)delta;
    (void)e;
	return;
}

Entity* init_bobbi(GameData* game, int x, int y) {
	int* nbs = malloc(sizeof(int));
	nbs[0] = 7;
	int* lock = malloc(sizeof(int));
	lock[0] = 0;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_bobbi");  // to change

	Entity* bobbi = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_bobbi, event_handler_bobbi, update_animation_bobbi, 9999, false);


	return bobbi;
}

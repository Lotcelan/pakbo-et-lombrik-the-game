#include "greg.h"

// SECTION ENTITE
void update_greg(GameData* game, Entity* greg, float delta_t) {
	(void) delta_t;
	if (greg == NULL) {
		return;
	}


	Box* interact_box = init_rect_box_from_entity(game, greg);
	// pour l'instant on suppose
	interact_box->zone.x = greg->x_position - 10;
	interact_box->zone.y = greg->y_position - 10;
	interact_box->zone.w = greg->collision_box->zone.w + 10;
	interact_box->zone.h = greg->collision_box->zone.h + 10;

	// if (game->current_scene->name == "hub_level") {
	if (are_colliding(interact_box, game->player->collision_box)) {
		Text* press_text = init_text(game, "Press E", (SDL_Color){255, 255, 255, 255}, greg->x_position, greg->y_position - 20, get(game->fonts, "suifak_small", strcmp));
		push_render_stack_text(game, press_text, true);
	}
	// }

	free(interact_box);
}
void event_handler_greg(Entity* greg, GameData* game) {
	Box* interact_box = init_rect_box_from_entity(game, greg);
	interact_box->zone.x = greg->x_position - 10;
	interact_box->zone.y = greg->y_position - 10;
	interact_box->zone.w = greg->collision_box->zone.w + 10;
	interact_box->zone.h = greg->collision_box->zone.h + 10;

	if (game->keyboardState[SDL_SCANCODE_E]) {
		// if (game->current_scene->name == "hub_level") {
		if (are_colliding(interact_box, game->player->collision_box)) {
			Dialog* dialog = get_dialog_from_json("greg");
			if (dialog != NULL) {
				game->current_dialog = dialog;
			}
		}
		// }
	}
	free(interact_box);
}

void update_animation_greg(Entity* e, float delta) {
    (void)delta;
    (void)e;
	return;
}

Entity* init_greg(GameData* game, int x, int y) {
	int* nbs = malloc(sizeof(int));
	nbs[0] = 7;
	int* lock = malloc(sizeof(int));
	lock[0] = 0;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_greg");  // to change

	Entity* greg = init_entity(x, y, 14, spritesheet, 32, 32, nbs, lock, update_greg, event_handler_greg, update_animation_greg, 9999, false);


	return greg;
}

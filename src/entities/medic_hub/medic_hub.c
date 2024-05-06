#include "medic_hub.h"

// SECTION ENTITE
void update_medic_hub(GameData* game, Entity* medic_hub, float delta_t) {
	(void) delta_t;
	if (medic_hub == NULL) {
		return;
	}

	Box* interact_box = init_rect_box_from_entity(game, medic_hub);
	// pour l'instant on suppose
	interact_box->zone.x = medic_hub->x_position - 10;
	interact_box->zone.y = medic_hub->y_position - 10;
	interact_box->zone.w = medic_hub->collision_box->zone.w + 10;
	interact_box->zone.h = medic_hub->collision_box->zone.h + 10;

	// if (game->current_scene->name == "hub_level") {
	if (are_colliding(interact_box, game->player->collision_box)) {
		Text* press_text = init_text(game, "Press E", (SDL_Color){255, 255, 255, 255}, medic_hub->x_position, medic_hub->y_position - 20, get(game->fonts, "suifak_small", strcmp));
		push_render_stack_text(game, press_text, true);
	}
	// }

	free(interact_box);
}
void event_handler_medic_hub(Entity* medic_hub, GameData* game) {
	// SDL_Event event = game->event; // potentiellement avec switch
	// bool* is_going_down = get(medic_hub->objects, "is_going_down", strcmp);
	// bool* is_going_up = get(medic_hub->objects, "is_going_up", strcmp);
	// bool* is_going_left = get(medic_hub->objects, "is_going_left", strcmp);
	// bool* is_going_right = get(medic_hub->objects, "is_going_right", strcmp);
	Box* interact_box = init_rect_box_from_entity(game, medic_hub);
	interact_box->zone.x = medic_hub->x_position - 10;
	interact_box->zone.y = medic_hub->y_position - 10;
	interact_box->zone.w = medic_hub->collision_box->zone.w + 10;
	interact_box->zone.h = medic_hub->collision_box->zone.h + 10;

	if (game->keyboardState[SDL_SCANCODE_E]) {
		// if (game->current_scene->name == "hub_level") {
		if (are_colliding(interact_box, game->player->collision_box)) {
			Dialog* dialog = get_dialog_from_json("medic_hub_test");
			if (dialog != NULL) {
				game->current_dialog = dialog;
			}
		}
		// }
	}
	free(interact_box);
}

void update_animation_medic_hub(Entity* e, float delta) {
    (void)delta;
    (void)e;
	return;
}

Entity* init_medic_hub(GameData* game, int x, int y) {
	int* nbs = malloc(4 * sizeof(int));
	nbs[0] = 7;
	nbs[1] = 8;
	nbs[2] = 5;
	nbs[3] = 1;
	int* lock = malloc(4 * sizeof(int));
	lock[0] = 0;
	lock[1] = 1;
	lock[2] = 1;
	lock[3] = 1;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_lombric");  // to change

	Entity* medic_hub = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_medic_hub, event_handler_medic_hub, update_animation_medic_hub, 9999, false);


	return medic_hub;
}

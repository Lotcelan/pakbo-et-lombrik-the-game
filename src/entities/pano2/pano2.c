#include "pano2.h"

// SECTION ENTITE
void update_pano2(GameData* game, Entity* e, float delta_t) {
	(void) delta_t;
	if (e == NULL) {
		return;
	}

	Box* interact_box = init_rect_box_from_entity(game, e);
	// pour l'instant on suppose
	interact_box->zone.x = e->x_position - 10;
	interact_box->zone.y = e->y_position - 10;
	interact_box->zone.w = e->collision_box->zone.w + 10;
	interact_box->zone.h = e->collision_box->zone.h + 10;

	// if (game->current_scene->name == "hub_level") {
	if (are_colliding(interact_box, game->player->collision_box)) {
		Text* press_text = init_text(game, "Press E", (SDL_Color){255, 255, 255, 255}, e->x_position, e->y_position - 20, get(game->fonts, "suifak_small", strcmp));
		push_render_stack_text(game, press_text, true);
	}
	// }

	free(interact_box);
}
void event_handler_pano2(Entity* pano2, GameData* game) {
	Box* interact_box = init_rect_box_from_entity(game, pano2);
	interact_box->zone.x = pano2->x_position - 10;
	interact_box->zone.y = pano2->y_position - 10;
	interact_box->zone.w = pano2->collision_box->zone.w + 10;
	interact_box->zone.h = pano2->collision_box->zone.h + 10;

	if (game->keyboardState[SDL_SCANCODE_E]) {
		// if (game->current_scene->name == "hub_level") {
		if (are_colliding(interact_box, game->player->collision_box)) {
			Dialog* dialog = get_dialog_from_json("pano2");
			if (dialog != NULL) {
				game->current_dialog = dialog;
			}
		}
		// }
	}
	free(interact_box);
}

void update_animation_pano2(Entity* e, float delta) {
    (void)delta;
    (void)e;
	return;
}

Entity* init_pano2(GameData* game, int x, int y) {
	int* nbs = malloc(sizeof(int));
	nbs[0] = 1;
	int* lock = malloc(sizeof(int));
	lock[0] = 0;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_panoda");  // to change

	Entity* pano2 = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_pano2, event_handler_pano2, update_animation_pano2, 9999, false);


	return pano2;
}

#include "first_boss_room.h"

void update_first_boss_room(GameData* game) {
	// printf("Current coords : %d, %d\n", moving_platform->position.x, moving_platform->position.y);

	Structure* moving_platform_left = get(game->current_scene->objects, "moving_platform_left", strcmp);
	Structure* moving_platform_right = get(game->current_scene->objects, "moving_platform_right", strcmp);
	int* state = get(game->current_scene->objects, "state", strcmp);

	if (moving_platform_left == NULL || moving_platform_right == NULL || state == NULL) {
		return;
	}

    int previous_state = *state;
	if (moving_platform_left->position.x < 0) {
		change_structure_coordinates(game, moving_platform_left, moving_platform_left->position.x + 3, moving_platform_left->position.y);
	} else {
        if (previous_state < 1) {
            change_structure_coordinates(game, moving_platform_left, 0, moving_platform_left->position.y);
            *state = 1;
        }
	}
	if (moving_platform_right->position.x > game->width_amount * CELL_WIDTH / 2) {
		change_structure_coordinates(game, moving_platform_right, moving_platform_right->position.x - 3, moving_platform_right->position.y);
	} else {
        if (previous_state < 1) {
		    change_structure_coordinates(game, moving_platform_right, game->width_amount * CELL_WIDTH / 2, moving_platform_right->position.y);
            *state = 1;
        }
	}

    if (*state == 1) {
        EntityInitFunc* boss_func = get(game->entities, "first_final_boss", strcmp);
        if (!boss_func) return;
        Entity* boss = (*boss_func)(game, 7, 2);
        game->current_scene->entities = append_first(boss, game->current_scene->entities);
        insert(game->current_scene->objects, "boss", boss, NULL);
        *state = 2;
    }

    if (*state == 5) {
        game->state = CLOSING;
        return;
    }
    Entity* boss = (Entity*)get(game->current_scene->objects, "boss", strcmp);
    if (!boss) return;
    if (!boss->objects) return;
    int* phase = get(boss->objects, "phase", strcmp);
    if (!phase) return;

    if (*phase == 2 && *state < 3) {
        *state = 3;
        Structure* upper_left_platform = init_structure(game, "upper_left_platform", "src_assets_structures_sol", 2, 8, 11, "none");
        Structure* upper_right_platform = init_structure(game, "upper_right_platform", "src_assets_structures_sol", 15-2, 8, 11, "none");
        insert(game->current_scene->objects, "upper_left_platform", upper_left_platform, NULL);
        insert(game->current_scene->objects, "upper_right_platform", upper_right_platform, NULL);
        game->current_scene->structures = append_first(upper_left_platform, game->current_scene->structures);
        game->current_scene->structures = append_first(upper_right_platform, game->current_scene->structures);
        push_render_stack_structure(game, upper_left_platform, false);
        push_render_stack_structure(game, upper_right_platform, false);
        spawn_modifier_in_scene(game, game->current_scene, create_modifier(N_LIFE, 1, -1), 2 , 6);
        spawn_modifier_in_scene(game, game->current_scene, create_modifier(N_LIFE, 1, -1), 2 , 6);
        spawn_modifier_in_scene(game, game->current_scene, create_modifier(N_JUMP, 1, -1), (15-2) , 6);
    }

    if (*state == 3) {
        // montée des plateformes
        Structure* upper_left = get(game->current_scene->objects, "upper_left_platform", strcmp);
        Structure* upper_right = get(game->current_scene->objects, "upper_right_platform", strcmp);
        if (!upper_left || ! upper_right) return;

        int current_y = upper_left->position.y;
        if (current_y > game->height_amount * CELL_HEIGHT / 2) {
            change_structure_coordinates(game, upper_left, upper_left->position.x, current_y - 2);
            change_structure_coordinates(game, upper_right, upper_right->position.x, current_y - 2);
        } else {
            *state = 4;
        }
        
    }

    if (*phase == 3) {
        *state = 5;
        bool* DO_NOT_CLEAR = get(boss->objects, "DO_NOT_CLEAR", strcmp);
        *DO_NOT_CLEAR = false;
        boss->current_hp = -1;
        Dialog* ending_demo = get_dialog_from_json("ending_demo");
        game->current_dialog = ending_demo;

    }

	return;
}

void event_handler_first_boss_room(GameData* game) {
	switch (game->event.type) {
	case SDL_KEYDOWN:
		switch (game->event.key.keysym.sym) {
		default:
			break;
		}
		break;
	case SDL_QUIT:
		game->state = CLOSING;
		break;
	default:
		break;
	}
	return;
}

void populate_first_boss_room(GameData* game) {
	push_background_structures(game);

	if (game->player) {
		change_entity_coordinates(game->player, game->player->x_position, 6 * CELL_HEIGHT);
		game->player->y_velocity = -220;
	}

	Structure* moving_platform_left = init_structure(game, "moving_platform_left", "src_assets_cafet_tablePingPongHalf", -8, 7, 0, "none");
	insert(game->current_scene->objects, "moving_platform_left", moving_platform_left, NULL);
	game->current_scene->structures = append_first(moving_platform_left, game->current_scene->structures);
	push_render_stack_structure(game, moving_platform_left, false);

	Structure* moving_platform_right = init_structure(game, "moving_platform_right", "src_assets_cafet_tablePingPongHalf", 16, 7, 0, "none");
	insert(game->current_scene->objects, "moving_platform_right", moving_platform_right, NULL);
	game->current_scene->structures = append_first(moving_platform_right, game->current_scene->structures);
	push_render_stack_structure(game, moving_platform_right, false);

	int* state = malloc(sizeof(int));
	*state = 0;	 // state = 0 : initialisation. state = 1 : les plateformes se sont rétractées. state = 2 : le boss est dans la phase 1. state = 3 : le boss phase 1 est mort et montée des 2 plateformes. state = 4:2 plateformes stabilisées. state = 5: phase 2 finie
	insert(game->current_scene->objects, "state", state, free);
}

Scene* init_first_boss_room(GameData* game) {
	Scene* scene = init_scene(game, "first_boss_room");

	scene->update = update_first_boss_room;
	scene->event_handler = event_handler_first_boss_room;
	scene->populate = populate_first_boss_room;

	return scene;
}

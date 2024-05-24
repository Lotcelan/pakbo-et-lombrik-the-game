#include "ice_pic_structure.h"

#include <SDL2/SDL.h>

void update_ice_pic_structure(GameData* game, Entity* icePicStructure, float delta_t) {
	if (icePicStructure == NULL) {
		return;
	}
    // Exemple de logique de monstre

	int* damage = get(icePicStructure->objects, "damage", strcmp);
	if (damage == NULL) {
        return;
	}

	bool* is_attacking = get(icePicStructure->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}

	bool* is_detected = get(icePicStructure->objects, "is_detected", strcmp);
	if (is_detected == NULL) {
		return;
	}

	*is_detected = *is_detected || detect_player(game, icePicStructure, 30);
	update_entity_movement(game, icePicStructure, delta_t, *is_detected);

	bool* exploding = get(icePicStructure->objects, "is_exploding", strcmp);
	if (exploding == NULL) {
        return;
	}

	if (*exploding) {
		damage_entity(game, icePicStructure, *damage, 1000, -1, false, icePicStructure);
	}

	if (are_colliding(icePicStructure->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1, false, icePicStructure);
		*exploding = true;
    }

	if (is_entity_touching_the_top_of_a_structure(icePicStructure, game->current_scene->structures) != NULL) {
		*exploding = true;
	}
	
	return;
}

void event_handler_ice_pic_structure(Entity* icePicStructure, GameData* game) {
	(void)icePicStructure;
	(void)game;
    // utilise si PNJ ou joueur
    
	return;
}

void update_animation_ice_pic_structure(Entity* e, float delta) {
	(void)delta;
	bool* exploding = get(e->objects, "is_exploding", strcmp);
	if (exploding == NULL) {
        return;
	}
	if (*exploding) {
		e->etat = 1;

	}
	
	return;
}

Entity* init_ice_pic_structure(GameData* game, int x, int y) {
	int* nbs = malloc(2 * sizeof(int));
	nbs[0] = 1;	
	nbs[1] = 1;
	int* lock = malloc(2  * sizeof(int));
	lock[0] = 1;
	lock[1] = 1;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_icePicStructure");

    // Changer ici les FPS, la taille d'une case dans la sprite sheet, le nombre d'HP et si l'entité doit avoir une hitbox ou non
	Entity* icePicStructure = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_ice_pic_structure, event_handler_ice_pic_structure, update_animation_ice_pic_structure, 1, true);

    // Exemple de l'utilisation de la hashtable objects
	int* damage = malloc(sizeof(int));
	*damage = 1;
	insert(icePicStructure->objects, "damage", damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(icePicStructure->objects, "is_attacking", is_attacking, free);
    
	bool* is_detected = malloc(sizeof(bool));
	*is_detected = false;
	insert(icePicStructure->objects, "is_detected", is_detected, free);
	
	bool* is_exploding = malloc(sizeof(bool));
	*is_exploding = false;
	insert(icePicStructure->objects, "is_exploding", is_exploding, free);

	return icePicStructure;
}

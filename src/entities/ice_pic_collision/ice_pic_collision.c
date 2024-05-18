#include "ice_pic_collision.h"

#include <SDL2/SDL.h>

void update_ice_pic_collision(GameData* game, Entity* icePicCollision, float delta_t) {
	if (icePicCollision == NULL) {
		return;
	}

	int* damage = get(icePicCollision->objects, "damage", strcmp);
	if (damage == NULL) {
        return;
	}

	bool* is_attacking = get(icePicCollision->objects, "is_attacking", strcmp);
	if (is_attacking == NULL) {
		return;
	}

	update_entity_movement(game, icePicCollision, delta_t, false);

	int* exploding = get(icePicCollision->objects, "is_exploding", strcmp);
	if (exploding == NULL) {
        return;
	}
	printf("exploding : %i \n", *exploding);

	if (*exploding) {
		damage_entity(game, icePicCollision, *damage, 1000, -1);
	}

	if (are_colliding(icePicCollision->hit_box, game->player->hurt_box)) {
		damage_entity(game, game->player, *damage, 1000, -1);
		*exploding = true;
    }

	return;
}

void event_handler_ice_pic_collision(Entity* icePicCollision, GameData* game) {
	(void)icePicCollision;
	(void)game;
    // utilise si PNJ ou joueur
    
	return;
}

void update_animation_ice_pic_collision(Entity* e, float delta) {
	(void)delta;
	int* exploding = get(e->objects, "is_exploding", strcmp);
	if (exploding == NULL) {
        return;
	}
	if (*exploding) {
		e->etat = 1;

	}
	
	return;
}

Entity* init_ice_pic_collision(GameData* game, int x, int y) {
	int* nbs = malloc(2 * sizeof(int));
	nbs[0] = 3;	
	nbs[1] = 3;
	int* lock = malloc(2  * sizeof(int));
	lock[0] = 1;
	lock[1] = 3;

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_icePicCollision");

    // Changer ici les FPS, la taille d'une case dans la sprite sheet, le nombre d'HP et si l'entité doit avoir une hitbox ou non
	Entity* icePicCollision = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_ice_pic_collision, event_handler_ice_pic_collision, update_animation_ice_pic_collision, 1, true);

    // Exemple de l'utilisation de la hashtable objects
	int* damage = malloc(sizeof(int));
	*damage = 1;
	insert(icePicCollision->objects, "damage", damage, free);

	bool* is_attacking = malloc(sizeof(bool));
	*is_attacking = false;
	insert(icePicCollision->objects, "is_attacking", is_attacking, free);
    
	bool* is_exploding = malloc(sizeof(bool));
	*is_exploding = false;
	insert(icePicCollision->objects, "is_exploding", is_exploding, free);

	return icePicCollision;
}

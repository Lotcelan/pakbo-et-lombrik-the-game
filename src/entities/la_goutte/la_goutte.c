#include "la_goutte.h"

#include <SDL2/SDL.h>

void update_la_goutte(GameData* game, Entity* la_goutte, float delta_t) {
	if (la_goutte == NULL) {
		return;
	}
    // Exemple de logique de monstre

	// int* damage = get(la_goutte->objects, "damage", strcmp);
	// if (damage == NULL) {
	// 	return;
	// }

	// bool* is_attacking = get(la_goutte->objects, "is_attacking", strcmp);
	// if (is_attacking == NULL) {
	// 	return;
	// }
	
	// follow_player(game, la_goutte, 30, 30);
	// update_entity_movement(game, la_goutte, delta_t, true);
	// if (are_colliding(la_goutte->hit_box, game->player->hurt_box)) {
	// 	damage_entity(game, game->player, *damage, 1000, -1);
	// 	*is_attacking = true;
	// }
	// else {
	// 	*is_attacking = false;
    // }
	return;
}
void event_handler_la_goutte(Entity* la_goutte, GameData* game) {
	(void)la_goutte;
	(void)game;
    // utilse si PNJ ou joueur
    
	return;
}

void update_animation_la_goutte(Entity* e, float delta) {
	(void)delta;
	// On vient juste modifier e->etat selon certaines conditions

	return;
}

//Entity* init_la_goutte(GameData* game, int x, int y) {
//	int* nbs = malloc(nombre de ligne dans la sheet * sizeof(int));
//	nbs[0] = nb de frame sur la 1ere ligne;	 // idle
//	nbs[1] = nb de frame sur la 2eme ligne
//	...
//	int* lock = malloc(nombre de ligne dans la sheet  * sizeof(int));
//	lock[0] = nb de frames qu on veut "lock" sur la 1ere ligne;
//	...
//
//	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_NOM DE LA SPRITE SHEET");	// to change
//
//    // Changer ici les FPS, la taille d'une case dans la sprite sheet, le nombre d'HP et si l'entité doit avoir une hitbox ou non
//	Entity* la_goutte = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_la_goutte, event_handler_la_goutte, update_animation_la_goutte, 9, true);
//
//    // Exemple de l'utilisation de la hashtable objects
//	// int* duck_damage = malloc(sizeof(int));
//	// *duck_damage = 1;
//	// insert(la_goutte->objects, "damage", duck_damage, free);
//
//	// bool* is_attacking = malloc(sizeof(bool));
//	// *is_attacking = false;
//	// insert(la_goutte->objects, "is_attacking", is_attacking, free);
//
//	return la_goutte;

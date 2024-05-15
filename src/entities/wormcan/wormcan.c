#include "wormcan.h"

#include <SDL2/SDL.h>

void update_wormcan(GameData* game, Entity* e, float delta_t) {
	(void) game;
	(void) e;
	(void) delta_t;
}
void event_handler_wormcan(Entity* e, GameData* game) {
	(void)e;
	(void)game;
	return;
}

void update_animation_wormcan(Entity* e, float delta) {
	(void)e;
	(void)delta;
	return;
}

Entity* init_wormcan(GameData* game, int x, int y) {
	int* nbs = malloc(3*sizeof(int));
	nbs[0] = 12;
	nbs[1] = 4;
	nbs[2] = 12;
	int* lock = malloc(3*sizeof(int));
	lock[0] = 0;
	lock[1] = 0;
	lock[2] = 0;
	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_wormcan");

	Entity* e = init_entity(x, y, 12, spritesheet, 64, 64, nbs, lock, update_wormcan, event_handler_wormcan, update_animation_wormcan, 1, false);
	e->etat = 2;
	e->sprite->currentFrame = e->sprite->frames[2];
	return e;
}

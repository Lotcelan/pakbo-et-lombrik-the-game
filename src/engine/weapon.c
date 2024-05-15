#include<SDL2/SDL.h>
#include "include/weapon.h"

void render_weapon(GameData* game, Entity* e, float delta_t) {
    if (e->weapon) {
        e->weapon->render(game, e, delta_t);
    }
}

int delete_weapon(Weapon *weapon){
    if(weapon){
        // free(weapon->name);
        destroyHashTable(weapon->objects);
        free(weapon);
        return 1;
    }
	return 0;
}

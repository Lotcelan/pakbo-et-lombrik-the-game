#include "include/entity.h"

// TODO
void free_entity(void* entite) {
    // Entity* e = (Entity*)entite;
    free(entite);
}

// /!\ PAS ENCORE TESTÉE
Sprite* get_sprite(Entity* e){
    return e->animations[e->etat];
}

void update_animation(Sprite* sprite, float delta){
    int d = delta;
    // cette boucle sert a gérer les cas ou delta est assez grand pour passer plusieurs frames
    // (exemple : si il y a un lag, on va vouloir sauter une frame)
    while (d - sprite->timer > 0){      
        d = d - sprite->timer;
        sprite->frames = sprite->frames->next;
        sprite->timer = 1/sprite->framerate;    // on reset le timer
    }
    sprite->timer -= d;
}

void print_entity(Entity* e){
    printf("position : (%d, %d)\n", e->x_position, e->y_position);
    printf("velocité : (%.2f, %.2f)\n", e->x_velocity, e->y_velocity);
    printf("état : %d\n", e->etat);
}

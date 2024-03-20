#include "include/entity.h"

void update_self(Entity* e) {
    // Update the entity
    e->update(e);
}

Entity* init_entity(char* entity, int respawn_delay, int x, int y) {
    return NULL;
}

void update_entities(List* entities) {
    // Map to each entity the update function contained in the Entity struct
    map(update_self, entities);
}

void update_pos_speed(Entity *e, float a_x, float a_y, int dt) {    
     /*
    Still have to change the function to add the if statements.
    */
 
    /*
    if no colisions
    */
    e->y_velocity += a_x*dt;
    e->x_velocity += a_y*dt;

    e->x_position += dt*(e->x_velocity);
    e->y_position += dt*(e->y_velocity);

    /*
    if colision up of entity 
    */
    e->x_velocity += a_x*dt;
    e->y_velocity = a_y*dt;

    e->x_position += dt*(e->x_velocity);
    e->y_position += dt*(e->y_velocity);

    /*
    if colision down of entity 
    */
    e->x_velocity += a_x*dt;
    e->y_velocity = 0;

    e->x_position += dt*(e->x_velocity);
    e->y_position += dt*(e->y_velocity);

    /*
    if colision right or left of entity 
    */
    e->x_velocity = 0;
    e->y_velocity += a_y*dt;

    e->x_position += dt*(e->x_velocity);
    e->y_position += dt*(e->y_velocity);

}

void update_animation(Sprite* sprite, float delta){
    int d = delta;
    // cette boucle sert a gérer les cas ou delta est assez grand pour passer plusieurs frames
    // (exemple : si il y a un lag, l'animation est pas ralentie)
    while (d - sprite->timer > 0){      
        d = d - sprite->timer;
        sprite->frames = sprite->frames->next;
        sprite->timer = 1/sprite->framerate;    // on reset le timer
    }
    sprite->timer -= d;
}

void print_entity(Entity* e){
    printf("position : (%d, %d)\n", e->x_position, e->y_position);
    printf("velocité : (%d, %d)\n", e->x_velocity, e->y_velocity);
    printf("état : %d\n", e->etat);
}
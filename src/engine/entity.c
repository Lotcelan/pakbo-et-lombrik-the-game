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

void update_animation(Entity entite, float delta){
    
};
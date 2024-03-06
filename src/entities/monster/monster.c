#include<SDL2/SDL.h>
#include "monster.h"

int delete_mob(monster_t *monster){
    if(monster->current_pv == 0){
        return 1;
    } else {
        return 0;
    }
}

void damaged_mob(monster_t *monster, int damage_value){
    monster->current_pv = monster->current_pv - damage_value; 
}

int get_x(monster_t *monster){
    return monster->x_position;
}

int get_y(monster_t *monster){
    return monster->y_position;
}
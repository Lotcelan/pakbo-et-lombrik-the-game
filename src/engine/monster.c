
#include "include/monster.h"

int delete_mob(monster_t *monster){
    if(monster->current_hp == 0){
        return 1;
    } else {
        return 0;
    }
}

void damaged_mob(monster_t *monster, int damage_value){
    monster->current_hp = monster->current_hp - damage_value; 
}


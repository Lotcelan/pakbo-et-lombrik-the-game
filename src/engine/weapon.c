#include<SDL2/SDL.h>
#include"include/weapon.h"

int delete_weapon(Weapon_t *weapon){
    if(weapon->current_pv == 0){
        return 1;
    } else {
        return 0;
#include<SDL2/SDL.h>
#include"weapon.h"

struct _monster_t{
    char *name;
    int *hp;
    int current_hp;
    int direction;
    Weapon_t *weapon;

};

typedef struct _monster_t monster_t;

int delete_mob(monster_t *monster);
void damaged_mob(monster_t *monster, int damage_value);

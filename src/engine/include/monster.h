#include<SDL2/SDL.h>
#include"weapon.h"
#include"entity.h"

struct _monster_t{
    char *name;
    int direction;
    int max_hp;
    int current_hp; // when current_hp  = 0, the entity is dead 
    Weapon_t *weapon;
    Entity *entity;

};

typedef struct _monster_t monster_t;

int delete_mob(monster_t *monster);
void damaged_mob(monster_t *monster, int damage_value);

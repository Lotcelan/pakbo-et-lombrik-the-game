#include<SDL2/SDL.h>

struct _weapon_t
{
    char *name;
    int damage_value;
    int *pv;
    int current_pv;
    
};

typedef struct _weapon_t Weapon_t;

int delete_weapon(Weapon_t *weapon);
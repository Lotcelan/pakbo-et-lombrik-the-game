#include<SDL2/SDL.h>

struct _weapon_t
{
    char *name;
    int damage_value;
    int *pv;
    int current_pv;
};

typedef struct _weapon_t weapon_t;

int delete_weapon(weapon_t *weapon);
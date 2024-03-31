#include<SDL2/SDL.h>

struct _weapon_t
{
    char *name;
    int damage_value;
    int max_durability;
    int current_durability;
    int is_on_ground;
    
    
    
};

typedef struct _weapon_t Weapon_t;

int delete_weapon(Weapon_t *weapon);

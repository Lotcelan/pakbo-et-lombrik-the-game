#include<SDL2/SDL.h>
#include"../../weapon/weapon.h"

struct _monster_t{
    char *name;
    int *pv;
    int current_pv;
    int x_position;
    int y_position;
    weapon_t *weapon;
    SDL_Texture* sprite;

};

typedef struct _monster_t monster_t;

int delete_mob(monster_t *monster);
void damaged_mob(monster_t *monster, int damage_value);
int get_x(monster_t *monster);
int get_y(monster_t *monster);
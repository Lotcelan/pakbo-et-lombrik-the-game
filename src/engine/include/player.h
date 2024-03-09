#include<SDL2/SDL.h>
#include"weapon.h"

struct _player_t{
    char *name;
    int current_hp;
    int *hp;
    int *state;
    int *double_jump;
    int *direction; // looking right or left after a end of a run 
    Weapon_t *weapon;

};

typedef struct _player_t player_t;

void damaged_player(player_t *player, int damage_value);
int delete_player(player_t *player);

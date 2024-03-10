#include<SDL2/SDL.h>
#include"weapon.h"




struct _player_t{
    char *name;
    int state;
    int double_jump;
    int direction; // looking right or left after a end of a run 
    int respawn_delay;
    int max_hp;
    int current_hp; // when current_hp  = 0, the entity is dead 
    Weapon_t *weapon;

};

typedef struct _player_t player_t;

void damaged_player(player_t *player, int damage_value);
int delete_player(player_t *player);

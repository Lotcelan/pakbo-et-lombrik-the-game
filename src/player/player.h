#include<SDL2/SDL.h>
#include"../weapon/weapon.h"

struct _player_t{
    char *name;
    int x_position;
    int y_position;
    int current_pv;
    int *pv;
    int *state;
    int *double_jump;
    int *direction;
    int *speed;
    weapon_t *weapon;
    SDL_Texture* sprite;

};

typedef struct _player_t player_t;

void damaged_player(player_t *player, int damage_value);
int delete_player(player_t *player);
int get_x(player_t *player);
int get_y(player_t *player);

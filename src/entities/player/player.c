#include <SDL2/SDL.h>
#include "player.h"

void damaged_player(player_t *player, int damage_value){
    player->current_pv = player->current_pv - damage_value;
}

int delete_player(player_t *player){
    if(player->current_pv == 0){
        return 1;
    } else {
        return 0;
    }
}

int get_x(player_t *player){
    return player->x_position;
}

int get_y(player_t *player){
    return player->y_position;
}
#include "include/player.h"

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


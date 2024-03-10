#include "include/player.h"

void damaged_player(player_t *player, int damage_value){
    player->current_hp = player->current_hp - damage_value;
}

int delete_player(player_t *player){
    if(player->current_hp == 0){
        return 1;
    } else {
        return 0;
    }
}


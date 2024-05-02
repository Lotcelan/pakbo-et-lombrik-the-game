#include "game_over.h"

// cette fonction est inutile, elle sert à annuler la gravité et la gestion des touches
void immobile(Entity* e, GameData* game){
    return;
}
void animation_mort(Entity* e, float delta){
    e->etat = 4;
    return;
}

void update_mort(GameData* game, Entity* e, float delta){
    e->x_velocity = 0;
    e->y_velocity = 0;
    e->damage_delay = 0;
}

void update_game_over(GameData* game){
    game->player->event_handler = &immobile;
    game->player->update_animation = &animation_mort;
    game->player->update = &update_mort;
    int* position = (int*) game->player->sprite->currentFrame->value;
    if (position[0] == 8){
        change_scene(game, "hub_level");
        game->player->update = update_player;
        game->player->event_handler = event_handler_player;
        game->player->update_animation = update_animation_player;
    }
    return;
}
void event_handler_game_over(GameData* game){
    return;
}
void populate_game_over(GameData* game){
    return;
}
Scene* init_game_over(GameData* game){
    Scene* scene = init_scene(game, "game_over");
    scene->update = update_game_over;
    scene->event_handler = event_handler_game_over;
    scene->populate = populate_game_over;
    return scene;
}
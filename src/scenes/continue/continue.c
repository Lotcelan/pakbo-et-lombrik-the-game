#include "continue.h"

// cette fonction est inutile, elle sert à annuler la gestion des touches
void immobile_cont(Entity* e, GameData* game){
    return;
}

void update_player_continue(GameData* game, Entity* e, float delta){
    e->x_velocity = 0;
    e->y_velocity = 0;
    e->damage_delay = 0;
}

void update_continue(GameData* game){
    game->player->event_handler = &immobile_cont;
    game->player->update = &update_player_continue;
    // si on atteint la dernière frame de l'animation de mort
    int* position = (int*) game->player->sprite->currentFrame->value;
    if (position[0] == 8){
        change_scene(game, "hub_level");
        game->player->update = update_player;
        game->player->event_handler = event_handler_player;
        game->player->update_animation = update_animation_player;
    }
    return;
}

void event_handler_continue(GameData* game){
    return;
}

void populate_continue(GameData* game){
    push_background_structures(game);
    change_entity_coordinates(game->player, 120, 90);
    return;
}

Scene* init_continue(GameData* game){
    Scene* scene = init_scene(game, "continue");
    scene->update = update_continue;
    scene->event_handler = event_handler_continue;
    scene->populate = populate_continue;
    return scene;
}
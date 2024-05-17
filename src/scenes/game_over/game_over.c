#include "game_over.h"

// cette fonction est inutile, elle sert à annuler la gravité et la gestion des touches
void immobile(Entity* e, GameData* game){
    (void) e;
    (void) game;
    return;
}
void animation_mort(Entity* e, float delta){
    (void) delta;
    e->etat = 4;
    return;
}

void update_mort(GameData* game, Entity* e, float delta){
    (void) game;
    (void) delta;
    e->x_velocity = 0;
    e->y_velocity = 0;
    e->damage_delay = -1;
    e->stagger_duration = -1;
}

void update_game_over(GameData* game){
    // Pcq on a du appeler change_scene(game, "game_over_-1_-1"), alors on remet le joueur à sa position initiale
    change_entity_coordinates(game->player, game->player->prev_collision_box->zone.x, game->player->prev_collision_box->zone.y);

    game->player->event_handler = immobile;
    game->player->update_animation = animation_mort;
    game->player->update = update_mort;
    // si on atteint la dernière frame de l'animation de mort
    int* position = (int*) game->player->sprite->currentFrame->value;
    if (position[0] == 8){
        game->player->sprite->currentFrame = game->player->sprite->frames[0];
        game->player->update = update_player;
        game->player->event_handler = event_handler_player;
        printf("chgt animation player\n");
        game->player->update_animation = update_animation_player;
        change_scene(game, "continue_7_5");
        
    }
    return;
}
void event_handler_game_over(GameData* game){
    (void)game;
    return;
}
void populate_game_over(GameData* game){
    push_background_structures(game);
    return;
}
Scene* init_game_over(GameData* game){
    Scene* scene = init_scene(game, "game_over");
    scene->update = update_game_over;
    scene->event_handler = event_handler_game_over;
    scene->populate = populate_game_over;
    return scene;
}
#include "continue.h"

// cette fonction est inutile, elle sert à annuler la gestion des touches
void immobile_cont(Entity* e, GameData* game){
    (void) e;
    (void) game;
    return;
}

void update_player_continue(GameData* game, Entity* e, float delta){
    e->y_velocity = 0;
    e->damage_delay = -1;
    update_entity_movement(game, game->player, delta, false);
}

void update_continue(GameData* game){
    game->player->event_handler = &immobile_cont;
    game->player->update = &update_player_continue;
    // on regarde si la canette (wormcan) doit boucler la fin de son animation
    Entity* wormcan = game->current_scene->entities->value;
    int* position = (int*) wormcan->sprite->currentFrame->value;
    if (position[0] == 11 && position[1] == 0){
        wormcan->sprite->currentFrame = wormcan->sprite->frames[1];
        wormcan->etat = 1;
	}
    // si on atteint la dernière frame de l'animation de mort
    if (game->player->x_position >= 240){
        game->player->update = update_player;
        game->player->event_handler = event_handler_player;
        game->player->update_animation = update_animation_player;
        change_scene(game, "telecom_3_4");
        game->player->x_velocity = 0;
    }
    else if (game->player->x_position <= -10){
        game->player->update = update_player;
        game->player->event_handler = event_handler_player;
        game->player->update_animation = update_animation_player;
        change_scene(game, "main_menu_-1_-1");
        game->player->x_velocity = 0;
    }
}

void event_handler_continue(GameData* game){
    if (game->player->x_velocity == 0){
        Entity* wormcan = game->current_scene->entities->value;
        if (game->keyboardState[SDL_SCANCODE_RIGHT]){
            wormcan->sprite->currentFrame = wormcan->sprite->frames[0];
            wormcan->etat = 0;
            game->player->x_velocity = 60;
            game->player->sprite->orientation = SDL_FLIP_NONE;
        }
        if (game->keyboardState[SDL_SCANCODE_LEFT]){
            game->player->x_velocity = -60;
            game->player->sprite->orientation = SDL_FLIP_HORIZONTAL;
        }
    }
}


void populate_continue(GameData* game){
    game->current_scene->entities = append_first(init_wormcan(game, 89, 13), game->current_scene->entities);
    push_background_structures(game);
    // change_entity_coordinates(game->player, 120, 90); // tkt, je le gère ailleurs
    game->player->sprite->orientation = SDL_FLIP_NONE;
    return;
}

Scene* init_continue(GameData* game){
    Scene* scene = init_scene(game, "continue");
    scene->update = update_continue;
    scene->event_handler = event_handler_continue;
    scene->populate = populate_continue;
    return scene;
}
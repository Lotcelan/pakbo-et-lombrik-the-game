#include "game_over.h"

void update_game_over(GameData* game){
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
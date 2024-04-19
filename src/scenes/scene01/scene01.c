#include "scene01.h"

void update_scene01(GameData* game) {
    (void)game;
    // update the scene
    return;
}

void event_handler_scene01(GameData* game) {
    (void)game;
    // handle the events
    return;
}

void populate_scene01(GameData* game) {
    push_background_structures(game);
    return;
}

Scene* init_scene01(GameData* game) {
    Scene* scene = init_scene(game, "scene01");
    scene->update = update_scene01;
    scene->event_handler = event_handler_scene01;
    scene->populate = populate_scene01;

    return scene;
}

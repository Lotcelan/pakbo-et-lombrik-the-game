#include "scene01.h"

void update_scene01(GameData* game) {
    // update the scene
    return;
}

Scene* init_scene01(GameData* game) {
    printf("hola\n");
    Scene* scene = init_scene(game, "scene01");
    scene->update = update_scene01;

    return scene;
}

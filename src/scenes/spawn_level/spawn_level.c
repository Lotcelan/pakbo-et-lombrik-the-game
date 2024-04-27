#include "spawn_level.h"

void update_spawn_level(GameData* game) {
    // update the scene
    (void)game;
    return;
}

void event_handler_spawn_level(GameData* game) {
    ScreenShake* screen_shake;
    switch (game->event.type) {
        case SDL_KEYDOWN:
            switch (game->event.key.keysym.sym) {
                // case SDLK_ESCAPE:
                //     game->running = 0;
                //     break;
                case SDLK_h:
                    screen_shake = init_screen_shake(10, 10);
                    // printf("Screen shake: %p\n", (void*)&screen_shake);
                    game->current_scene->screen_shake = screen_shake;
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            game->state = CLOSING;
            break;
        default:
            break;
    }
    return;
}

void populate_spawn_level(GameData* game) {
    push_background_structures(game);
}

Scene* init_spawn_level(GameData* game) {
    Scene* scene = init_scene(game, "spawn_level");
    scene->update = update_spawn_level;
    scene->event_handler = event_handler_spawn_level;
    scene->populate = populate_spawn_level;
    return scene;
}

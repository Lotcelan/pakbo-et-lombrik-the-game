#include "etagere_level.h"

void update_etagere_level(GameData* game) {
    // update the scene
    return;
}

void event_handler_etagere_level(GameData* game) {
    switch (game->event.type) {
        case SDL_KEYDOWN:
            switch (game->event.key.keysym.sym) {
                // case SDLK_ESCAPE:
                //     game->running = 0;
                //     break;
                case SDLK_h:
                    ScreenShake* screen_shake = init_screen_shake(10, 10);
                    printf("Screen shake: %p\n", screen_shake);
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

void populate_etagere_level(GameData* game) {
    push_background_structures(game);
}

Scene* init_etagere_level(GameData* game) {
    Scene* scene = init_scene(game, "etagere_level");
    scene->update = update_etagere_level;
    scene->event_handler = event_handler_etagere_level;
    scene->populate = populate_etagere_level;
    return scene;
}

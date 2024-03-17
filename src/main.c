#include "engine/include/game.h"
#include "engine/include/scenes.h"
#include "engine/include/entity.h"

#include "resources.h"

#include "scenes/scene01/scene01.h"

int main(int argc, char *argv[]) {
    // set_dir(); -> todo
    // Initialize SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    GameData* game = init_game(16, 16, 1024, 1024, "Pakbo é Lonbrik", 30);

    
    // Init scenes
    Scene* scene01 = init_scene01(game);
    game->current_scene = scene01;

    /* Main loop :
        - Getting events
        - Updating the entities logic with the event
        - Updating the scene logic with the event
        - Render the scene
        - Render the entities
    */

    // Variables for deltaT between each loop
    int t0;
    t0 = SDL_GetTicks();
    int deltaT;

    while (game->state != CLOSING) {
        // downscale_render(game);
        // Calculate deltaT and set t0 to the current time
        deltaT = SDL_GetTicks() - t0;
        t0 = SDL_GetTicks(); 

        printf("hola\n");
        // event_handler(game);
        while (SDL_PollEvent(&(game->event)) != 0) {
            if ((game->event).type == SDL_QUIT) {
                game->state = CLOSING;
            }
        }

        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);

        if (game->current_scene != NULL) {
            update_entities(game->current_scene->entities);
            game->current_scene->update(game);
        }

        render_scene(game);

        // upscale_render(game);

        SDL_RenderPresent(game->renderer);
        cap_fps(game->frm);
    }
    

    free_game(game);
    SDL_Quit();

    return 0;
}

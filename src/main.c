#include "engine/include/game.h"
#include "engine/include/scenes.h"
#include "engine/include/entity.h"

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    GameData* game = init_game(800, 600, "SDL2 Window");

    /* Main loop :
        - Getting events
        - Updating the entities logic with the event
        - Updating the scene logic with the event
        - Render the scene
        - Render the entities
    */

    while (game->state != PAUSED) {
        printf("Game state: %d\n", game->state);
        while (SDL_PollEvent(&(game->event)) != 0) {
            printf("Event");
            if ((game->event).type == SDL_QUIT) {
                game->state = PAUSED;
            }
        }
        printf("a");
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        printf("b");
        SDL_RenderClear(game->renderer);

        update_entities(game->current_scene->entities);
        update_scene(game->current_scene);

        render_scene(game->current_scene, game);

        SDL_RenderPresent(game->renderer);
    }

    free_game(game);
    SDL_Quit();

    return 0;
}

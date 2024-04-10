#include "engine/include/game.h"
#include "engine/include/scenes.h"
#include "engine/include/entity.h"

#include "resources.h"

#include "scenes/scene01/scene01.h"
#include "scenes/main_menu/main_menu.h"
#include "scenes/spawn_level/spawn_level.h"
#include "scenes/etagere_level/etagere_level.h"

#include "entities/player/player.h"

int main(int argc, char *argv[]) {
    printf("oskouuuur \n");
    set_dir();
    // Initialize SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    TTF_Init();

    GameData* game = init_game(16, 8, 1024, 512, "Pakbo é Lonbrik", 30);

    // Init entities MUST DO IT BEFORE INIT SCENES
    EntityInitFunc* i_p = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
    *i_p = init_player;
    printf("i_p : %p\n", i_p);
    insert(game->entities, "player", i_p);
    printKeys(game->entities);


    
    // Init scenes
    Scene* scene01 = init_scene01(game);
    Scene* main_menu = init_main_menu(game);
    Scene* spawn_level = init_spawn_level(game);
    Scene* etagere_level = init_etagere_level(game);

    insert(game->scenes, "scene01", scene01);
    insert(game->scenes, "main_menu", main_menu);
    insert(game->scenes, "spawn_level", spawn_level);
    insert(game->scenes, "etagere_level", etagere_level);


    change_scene(game, "main_menu");

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
        // Calculate deltaT and set t0 to the current time
        deltaT = SDL_GetTicks() - t0;
        t0 = SDL_GetTicks(); 


        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
        SDL_RenderClear(game->renderer);


        // event_handler(game);
        while (SDL_PollEvent(&(game->event)) != 0) {
            if ((game->event).type == SDL_QUIT) {
                game->state = CLOSING;
            }
            if (game->current_scene != NULL) {
                game->current_scene->event_handler(game);
                List* current = game->current_scene->entities;
                while (current != NULL) {
                    Entity* e = (Entity*)current->value;
                    e->event_handler(e, game);
                    current = current->next;
                }
            }


        }

        if (game->current_scene != NULL) {
            // update_entities(game->current_scene->entities);
            game->current_scene->update(game);
            List* current = game->current_scene->entities;
            while (current != NULL) {
                Entity* e = (Entity*)current->value;
                e->update(e, deltaT);
                current = current->next;
            }
        }
        // Render entities ici

        render_scene(game, deltaT);
        // render_screen_shake(game);

        SDL_RenderPresent(game->renderer);
        cap_fps(game->frm);
    }
    

    free_game(game);
    SDL_Quit();

    return 0;
}

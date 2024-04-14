#include "engine/include/game.h"
#include "engine/include/scenes.h"
#include "engine/include/entity.h"
#include "engine/include/hud.h"

#include "resources.h"

#include "scenes/scene01/scene01.h"
#include "scenes/main_menu/main_menu.h"
#include "scenes/spawn_level/spawn_level.h"
#include "scenes/etagere_level/etagere_level.h"

#include "entities/player/player.h"
#include "entities/canard01/canard01.h"

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
    *i_p = init_canard01;
    insert(game->entities, "canard01", i_p);
    printKeys(game->entities);

    // potentiellement systeme de sauvegarde plus tard (donc init avec valeurs différentes)
    Entity* player = init_player(game, -1, -1); // -1 -1 convention pour dire que l'on ne l'affiche pas
    game->player = player;
    
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


    TTF_Font* font = TTF_OpenFont("../src/assets/Suifak.otf", 24);
    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 0;
    }

    insert(game->fonts, "suifak", font);

    font = TTF_OpenFont("../src/assets/Suifak.otf", 12);
    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 0;
    }
    insert(game->fonts, "suifak_small", font);

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


        if (game->current_dialog == NULL) {

        // event_handler(game);
        while (SDL_PollEvent(&(game->event)) != 0) {
            if ((game->event).type == SDL_QUIT) {
                game->state = CLOSING;
            }
            if (game->current_scene != NULL) {
                game->current_scene->event_handler(game);

                if (game->player != NULL) {
                    game->player->event_handler(game->player, game);
                }
                // tout ceci devrait être inutile en théorie (a part pour les PNJ avec lesquels on peut intéragir)
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

            if (game->player != NULL) {
                game->player->update(game, game->player, deltaT);
            }

            List* current = game->current_scene->entities;
            while (current != NULL) {
                Entity* e = (Entity*)current->value;
                e->update(game, e, deltaT);
                current = current->next;
            }
        }
        // Render entities ici

            render_scene(game, deltaT);
            render_hud(game);
            // render_screen_shake(game);

        } else {
            // Peut être à revoir, peut sûrement être abuse (peut être pour skip frames)
            while (SDL_PollEvent(&(game->event)) != 0) {
                if ((game->event).type == SDL_QUIT) {
                    game->state = CLOSING;
                }
                dialog_event_handler(game);
            }

            update_dialog(game);
            render_dialog(game);
        }
        SDL_RenderPresent(game->renderer);
        cap_fps(game->frm);
    }
    

    free_game(game);
    SDL_Quit();

    return 0;
}

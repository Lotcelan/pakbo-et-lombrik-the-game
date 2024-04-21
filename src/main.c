#include "engine/include/entity.h"
#include "engine/include/game.h"
#include "engine/include/hud.h"
#include "engine/include/scenes.h"
#include "entities/canard01/canard01.h"
#include "entities/duck_orange/duck_orange.h"
#include "entities/blue_canard_boss/blue_canard_boss.h"
#include "entities/player/player.h"
#include "entities/projectile_arrow/projectile_arrow.h"
#include "entities/projectile_laser/projectile_laser.h"
#include "entities/medic_hub/medic_hub.h"
#include "resources.h"
#include "scenes/etagere_level/etagere_level.h"
#include "scenes/main_menu/main_menu.h"
#include "scenes/scene01/scene01.h"
#include "scenes/spawn_level/spawn_level.h"
#include "scenes/simple_arena/simple_arena.h"
#include "scenes/hub_level/hub_level.h"
#include "weapons/arbalete/arbalete.h"
#include "weapons/basic_sword/basic_sword.h"
#include "weapons/blue_duck_boss_laser/blue_duck_boss_laser.h"

int main(int argc, char* argv[]) {
	(void)argc; // Pour les warnings
    (void)argv;

	set_dir();
	// Initialize SDL

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	TTF_Init();

	GameData* game = init_game(16, 8, 1024, 512, "Pakbo é Lonbrik", 30);

	// Init weapons MUST DO IT BEFORE ENTITIES
	WeaponInitFunc* i_w = (WeaponInitFunc*)malloc(sizeof(WeaponInitFunc));
	*i_w = init_basic_sword;
	insert(game->weapons, "basic_sword", i_w);

	WeaponInitFunc* i_a = (WeaponInitFunc*)malloc(sizeof(WeaponInitFunc));
	*i_a = init_arbalete;
	insert(game->weapons, "arbalete", i_a);

    WeaponInitFunc* i_bdbl = (WeaponInitFunc*)malloc(sizeof(WeaponInitFunc));
    *i_bdbl = init_blue_duck_boss_laser;
    insert(game->weapons, "blue_duck_boss_laser", i_bdbl);

	// Init entities MUST DO IT BEFORE INIT SCENES
	EntityInitFunc* i_p = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_p = init_canard01;
	insert(game->entities, "canard01", i_p);

	EntityInitFunc* i_arrow = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_arrow = init_projectile_arrow;
	insert(game->entities, "projectile_arrow", i_arrow);

    EntityInitFunc* i_laser = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_laser = init_projectile_laser;
	insert(game->entities, "projectile_laser", i_laser);

    EntityInitFunc* i_bcb = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
    *i_bcb = init_blue_canard_boss;
    insert(game->entities, "blue_canard_boss", i_bcb);

	EntityInitFunc* i_medic_hub = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_medic_hub = init_medic_hub;
	insert(game->entities, "medic_hub", i_medic_hub);
	
	EntityInitFunc* i_duck_orange = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_duck_orange = init_duck_orange;
	insert(game->entities, "duck_orange", i_duck_orange);

	// potentiellement systeme de sauvegarde plus tard (donc init avec valeurs différentes)
	Entity* player = init_player(game, -1, -1);	 // -1 -1 convention pour dire que l'on ne l'affiche pas
	game->player = player;

	// Init scenes
	Scene* scene01 = init_scene01(game);
	Scene* main_menu = init_main_menu(game);
	Scene* spawn_level = init_spawn_level(game);
	Scene* etagere_level = init_etagere_level(game);
    Scene* simple_arena = init_simple_arena(game);
	Scene* hub_level = init_hub_level(game);

	insert(game->scenes, "scene01", scene01);
	insert(game->scenes, "main_menu", main_menu);
	insert(game->scenes, "spawn_level", spawn_level);
	insert(game->scenes, "etagere_level", etagere_level);
    insert(game->scenes, "simple_arena", simple_arena);
	insert(game->scenes, "hub_level", hub_level);

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
                SDL_PumpEvents();
				if (game->current_scene != NULL) {
					game->current_scene->event_handler(game);

					if (game->player != NULL) {
						game->player->event_handler(game->player, game);
						if (game->player->weapon != NULL) {
							game->player->weapon->event_handler(game, game->player->weapon, game->player);
						}
					}
					// tout ceci devrait être inutile en théorie (a part pour les PNJ avec lesquels on peut intéragir)
					List* current = game->current_scene->entities;
					while (current != NULL) {
						Entity* e = (Entity*)current->value;
						e->event_handler(e, game);
						current = current->next;
						if (e->weapon != NULL) {
							e->weapon->event_handler(game, e->weapon, e);
						}
					}
				}
			}

			if (game->current_scene != NULL) {
				// update_entities(game->current_scene->entities);
				game->current_scene->update(game);

				if (game->player != NULL) {
					game->player->update(game, game->player, deltaT);
					if (game->player->weapon != NULL) {
						game->player->weapon->update(game, game->player, deltaT);
					}
				}

				List* current = game->current_scene->entities;
				while (current != NULL) {
					Entity* e = (Entity*)current->value;
					e->update(game, e, deltaT);
                    if (e->weapon != NULL) {
                        e->weapon->update(game, e, deltaT);
                    }
					current = current->next;
				}
			}

			clear_entities(game);

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

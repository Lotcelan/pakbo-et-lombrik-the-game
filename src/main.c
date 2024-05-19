#include "engine/include/entity.h"
#include "engine/include/game.h"
#include "engine/include/hud.h"
#include "engine/include/scenes.h"
#include "entities/canard01/canard01.h"
#include "entities/duck_orange/duck_orange.h"
#include "entities/duck_green/duck_green.h"
#include "entities/duck_blue/duck_blue.h"
#include "entities/la_mouche/la_mouche.h"
#include "entities/blue_canard_boss/blue_canard_boss.h"
#include "entities/player/player.h"
#include "entities/projectile_arrow/projectile_arrow.h"
#include "entities/projectile_laser/projectile_laser.h"
#include "entities/medic_hub/medic_hub.h"
#include "entities/wormcan/wormcan.h"
#include "resources.h"
#include "scenes/etagere_level/etagere_level.h"
#include "scenes/main_menu/main_menu.h"
#include "scenes/scene01/scene01.h"
#include "scenes/spawn_level/spawn_level.h"
#include "scenes/simple_arena/simple_arena.h"
#include "scenes/cafet_beginning/cafet_beginning.h"
#include "scenes/cafet_crossing_counters/cafet_crossing_counters.h"
#include "scenes/cafet_second_counter_beginning/cafet_second_counter_beginning.h"
#include "scenes/cafet_second_counter_end/cafet_second_counter_end.h"
#include "scenes/ping_pong/ping_pong.h"
#include "scenes/game_over/game_over.h"
#include "scenes/hub_level/hub_level.h"
#include "scenes/continue/continue.h"
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
	insert(game->weapons, "basic_sword", i_w, free);

	WeaponInitFunc* i_a = (WeaponInitFunc*)malloc(sizeof(WeaponInitFunc));
	*i_a = init_arbalete;
	insert(game->weapons, "arbalete", i_a, free);

    WeaponInitFunc* i_bdbl = (WeaponInitFunc*)malloc(sizeof(WeaponInitFunc));
    *i_bdbl = init_blue_duck_boss_laser;
    insert(game->weapons, "blue_duck_boss_laser", i_bdbl, free);

	// Init entities MUST DO IT BEFORE INIT SCENES
	EntityInitFunc* i_p = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_p = init_canard01;
	insert(game->entities, "canard01", i_p, free);

	EntityInitFunc* i_arrow = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_arrow = init_projectile_arrow;
	insert(game->entities, "projectile_arrow", i_arrow, free);

    EntityInitFunc* i_laser = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_laser = init_projectile_laser;
	insert(game->entities, "projectile_laser", i_laser, free);

    EntityInitFunc* i_bcb = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
    *i_bcb = init_blue_canard_boss;
    insert(game->entities, "blue_canard_boss", i_bcb, free);

	EntityInitFunc* i_medic_hub = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_medic_hub = init_medic_hub;
	insert(game->entities, "medic_hub", i_medic_hub, free);
	
	EntityInitFunc* i_duck_orange = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_duck_orange = init_duck_orange;
	insert(game->entities, "duck_orange", i_duck_orange, free);

	EntityInitFunc* i_duck_green = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_duck_green = init_duck_green;
	insert(game->entities, "duck_green", i_duck_green, free);

	EntityInitFunc* i_duck_blue = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_duck_blue = init_duck_blue;
	insert(game->entities, "duck_blue", i_duck_blue, free);

	EntityInitFunc* i_la_mouche = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*i_la_mouche = init_la_mouche;
	insert(game->entities, "la_mouche", i_la_mouche, free);

	EntityInitFunc* wormcan = (EntityInitFunc*)malloc(sizeof(EntityInitFunc));
	*wormcan = init_wormcan;
	insert(game->entities, "wormcan", wormcan, free);

	// potentiellement systeme de sauvegarde plus tard (donc init avec valeurs différentes)
	Entity* player = init_player(game, -1, -1);	 // -1 -1 convention pour dire que l'on ne l'affiche pas
	game->player = player;

	// Init scenes
	SceneInit* scene01 = (SceneInit*)malloc(sizeof(SceneInit));
	*scene01 = init_scene01;
	SceneInit* main_menu = (SceneInit*)malloc(sizeof(SceneInit));
	*main_menu = init_main_menu;
	SceneInit* spawn_level = (SceneInit*)malloc(sizeof(SceneInit));
	*spawn_level = init_spawn_level;
	SceneInit* etagere_level = (SceneInit*)malloc(sizeof(SceneInit));
	*etagere_level = init_etagere_level;
	SceneInit* simple_arena = (SceneInit*)malloc(sizeof(SceneInit));
	*simple_arena = init_simple_arena;
	SceneInit* hub_level = (SceneInit*)malloc(sizeof(SceneInit));
	*hub_level = init_hub_level;
	SceneInit* game_over = (SceneInit*)malloc(sizeof(SceneInit));
	*game_over = init_game_over;
	SceneInit* continue_scene = (SceneInit*)malloc(sizeof(SceneInit));
	*continue_scene = init_continue;
	SceneInit* ping_pong = (SceneInit*)malloc(sizeof(SceneInit));
	*ping_pong = init_ping_pong;
	SceneInit* cafet_beginning = (SceneInit*)malloc(sizeof(SceneInit));
	*cafet_beginning = init_cafet_beginning;
	SceneInit* cafet_crossing_counters = (SceneInit*)malloc(sizeof(SceneInit));
	*cafet_crossing_counters = init_cafet_crossing_counters;
	SceneInit* cafet_second_counter_beginning = (SceneInit*)malloc(sizeof(SceneInit));
	*cafet_second_counter_beginning = init_cafet_second_counter_beginning;
	SceneInit* cafet_second_counter_end = (SceneInit*)malloc(sizeof(SceneInit));
	*cafet_second_counter_end = init_cafet_second_counter_end;


	insert(game->scenes, "scene01", scene01, free);
	insert(game->scenes, "main_menu", main_menu, free);
	insert(game->scenes, "spawn_level", spawn_level, free);
	insert(game->scenes, "etagere_level", etagere_level, free);
    insert(game->scenes, "simple_arena", simple_arena, free);
	insert(game->scenes, "hub_level", hub_level, free);
	insert(game->scenes, "game_over", game_over, free);
	insert(game->scenes, "continue", continue_scene, free);
	insert(game->scenes, "ping_pong", ping_pong, free);
	insert(game->scenes, "cafet_beginning", cafet_beginning, free);
	insert(game->scenes, "cafet_crossing_counters", cafet_crossing_counters, free);
	insert(game->scenes, "cafet_second_counter_beginning", cafet_second_counter_beginning, free);
	insert(game->scenes, "cafet_second_counter_end", cafet_second_counter_end, free);

	change_scene(game, "main_menu_-1_-1");

	// Init fonts
	TTF_Font* font = TTF_OpenFont("../src/assets/Suifak.otf", 24);
	if (font == NULL) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return 0;
	}

	insert(game->fonts, "suifak", font, free); // avec destroy_font ca segfault ¯\_(ツ)_/¯

	font = TTF_OpenFont("../src/assets/Suifak.otf", 12);
	if (font == NULL) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return 0;
	}
	insert(game->fonts, "suifak_small", font, free); // avec destroy_font ca segfault ¯\_(ツ)_/¯

	font = TTF_OpenFont("../src/assets/MontserratThin.otf", 10);
	if (font == NULL) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		return 0;
	}
	insert(game->fonts, "monsterrat_thin_small", font, free); // avec destroy_font ca segfault ¯\_(ツ)_/¯

	/* Main loop :
		- Getting events
		- Updating the entities logic with the event
		- Updating the scene logic with the event
		- Render the scene (which also renders the entities)
	*/

	// Variables for deltaT between each loop
	int t0;
	t0 = SDL_GetTicks();
	int deltaT;

	while (game->state != CLOSING) {
		// Calculate deltaT and set t0 to the current time
		if (game->state == CHANGING) {
			game->state = RUNNING;
		}
		
		deltaT = SDL_GetTicks() - t0;
		game->deltaT = deltaT;
		t0 = SDL_GetTicks();

		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
		SDL_RenderClear(game->renderer);

		if (game->current_dialog == NULL) {
			// SECTION EVENT HANDLER

			while (SDL_PollEvent(&(game->event)) != 0) {
				if ((game->event).type == SDL_QUIT) {
					game->state = CLOSING;
				}
                SDL_PumpEvents();
				if (game->current_scene != NULL) {
					game->current_scene->event_handler(game);
					if (game->state == CHANGING) continue;

					if (game->player != NULL) {
						game->player->event_handler(game->player, game);
						if (game->state == CHANGING) continue;
						if (game->player->weapon != NULL) {
							game->player->weapon->event_handler(game, game->player->weapon, game->player);
							if (game->state == CHANGING) continue;
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
							if (game->state == CHANGING) continue;
						}
					}
				}
			}

			// SECTION UPDATE
			if (game->current_scene != NULL) {
				// update_entities(game->current_scene->entities);
				game->current_scene->update(game);
				update_modifiers(game);
				if (game->state == CHANGING) continue;
				if (game->player != NULL) {
					game->player->update(game, game->player, deltaT);
					if (game->player->weapon != NULL) {
						game->player->weapon->update(game, game->player, deltaT);
						if (game->state == CHANGING) continue;
					}
				}

				List* current = game->current_scene->entities;
				while (current != NULL) {
					Entity* e = (Entity*)current->value;
					e->update(game, e, deltaT);
					if (game->state == CHANGING) continue;
                    if (e->weapon != NULL) {
                        e->weapon->update(game, e, deltaT);
						if (game->state == CHANGING) continue;
                    }
					current = current->next;
				}
			}

			clear_entities(game); // removes <= 0 hp entities

			render_scene(game, deltaT);
			render_hud(game);

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
		
		// Afficher
		SDL_RenderPresent(game->renderer);
		cap_fps(game->frm);
	}

	free_game(game);
	SDL_Quit();

	return 0;
}

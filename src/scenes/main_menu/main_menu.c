#include "main_menu.h"

#define NUM_MENU_ITEMS 3
// #define MAIN_MENU_OPTIONS ("Play", "Options", "Quit")

void event_handler_main_menu(GameData* game) {
    int* selectedMenuItem = get(game->current_scene->objects, "selectedMenuItem", strcmp);
    const char *main_menu_options[] = {"Play", "Options", "Quit"};
    SDL_Rect* menuItemsRect;
    SDL_Point point;
    switch (game->event.type) {
        case SDL_MOUSEMOTION:
            if (selectedMenuItem == NULL) {
                // printf("selectedMenuItem is NULL\n");
                exit(-1);
            }
            menuItemsRect = get(game->current_scene->objects, "menuItemsRect", strcmp);
            if (menuItemsRect == NULL) {
                printf("menuItemsRect is NULL\n");
                exit(-1);
            }
            *selectedMenuItem = -1;
            for (int i = 0; i < NUM_MENU_ITEMS; i++) {
                point.x = game->event.motion.x;
                point.y = game->event.motion.y;
                // printf("x: %d, y: %d\n", game->event.motion.x, game->event.motion.y);
                if (SDL_PointInRect(&point, &menuItemsRect[i])) {
                    *selectedMenuItem = i;
                    break;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (selectedMenuItem == NULL) {
                printf("selectedMenuItem is NULL\n");
                exit(-1);
            }
            
            if (*selectedMenuItem != -1) {
                // printf("Clicked: %s\n", menuItems[selectedMenuItem].name);
                if (strcmp(main_menu_options[*selectedMenuItem], "Play")==0) {
                    // game->current_scene = get(game->scenes, "spawn_level", strcmp);
                    game->player->y_velocity = 0;

                    //change_scene(game, "cafet_beginning_2_4");
                    //change_scene(game, "first_boss_room_7_6");

                    //change_scene(game, "ping_pong_1_4");
                    // change_scene(game, "cafet_ping_pong_beginning_0_3");
                    // change_scene(game, "cafet_second_counter_end_0_3");

                    change_scene(game, "cave_0_6");

                    return;
                } else if (strcmp(main_menu_options[*selectedMenuItem], "Quit")==0) {
                    game->state = CLOSING;
                }
            }
            break;
        default:
            break;
    }

}

void update_main_menu(GameData* game) {
    const char *main_menu_options[] = {"Play", "Options", "Quit"};
    if (game->current_scene->objects == NULL) {
        printf("objects is NULL\n");
        exit(-1);
    }

    int* selectedMenuItem = (int*)get(game->current_scene->objects, "selectedMenuItem", strcmp);
    if (selectedMenuItem == NULL) {
        printf("selectedMenuItem is NULL\n");
        exit(-1);
    }
    // Render menu items
    for (int i = 0; i < NUM_MENU_ITEMS; i++) {

        SDL_Rect* menuItemsRect = get(game->current_scene->objects, "menuItemsRect", strcmp);
        if (menuItemsRect == NULL) {
            printf("menuItemsRect is NULL\n");
            exit(-1);
        }
        // printf("%d = selectedMenuItem\n", *selectedMenuItem);

        if (i == *selectedMenuItem) {
            // SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
            // push_render_stack_rect(game, menuItems[i].rect);
            // SDL_RenderDrawRect(game->renderer, &menuItems[i].rect);
            Rectangle* rect = init_rectangle(menuItemsRect[i].x, menuItemsRect[i].y, menuItemsRect[i].w, menuItemsRect[i].h, (SDL_Color){255, 0, 0, 0}, (SDL_Color){0, 0, 0, 0});
            push_render_stack_rect(game, rect, true);
        }  else {
            Rectangle* rect = init_rectangle(menuItemsRect[i].x, menuItemsRect[i].y, menuItemsRect[i].w, menuItemsRect[i].h, (SDL_Color){0, 0, 0, 0}, (SDL_Color){0, 0, 0, 0});
            push_render_stack_rect(game, rect, true);
        }


        Text* text = init_text(game, main_menu_options[i], (SDL_Color){255, 255, 255, (int)SDL_GetTicks() % 256}, 50, 10 + i*40, get(game->fonts, "suifak", strcmp));        
        push_render_stack_text(game, text, true);
    

        // SDL_Color textColor = {(int)SDL_GetTicks() % 256, (((int)SDL_GetTicks() % 256) + 50) % 256, ((2*(int)SDL_GetTicks() % 256) + 100) % 256, 255};
        
        // Text* text = init_text(game, menuItems[i].name, textColor, menuItems[i].rect.x + 10, menuItems[i].rect.y + 10, get(game->fonts, "main_menu", strcmp));
        // push_render_stack_text(game, text);

        // SDL_Surface* textSurface = TTF_RenderText_Solid(get(game->fonts, "main_menu", strcmp), menuItems[i].name, textColor);
        // SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
        // SDL_Rect textRect = {menuItems[i].rect.x + 10, menuItems[i].rect.y + 10, textSurface->w, textSurface->h};
        // SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);

        // SDL_FreeSurface(textSurface);
        // SDL_DestroyTexture(textTexture);
    }
    
}

void populate(GameData* game) {

    push_background_structures(game);
    change_entity_coordinates(game->player, -1, -1);
    int* selectedMenuItem = malloc(sizeof(int));
    *selectedMenuItem = -1;
    Scene* scene = game->current_scene;

    insert(scene->objects, "selectedMenuItem", selectedMenuItem, free);
    
    SDL_Rect* menuItemsRect = (SDL_Rect*)malloc(sizeof(SDL_Rect) * NUM_MENU_ITEMS);
    menuItemsRect[0] = (SDL_Rect){ .x = 50, .y = 10, .w = 100, .h = 30 };
    menuItemsRect[1] = (SDL_Rect){ .x = 50, .y = 50, .w = 100, .h = 30 };
    menuItemsRect[2] = (SDL_Rect){ .x = 50, .y = 90, .w = 100, .h = 30 };

    insert(scene->objects, "menuItemsRect", menuItemsRect, free);

    // Text** menuItemsText = (Text**)malloc(sizeof(Text*) * NUM_MENU_ITEMS);
    // if (menuItemsText == NULL) {
    //     exit(-1);
    // }
    // menuItemsText[0] = init_text(game, "Play", (SDL_Color){255, 255, 255, 255}, 50, 50, get(game->fonts, "main_menu", strcmp));
    // menuItemsText[1] = init_text(game, "Options", (SDL_Color){255, 255, 255, 255}, 50, 110, get(game->fonts, "main_menu", strcmp));
    // menuItemsText[2] = init_text(game, "Quit", (SDL_Color){255, 255, 255, 255}, 50, 170, get(game->fonts, "main_menu", strcmp));

    // push_render_stack_text(game, menuItemsText[0]);
    // push_render_stack_text(game, menuItemsText[1]);
    // push_render_stack_text(game, menuItemsText[2]);

}

Scene* init_main_menu(GameData* game) {
    Scene* scene = init_scene(game, "main_menu");
    scene->update = update_main_menu;
    scene->event_handler = event_handler_main_menu;
    scene->populate = populate;

    return scene;
}

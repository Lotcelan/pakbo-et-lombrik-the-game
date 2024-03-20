#include "main_menu.h"

#define NUM_MENU_ITEMS 3



void event_handler_main_menu(GameData* game) {
    int* selectedMenuItem = get(game->current_scene->objects, "selectedMenuItem", strcmp);
    switch (game->event.type) {
        case SDL_MOUSEMOTION:
            if (selectedMenuItem == NULL) {
                printf("selectedMenuItem is NULL\n");
                exit(-1);
            }
            Rectangle** menuItemsRect = get(game->current_scene->objects, "menuItemsRect", strcmp);
            if (menuItemsRect == NULL) {
                printf("menuItemsRect is NULL\n");
                exit(-1);
            }
            *selectedMenuItem = -1;
            for (int i = 0; i < NUM_MENU_ITEMS; i++) {
                SDL_Point point = {game->event.motion.x, game->event.motion.y};
                printf("x: %d, y: %d\n", game->event.motion.x, game->event.motion.y);
                SDL_Rect hitbox = {menuItemsRect[i]->x, menuItemsRect[i]->y, menuItemsRect[i]->w, menuItemsRect[i]->h};
                if (SDL_PointInRect(&point, &hitbox)) {
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
            Text** menuItemsText = get(game->current_scene->objects, "menuItemsText", strcmp);
            if (menuItemsText == NULL) {
                printf("menuItemsText is NULL\n");
                exit(-1);
            }
            if (*selectedMenuItem != -1) {
                // printf("Clicked: %s\n", menuItems[selectedMenuItem].name);
                if (menuItemsText[*selectedMenuItem]->text == "Play") {
                    // game->current_scene = get(game->scenes, "spawn_level", strcmp);
                    change_scene(game, "spawn_level");
                } else if (menuItemsText[*selectedMenuItem]->text == "Quit") {
                    game->state = CLOSING;
                }
            }
            break;
        default:
            break;
    }

}

void update_main_menu(GameData* game) {
    
    if (game->current_scene->objects == NULL) {
        printf("objects is NULL\n");
        exit(-1);
    }

    int* selectedMenuItem = (int*)get(((Scene*)get(game->scenes, "main_menu", strcmp))->objects, "selectedMenuItem", strcmp);
    if (selectedMenuItem == NULL) {
        printf("selectedMenuItem is NULL\n");
        exit(-1);
    }
    // Render menu items
    for (int i = 0; i < NUM_MENU_ITEMS; i++) {

        Rectangle** menuItemsRect = get(game->current_scene->objects, "menuItemsRect", strcmp);
        if (menuItemsRect == NULL) {
            printf("menuItemsRect is NULL\n");
            exit(-1);
        }
        printf("%d = selectedMenuItem\n", *selectedMenuItem);

        if (i == *selectedMenuItem) {
            // SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
            // push_render_stack_rect(game, menuItems[i].rect);
            // SDL_RenderDrawRect(game->renderer, &menuItems[i].rect);
            menuItemsRect[i]->outline_color = (SDL_Color){255, 0, 0, 255};
            push_render_stack_rect(game, menuItemsRect[i], true);
        }  else {
            menuItemsRect[i]->outline_color = (SDL_Color){0, 0, 0, 255};
            push_render_stack_rect(game, menuItemsRect[i], true);
        }

        Text** menuItemsText = get(game->current_scene->objects, "menuItemsText", strcmp);
        if (menuItemsText == NULL) {
            printf("menuItemsText is NULL\n");
            exit(-1);
        }

        push_render_stack_text(game, menuItemsText[0], true);
        push_render_stack_text(game, menuItemsText[1], true);
        push_render_stack_text(game, menuItemsText[2], true);

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


    TTF_Font* font = TTF_OpenFont("../src/assets/Suifak.otf", 24);
    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return NULL;
    }

    insert(game->fonts, "main_menu", font);

    int* selectedMenuItem = malloc(sizeof(int));
    *selectedMenuItem = -1;
    insert(scene->objects, "selectedMenuItem", selectedMenuItem);


    Text** menuItemsText = (Text**)malloc(sizeof(Text*) * NUM_MENU_ITEMS);
    menuItemsText[0] = init_text(game, "Play", (SDL_Color){255, 255, 255, 255}, 50, 50, get(game->fonts, "main_menu", strcmp));
    menuItemsText[1] = init_text(game, "Options", (SDL_Color){255, 255, 255, 255}, 50, 110, get(game->fonts, "main_menu", strcmp));
    menuItemsText[2] = init_text(game, "Quit", (SDL_Color){255, 255, 255, 255}, 50, 170, get(game->fonts, "main_menu", strcmp));

    insert(scene->objects, "menuItemsText", menuItemsText);
    
    Rectangle** menuItemsRect = (Rectangle**)malloc(sizeof(Rectangle*) * NUM_MENU_ITEMS);
    menuItemsRect[0] = init_rectangle(50, 50, 100, 50, (SDL_Color){75, 0, 0, 0}, (SDL_Color){0, 0, 75, 255});
    menuItemsRect[1] = init_rectangle(50, 110, 100, 50, (SDL_Color){0, 0, 0, 0}, (SDL_Color){0, 0, 0, 255});
    menuItemsRect[2] = init_rectangle(50, 170, 100, 50, (SDL_Color){0, 0, 0, 0}, (SDL_Color){0, 0, 0, 255});

    insert(scene->objects, "menuItemsRect", menuItemsRect);

    return scene;
}

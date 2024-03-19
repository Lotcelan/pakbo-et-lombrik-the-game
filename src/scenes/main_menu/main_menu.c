#include "main_menu.h"

typedef struct {
    const char* name;
    SDL_Rect rect;
} MenuItem;

#define NUM_MENU_ITEMS 3

MenuItem menuItems[NUM_MENU_ITEMS] = {
    {"Play", {50, 50, 125, 50}},
    {"Options", {50, 110, 125, 50}},
    {"Quit", {50, 170, 125, 50}}
};

int selectedMenuItem = -1;

void event_handler_main_menu(GameData* game) {
    switch (game->event.type) {
        case SDL_MOUSEMOTION:
            selectedMenuItem = -1;
            for (int i = 0; i < NUM_MENU_ITEMS; i++) {
                SDL_Point point = {game->event.motion.x, game->event.motion.y};
                printf("x: %d, y: %d\n", game->event.motion.x, game->event.motion.y);
                if (SDL_PointInRect(&point, &menuItems[i].rect)) {
                    selectedMenuItem = i;
                    break;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (selectedMenuItem != -1) {
                // printf("Clicked: %s\n", menuItems[selectedMenuItem].name);
                if (menuItems[selectedMenuItem].name == "Play") {
                    game->current_scene = get(game->scenes, "spawn_level", strcmp);
                } else if (menuItems[selectedMenuItem].name == "Quit") {
                    game->state = CLOSING;
                }
            }
            break;
        default:
            break;
    }

}

void update_main_menu(GameData* game) {
    
    // Render menu items
    for (int i = 0; i < NUM_MENU_ITEMS; i++) {
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &menuItems[i].rect);

        if (i == selectedMenuItem) {
            SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(game->renderer, &menuItems[i].rect);
        }

        SDL_Color textColor = {(int)SDL_GetTicks() % 256, (((int)SDL_GetTicks() % 256) + 50) % 256, ((2*(int)SDL_GetTicks() % 256) + 100) % 256, 255};
        

        SDL_Surface* textSurface = TTF_RenderText_Solid(get(game->fonts, "main_menu", strcmp), menuItems[i].name, textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
        SDL_Rect textRect = {menuItems[i].rect.x + 10, menuItems[i].rect.y + 10, textSurface->w, textSurface->h};
        SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
    
}

Scene* init_main_menu(GameData* game) {
    Scene* scene = init_scene(game, "main_menu");
    scene->update = update_main_menu;
    scene->event_handler = event_handler_main_menu;

    TTF_Font* font = TTF_OpenFont("../src/assets/Suifak.otf", 24);
    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return NULL;
    }

    insert(game->fonts, "main_menu", font);

    return scene;
}

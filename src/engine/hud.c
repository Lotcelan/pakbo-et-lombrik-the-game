#include "include/hud.h"

void render_hud(GameData* game) {
    // Render user health bar
    int amount_of_full = game->player->current_hp / 2;
    int amount_of_half = game->player->current_hp % 2;
    int amount_of_empty = (game->player->max_hp - game->player->current_hp) / 2;
    SDL_Texture* full = loadTextureFromMemory(game, "src_assets_hp_full");
    SDL_Texture* half = loadTextureFromMemory(game, "src_assets_hp_half");
    SDL_Texture* empty = loadTextureFromMemory(game, "src_assets_hp_dead");

    for (int i = 0; i < amount_of_full; i++) {
        SDL_Rect src = {0, 0, 16, 16}; // potentiellement à ne rendre plus hardcodé
        SDL_Rect dest = {i * 16, 0, 16, 16};
        SDL_RenderCopy(game->renderer, full, &src, &dest);
    }
    for (int i = 0; i < amount_of_half; i++) {
        SDL_Rect src = {0, 0, 16, 16}; // potentiellement à ne rendre plus hardcodé
        SDL_Rect dest = {(amount_of_full + i) * 16, 0, 16, 16};
        SDL_RenderCopy(game->renderer, half, &src, &dest);
    }
    for (int i = 0; i < amount_of_empty; i++) {
        SDL_Rect src = {0, 0, 16, 16}; // potentiellement à ne rendre plus hardcodé
        SDL_Rect dest = {(amount_of_full + amount_of_half + i) * 16, 0, 16, 16};
        SDL_RenderCopy(game->renderer, empty, &src, &dest);
    }
    return;
}
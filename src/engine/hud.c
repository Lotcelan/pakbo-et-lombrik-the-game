#include "include/hud.h"

void render_hud(GameData* game) {
    if (game->player == NULL) return;
    if (game->player->x_position == -1 && game->player->y_position == -1) return;
    
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


    // Affichage des effets
    List* modif = game->player->modifiers;
    int x = game->width_amount * CELL_WIDTH - 12;
    int y = 4;
    int amount = 0;
    while (modif != NULL) {
        amount++;
        Modifier* m = (Modifier*)(modif->value);
        if (!is_modifier_name_effect(m->name)) {
            modif = modif->next;
            continue;
        }
        Texture* t = modifier_name_to_texture(game, m->name, x, y);
        t->dstRect->w = 8; // on supp que la c'est que du 16x16, sinon c relou
        t->dstRect->h = 8;
        
        render_texture(game, t);
        free_texture(t);


        char text[10];
        sprintf(text, "%d", m->quantity);

        Text* te = init_text(game, text, (SDL_Color){255, 255, 255, 255}, x+2, y+2, (TTF_Font*)get(game->fonts, "monsterrat_thin_small", strcmp));
        render_text(game, te);
        free_text(te);

        x -= 12;
        if (amount >= 10) {
            amount = 0;
            x = game->width_amount * CELL_WIDTH - 12;
            y += 12;
        }

        modif = modif->next;
    }

    // Affichage des affects
    modif = game->player->modifiers;
    x = 4;
    y = CELL_HEIGHT + 4; // y'a deja les pts de vie
    amount = 0;
    while (modif != NULL) {
        amount++;
        Modifier* m = (Modifier*)(modif->value);
        if (is_modifier_name_effect(m->name)) {
            modif = modif->next;
            continue;
        }
        Texture* t = modifier_name_to_texture(game, m->name, x, y);
        t->dstRect->w = 8; // on supp que la c'est que du 16x16, sinon c relou
        t->dstRect->h = 8;
        
        render_texture(game, t);
        free_texture(t);


        char text[10];
        sprintf(text, "%d", m->quantity);

        Text* te = init_text(game, text, (SDL_Color){255, 255, 255, 255}, x+2, y+2, (TTF_Font*)get(game->fonts, "monsterrat_thin_small", strcmp));
        render_text(game, te);
        free_text(te);

        x += 12;
        if (amount >= 10) {
            amount = 0;
            x = 4;
            y += 12;
        }

        modif = modif->next;
    }
    return;
}
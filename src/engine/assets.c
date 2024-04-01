#include "include/assets.h"

SDL_Texture* loadTextureFromMemory(GameData* game, const char* resource) {
    // Load texture from memory
    // displayHashTableResource(game->resources);
    MemTexture* resource_texture = (MemTexture*)get(game->resources, resource, &strcmp);
    if (resource_texture == NULL) {
        printf("Resource not found: %s\n", resource);
        return NULL;
    }
    SDL_RWops* rw = SDL_RWFromMem(resource_texture->data, resource_texture->size);
    SDL_Surface* surface = IMG_Load_RW(rw, 1);
    if (!surface) {
        printf("Unable to create surface from memory: %s\n", IMG_GetError());
        return NULL;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Unable to create texture from surface: %s\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

void render_texture(GameData* game, void* key) {

    Texture* texture = (Texture*)key;
    if (texture == NULL) {
        printf("Texture is NULL\n");
        return;
    }

    SDL_RenderCopy(game->renderer, texture->texture, texture->srcRect, texture->dstRect);
}

void render_structure(GameData* game, void* key) {
    Structure* structure = (Structure*)key;

    SDL_RenderCopy(game->renderer, structure->texture, NULL, &structure->position);
}

void render_text(GameData* game, void* key) {
    Text* text = (Text*)key;
    SDL_RenderCopy(game->renderer, text->texture, NULL, &text->position);
}

void render_wrap_text(GameData* game, void* key, int wrap_length) {
    Text* text = (Text*)key;
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(text->font, text->text, text->color, wrap_length);
    if (textSurface == NULL) {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
        return;
    }
    text->texture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    if (text->texture == NULL) {
        printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        return;
    }
    SDL_QueryTexture(text->texture, NULL, NULL, &text->position.w, &text->position.h);

    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(game->renderer, text->texture, NULL, &text->position);
}

void render_rectangle(GameData* game, void* key) {
    Rectangle* rect = (Rectangle*)key;
    SDL_SetRenderDrawColor(game->renderer, rect->fill_color.r, rect->fill_color.g, rect->fill_color.b, rect->fill_color.a);
    SDL_Rect fillRect = {rect->x, rect->y, rect->w, rect->h};
    SDL_RenderFillRect(game->renderer, &fillRect);
    SDL_SetRenderDrawColor(game->renderer, rect->outline_color.r, rect->outline_color.g, rect->outline_color.b, rect->outline_color.a);
    SDL_Rect outlineRect = {rect->x, rect->y, rect->w, rect->h};
    SDL_RenderDrawRect(game->renderer, &outlineRect);
}

void push_render_stack(GameData* game, void* key, void (*render)(GameData*, void*), void (*destroy)(void*), bool is_temporary) {
    RenderEntry* entry = (RenderEntry*)malloc(sizeof(RenderEntry));
    if (entry == NULL) {
        exit(-1);
    }
    entry->key = key;
    entry->render = render;
    entry->is_temporary = is_temporary;
    entry->destroy = destroy;

    // Assume the push does not add an entry if element is already in the list
    List* current = game->current_scene->render_stack;
    while (current != NULL) {
        RenderEntry* current_entry = (RenderEntry*)(current->value);
        if (current_entry != NULL) {
            if (current_entry->key == key) {
                return;
            }
        }
        current = current->next;
    }

    game->current_scene->render_stack = append_end(entry, game->current_scene->render_stack);
}


Text* init_text(GameData* game, const char* text, SDL_Color color, int x, int y, TTF_Font* font) {
    Text* t = (Text*)malloc(sizeof(Text));
    if (t == NULL) {
        exit(-1);
    }
    t->text = text;
    t->color = color;
    t->position.x = x;
    t->position.y = y;
    t->font = font;

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface == NULL) {
        printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
        return NULL;
    }
    t->texture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    if (t->texture == NULL) {
        printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_QueryTexture(t->texture, NULL, NULL, &t->position.w, &t->position.h);

    SDL_FreeSurface(textSurface);
    return t;
}

void free_text(void* t) {
    Text* t2 = (Text*)t;
    if (t2->texture != NULL) {
        SDL_DestroyTexture(t2->texture);
        free(t2);
    }
}

Structure* init_structure(GameData* game, const char* identifier, const char* resource, int x, int y, int allow_pass_through, const char* teleport_to_scene) {
    Structure* s = (Structure*)malloc(sizeof(Structure));
    if (s == NULL) {
        exit(-1);
    }
    s->identifier = identifier;
    s->texture = loadTextureFromMemory(game, resource);
    s->position.x = x * CELL_WIDTH;
    s->position.y = y * CELL_HEIGHT;
    SDL_QueryTexture(s->texture, NULL, NULL, &s->position.w, &s->position.h);

    s->allow_pass_through = allow_pass_through;
    s->teleport_to_scene = teleport_to_scene;
    return s;
}

void free_structure(void* s) {
    Structure* s2 = (Structure*)s;
    SDL_DestroyTexture(s2->texture);
    free(s2);
}


Rectangle* init_rectangle(int x, int y, int w, int h, SDL_Color outline_color, SDL_Color fill_color) {
    Rectangle* r = (Rectangle*)malloc(sizeof(Rectangle));
    if (r == NULL) {
        exit(-1);
    }
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    r->outline_color = outline_color;
    r->fill_color = fill_color;
    return r;
}

void free_rectangle(void* r) {
    free(r);
}

Texture* init_texture_from_memory(GameData* game, char* name, int x, int y) {
    Texture* t = (Texture*)malloc(sizeof(Texture));
    if (t == NULL) {
        exit(-1);
    }
    t->name = name;
    t->texture = loadTextureFromMemory(game, name);
    t->srcRect = NULL; // Could be changed later
    SDL_Rect* dstRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    if (dstRect == NULL) {
        exit(-1);
    }
    dstRect->x = x;
    dstRect->y = y;
    SDL_QueryTexture(t->texture, NULL, NULL, &dstRect->w, &dstRect->h);
    t->dstRect = dstRect;
    return t;
}

void free_texture(void* t) {
    Texture* t2 = (Texture*)t;
    SDL_DestroyTexture(t2->texture);
    free(t2->dstRect);
    free(t2);
}

void push_render_stack_text(GameData* game, Text* text, bool is_temporary) {
    push_render_stack(game, text, render_text, free_text, is_temporary);
}

void push_render_stack_structure(GameData* game, Structure* structure, bool is_temporary) {
    push_render_stack(game, structure, render_structure, free_structure, is_temporary);
}

void push_render_stack_texture(GameData* game, Texture* texture, bool is_temporary) {
    push_render_stack(game, texture, render_texture, free_texture, is_temporary);
}

void push_render_stack_rect(GameData* game, Rectangle* rect, bool is_temporary) {
    push_render_stack(game, rect, render_rectangle, free_rectangle, is_temporary);
}

void render_stack(GameData* game) {
    if (game == NULL) {
        printf("Game is NULL WTFFFFF\n");
        return;
    }
    if (game->current_scene != NULL) {
        List* current = game->current_scene->render_stack;
        List* prev = NULL;
        while (current != NULL) {
            ((RenderEntry*)current->value)->render(game, ((RenderEntry*)current->value)->key);
            if ( ((RenderEntry*)current->value)->is_temporary ) {
                List* temp = current;
                if (prev == NULL) {
                    game->current_scene->render_stack = current->next;
                    prev = game->current_scene->render_stack;
                } else {
                    prev->next = current->next;
                }
                current = current->next;
                ((RenderEntry*)temp->value)->destroy(((RenderEntry*)temp->value)->key);
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
    return;
}

void render_no_destroy(GameData* game) {
    if (game->current_scene != NULL) {
        List* current = game->current_scene->render_stack;
        while (current != NULL) {
            ((RenderEntry*)current->value)->render(game, ((RenderEntry*)current->value)->key);
            current = current->next;
        }
    }
    return;
}

void destroy_render_stack(GameData* game) {
    if (game->current_scene != NULL) {
        List* current = game->current_scene->render_stack;
        while (current != NULL) {
            List* temp = current;
            current = current->next;
            ((RenderEntry*)temp->value)->destroy(((RenderEntry*)temp->value)->key);
        }
    }
    return;
}

void push_background_structures(GameData* game) {
    Texture* background = init_texture_from_memory(game, game->current_scene->background, 0, 0);
    push_render_stack_texture(game, background, false);

    List* current = game->current_scene->structures;
    while (current != NULL) {
        push_render_stack_structure(game, (Structure*)current->value, false);
        current = current->next;
    }

}

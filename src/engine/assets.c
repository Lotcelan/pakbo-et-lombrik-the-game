#include "include/assets.h"

SDL_Texture* loadTextureFromMemory(GameData* game, const char* resource) {
    // Load texture from memory (using the resource.c/h files)
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

void render_scene_modifier(GameData* game, void* key) {
    if (key == NULL) return;
    SceneModifier* m = (SceneModifier*)key;
    if (m->modifier == NULL) return;
    Texture* t = modifier_name_to_texture(game, m->modifier->name, m->x * CELL_WIDTH + 2, m->y * CELL_HEIGHT + 2 + floor(50 * (sin(2 * 3.14 * SDL_GetTicks() / 1000))) / 20);
    t->dstRect->w = 12;
    t->dstRect->h = 12;
    render_texture(game, t);
}

void render_texture(GameData* game, void* key) {

    // printf("Rendering texture %s\n", ((Texture*)key)->name);

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

    // Rectangle* collision = init_rectangle(structure->collision_box->zone.x, structure->collision_box->zone.y, structure->collision_box->zone.w, structure->collision_box->zone.h, (SDL_Color){0, 255, 0, 255}, (SDL_Color){0, 0, 0, 0});
    // render_rectangle(game, collision);
}


void render_text(GameData* game, void* key) {
    Text* text = (Text*)key;
    SDL_RenderCopy(game->renderer, text->texture, NULL, &text->position);
}

void render_circle(GameData* game, void* key) {
    Circle* circle = (Circle*)key;
    int radius = circle->radius;
    int x = circle->x;
    int y = circle->y;
    SDL_Color color = circle->color;
    for (int i = 0; i < radius; i++) {
        for (int j = 0; j < radius; j++) {
            if (i*i + j*j < radius*radius) {
                SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, color.a);
                SDL_RenderDrawPoint(game->renderer, x + i, y + j);
                SDL_RenderDrawPoint(game->renderer, x - i, y + j);
                SDL_RenderDrawPoint(game->renderer, x + i, y - j);
                SDL_RenderDrawPoint(game->renderer, x - i, y - j);
            }
        }
    }
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

void render_entity(GameData* game, Entity* e, float delta) {
    // je sais ca peut paraitre bizarre de le faire ici, mais finalement ca fait sens
    if (e == game->player) {
        // printf("Delay : %d\n", e->damage_delay);
    }
    if (e->damage_delay >= 0){
        e->damage_delay -= delta;
    }
    if (e->stagger_duration >= 0){
        e->stagger_duration -= delta;
    }
    
    Sprite* sprite;

    sprite = get_sprite(e);
    // si on peut (l'animation n'est pas lock -- voir sprite.Lock) on met a jour l'animation de l'entité, en général :
    // soit on change l'état de e en fonction de conditions relatives à l'entité e en question
    // soit (si on n'a pas changé d'etat) on met a jour le sprite de e (le timer notamment)
    if (sprite->Lock > 0){
        sprite->Lock -= 1;
        update_frame(e, delta);
    }
    else{
        int etat_old = e->etat;
        e->update_animation(e, delta);
        sprite->Lock = sprite->Lock_liste[e->etat];
        // printf("old : etat : %d for width %d and height %d\n", etat_old, e->etat, sprite->width, sprite->height);
        if (e->etat == etat_old){
            update_frame(e, delta);
        }
        else{
            e->sprite->currentFrame = e->sprite->frames[e->etat];
        }
    }

    // zone de la sprite sheet à afficher
    // rappel : sprite->frames est une liste de coordonnées
    if (!e->sprite) return;
    int* frame = e->sprite->currentFrame->value;    // tableau de taille 2 : [x, y]
    // printf("\n\n%d, %d\n\n", frame[0], frame[1]);
    SDL_Rect spriteRect = {.x = frame[0]*sprite->width, .y = frame[1]*sprite->height, .w = sprite->width, .h = sprite->height};
    // position du sprite à l'écran
    SDL_Rect destRect = {.x = e->x_position, .y = e->y_position, .w = sprite->width, .h = sprite->height};
    
    // On applique un effet de transparence sinusoidal si il y a une récupération damage delay :
    if (e->damage_delay > 0){
        int alpha = 255 * (1 + (sin(2*3.1415*50 + SDL_GetTicks()) >= 0 ? 1 : -1));
        SDL_SetTextureAlphaMod(sprite->spriteSheet, alpha);
    }
    else{
        SDL_SetTextureAlphaMod(sprite->spriteSheet, 255);
    }

    // On affiche la bonne frame au bon endroit
    SDL_RenderCopyEx(game->renderer, sprite->spriteSheet, &spriteRect, &destRect, 0, NULL, sprite->orientation);

    // // Render the collision box in green
    // if (e->hit_box != NULL) {
    //     Rectangle* hitbox_rectangle = init_rectangle(e->hit_box->zone.x, e->hit_box->zone.y, e->hit_box->zone.w, e->hit_box->zone.h, (SDL_Color){0, 0, 255, 255}, (SDL_Color){0, 0, 0, 0});
    //     // printf("Hitbox rectangle : %d %d %d %d\n", hitbox_rectangle->x, hitbox_rectangle->y, hitbox_rectangle->w, hitbox_rectangle->h);
    //     render_rectangle(game, hitbox_rectangle);
    //     free(hitbox_rectangle);
    // }
    // Rectangle* collision_rectangle = init_rectangle(e->collision_box->zone.x, e->collision_box->zone.y, e->collision_box->zone.w, e->collision_box->zone.h, (SDL_Color){0, 255, 0, 255}, (SDL_Color){0, 0, 0, 0});
    // render_rectangle(game, collision_rectangle);
    // free(collision_rectangle);
    // if (e->hurt_box != NULL) {
    //     Rectangle* hurtbox = init_rectangle(e->hurt_box->zone.x, e->hurt_box->zone.y, e->hurt_box->zone.w, e->hurt_box->zone.h, (SDL_Color){255, 0, 0, 255}, (SDL_Color){0, 0, 0, 0});
    //     render_rectangle(game, hurtbox);
    //     free(hurtbox);
    // }

    render_weapon(game, e, delta);
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

Circle* init_circle(int x, int y, int radius, SDL_Color color) {
    Circle* c = (Circle*)malloc(sizeof(Circle));
    if (c == NULL) {
        exit(-1);
    }
    c->x = x;
    c->y = y;
    c->radius = radius;
    c->color = color;
    return c;

}

Structure* init_structure(GameData* game, const char* identifier, const char* resource, int x, int y, int allow_pass_through, const char* teleport_to_scene) {
    Structure* s = (Structure*)malloc(sizeof(Structure));
    if (s == NULL) {
        exit(-1);
    }

    s->identifier = strdup(identifier);
    s->texture = loadTextureFromMemory(game, resource);
    s->position.x = x * CELL_WIDTH;
    s->position.y = y * CELL_HEIGHT;
    SDL_QueryTexture(s->texture, NULL, NULL, &s->position.w, &s->position.h);

    s->allow_pass_through = allow_pass_through;
    s->teleport_to_scene = strdup(teleport_to_scene);
    s->collision_box = NULL;

    s->collision_box = init_rect_box_from_structure(game, s);
    // printf("initialized coll box : %d %d %d %d\n", s->collision_box->zone.x, s->collision_box->zone.y, s->collision_box->zone.w, s->collision_box->zone.h);
    return s;
}

void free_structure(void* s) {
    if (s == NULL) {
        return;
    }
    Structure* s2 = (Structure*)s;
    SDL_DestroyTexture(s2->texture);
    free_box(s2->collision_box);
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

void free_circle(void* c) {
    free(c);
}

void push_render_stack_scene_modifier(GameData* game, SceneModifier* sm, bool is_temporary) {
    push_render_stack(game, sm, render_scene_modifier, destroy_scene_modifier, is_temporary);
}

void push_render_stack_text(GameData* game, Text* text, bool is_temporary) {
    push_render_stack(game, text, render_text, free_text, is_temporary);
}

void push_render_stack_circle(GameData* game, Circle* circle, bool is_temporary) {
    push_render_stack(game, circle, render_circle, free_circle, is_temporary);
}

void push_render_stack_structure(GameData* game, Structure* structure, bool is_temporary) {
    push_render_stack(game, structure, render_structure, free_structure, is_temporary);

    // for debug
    // Rectangle* collision_rectangle = init_rectangle(structure->collision_box->zone.x, structure->collision_box->zone.y, structure->collision_box->zone.w, structure->collision_box->zone.h, (SDL_Color){255, 0, 0, 255}, (SDL_Color){0, 0, 0, 0});
    // push_render_stack_rect(game, collision_rectangle, is_temporary);
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
            if (((RenderEntry*)temp->value)->destroy != NULL) {
                ((RenderEntry*)temp->value)->destroy(((RenderEntry*)temp->value)->key);
            }
        }
        game->current_scene->render_stack = NULL;

    }
    return;
}

void push_background_structures(GameData* game) {
    Texture* background = init_texture_from_memory(game, game->current_scene->background, 0, 0);
    push_render_stack_texture(game, background, false);
    List* current = game->current_scene->structures;
    while (current != NULL) {
        push_render_stack_structure(game, (Structure*)(current->value), false);
        current = current->next;
    }

}

void free_mem_texture(void* t) {
    MemTexture* t2 = (MemTexture*)t;
    if (t2 == NULL) {
        return;
    }
    if (t2->data != NULL) {
        free(t2->data);
    }
    free(t2);
}

void destroy_font(void* f) {
    TTF_CloseFont((TTF_Font*)f);
}
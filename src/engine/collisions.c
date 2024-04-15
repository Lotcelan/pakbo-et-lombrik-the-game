#include "./include/collisions.h"

Box* init_rect_box(int x, int y, int w, int h) {
    Box* box = malloc(sizeof(Box));
    if (box == NULL) {
        return NULL;
    }
    SDL_Rect zone = {.x = x, .y = y, .w = w, .h = h};
    box->zone = zone;
    return box;
}

Box* init_rect_box_from_entity(GameData* game, Entity* e) {
    if (e == NULL) {
        return NULL;
    }
    SDL_Texture* spriteSheet = e->sprite->spriteSheet;
    int* frame = e->sprite->currentFrame->value;

    SDL_Rect spriteRect = {.x = frame[0]*e->sprite->width, .y = frame[1]*e->sprite->height, .w = e->sprite->width, .h = e->sprite->height};


    // Retrieve the SDL_Texture* sprite associated to the spriteRec in the spritesheet
    SDL_Texture* sprite = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, spriteRect.w, spriteRect.h);
    SDL_SetRenderTarget(game->renderer, sprite);
    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, spriteSheet, &spriteRect, NULL);

    // Now find the smallest box that contains the sprite and is not transparent
    int min_x = spriteRect.x;
    int max_x = spriteRect.x + spriteRect.w;
    int min_y = spriteRect.y;
    int max_y = spriteRect.y + spriteRect.h;

    Uint32* pixels = malloc(spriteRect.w * spriteRect.h * sizeof(Uint32));
    SDL_RenderReadPixels(game->renderer, &spriteRect, SDL_PIXELFORMAT_RGBA8888, pixels, spriteRect.w * sizeof(Uint32));
    SDL_SetRenderTarget(game->renderer, NULL);

    for (int y = 0; y < spriteRect.h; y++) {
        for (int x = 0; x < spriteRect.w; x++) {
            Uint32 pixel = pixels[y * spriteRect.w + x];
            if (pixel != 0) { // Assuming transparent pixels have a value of 0
                if (x < min_x) {
                    min_x = x;
                }
                if (x > max_x) {
                    max_x = x;
                }
                if (y < min_y) {
                    min_y = y;
                }
                if (y > max_y) {
                    max_y = y;
                }
            }
        }
    }

    free(pixels);

    int w = max_x - min_x + 1;
    int h = max_y - min_y + 1;

    return init_rect_box(e->x_position + min_x, e->y_position + min_y, w, h);
}

Box* init_rect_box_from_structure(GameData* game, Structure* s) {
    if (s == NULL) {
        return NULL;
    }
    
    printf("Structure : %s\n", s->identifier);
    SDL_Texture* texture = s->texture;
    SDL_Rect rect = s->position;

    return init_rect_box(rect.x, rect.y, rect.w, rect.h);
    
        // Create a surface to hold the texture's pixel data
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, SDL_PIXELFORMAT_RGBA8888);

    // Set the texture as the render target
    SDL_SetRenderTarget(game->renderer, texture);

    // Read the pixel data from the texture into the surface
    SDL_RenderReadPixels(game->renderer, &rect, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);

    // Reset the render target
    SDL_SetRenderTarget(game->renderer, NULL);

    // Now you can access the pixel data through the surface
    Uint32* pixels = (Uint32*)surface->pixels;



    // Uint32* pixels = (Uint32*)surface->pixels;
    
    // int min_x = rect.w;
    // int max_x = 0;
    // int min_y = rect.h;
    // int max_y = 0;

    // 
    // for (int y = 0; y < rect.h; y++) {
    //     for (int x = 0; x < rect.w; x++) {
    //         Uint32 pixel = pixels[(y + rect.y) * surface->w + (x + rect.x)];
    //         Uint8 alpha = (pixel >> 24) & 0xFF;

    //         if (alpha != 0) {
    //             if (x < min_x) {
    //                 min_x = x;
    //             }
    //             if (x > max_x) {
    //                 max_x = x;
    //             }
    //             if (y < min_y) {
    //                 min_y = y;
    //             }
    //             if (y > max_y) {
    //                 max_y = y;
    //             }
    //         }
    //     }
    // }

    int min_x = 0;
    int max_x = rect.w;
    int min_y = 0;
    int max_y = rect.h;

    printf("-------------------\n");
    // find the smallest x that is not transparent
    for (int x = 0; x < rect.w; x++) {
        bool isAllColumnTransparent = true;
        for (int y = 0; y < rect.h; y++) {
            Uint32 pixel = pixels[y * surface->w + x];
            Uint8 alpha = (pixel >> 24) & 0xFF;
            if (alpha != 0) {
                isAllColumnTransparent = false;
                break;
            }
        }
        if (isAllColumnTransparent) {
            min_x = x;
        } else {
            break;
        }
    }

    // find the biggest x that is not transparent
    for (int x = rect.w - 1; x >= 0; x--) {
        bool isAllColumnTransparent = true;
        for (int y = 0; y < rect.h; y++) {
            Uint32 pixel = pixels[y * surface->w + x];
            Uint8 alpha = (pixel >> 24) & 0xFF;
            if (alpha != 0) {
                isAllColumnTransparent = false;
                break;
            }
        }
        if (isAllColumnTransparent) {
            max_x = x;
        } else {
            break;
        }
    }

    // find the smallest y that is not transparent
    for (int y = 0; y < rect.h; y++) {
        bool isAllRowTransparent = true;
        for (int x = 0; x < rect.w; x++) {
            Uint32 pixel = pixels[y * surface->w + x];
            Uint8 alpha = (pixel >> 24) & 0xFF;
            if (alpha != 0) {
                isAllRowTransparent = false;
                break;
            }
        }
        if (isAllRowTransparent) {
            min_y = y;
        } else {
            break;
        }
    }

    // find the biggest y that is not transparent
    for (int y = rect.h - 1; y >= 0; y--) {
        bool isAllRowTransparent = true;
        for (int x = 0; x < rect.w; x++) {
            Uint32 pixel = pixels[y * surface->w + x];
            printf("Pixel : %d\n", pixel);
            Uint8 alpha = (pixel >> 24) & 0xFF;
            printf("Alpha : %d\n", alpha);
            if (alpha != 0) {
                isAllRowTransparent = false;
                break;
            }
        }
        if (isAllRowTransparent) {
            printf("All row transparent : %d\n", y);
            max_y = y;
        } else {
            break;
        }
    }
    printf("FIN -------------------\n");

    SDL_FreeSurface(surface);

    int w = max_x - min_x;
    int h = max_y - min_y;

    return init_rect_box(rect.x + min_x, rect.y + min_y, w, h);
}

bool are_colliding(Box* a, Box* b) {
    SDL_Rect zone1 = a->zone;
    SDL_Rect zone2 = b->zone;
    
    // printf("Comparing A : %d, %d, %d, %d AND B : %d, %d, %d, %d\n", zone1.x, zone1.y, zone1.w, zone1.h, zone2.x, zone2.y, zone2.w, zone2.h);

    if (SDL_HasIntersection(&zone1, &zone2)) {
        return true;
    }
    return false;
}

bool is_entity_colliding_with_structures(Entity* e, List* structures) {
    if (e == NULL) {
        return false;
    }
    // pour l'instant balek des pass_through, a prendre en compte après
    Box* entity_box = e->collision_box;
    
    // printf("structures : %p\n", structures);
    List* current = structures;
    while (current != NULL) {
        // ("Checking %d\n", ((Structure*)(current->value))->position.x);
        Box* struct_box = ((Structure*)(current->value))->collision_box;
        if (are_colliding(entity_box, struct_box)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void free_box(Box* box) {
    free(box);
}

void update_entity_boxes(Entity* e) {
    // non indépendant du type de zone
    if (e == NULL) {
        return;
    }
    if (e->collision_box == NULL) {
        return;
    }

    e->collision_box->zone.x = e->x_position;
    e->collision_box->zone.y = e->y_position;

    if (e->hurt_box != NULL) {
        e->hurt_box->zone.x = e->x_position;
        e->hurt_box->zone.y = e->y_position;
    }

    if (e->hit_box != NULL) {
        e->hit_box->zone.x = e->x_position;
        e->hit_box->zone.y = e->y_position;
    }
    
    // printf("after change : %d, %d, %d, %d\n", e->collision_box->zone.x, e->collision_box->zone.y, e->collision_box->zone.w, e->collision_box->zone.h);
    // todo : other boxes
}

void enlarge_entity_hitbox(Entity* e, Box* new_hitbox) {
    // non indépendant du type de zone
    if (e == NULL || new_hitbox == NULL) {
        return;
    }
    if (e->hit_box == NULL) {
        e->hit_box = new_hitbox;
        return;
    }
    SDL_Rect old_hitbox = e->hit_box->zone;
    SDL_Rect new_hitbox_rect = new_hitbox->zone;

    int min_x = old_hitbox.x;
    int max_x = old_hitbox.x + old_hitbox.w;
    int min_y = old_hitbox.y;
    int max_y = old_hitbox.y + old_hitbox.h;

    if (new_hitbox_rect.x < min_x) {
        min_x = new_hitbox_rect.x;
    }
    if (new_hitbox_rect.x + new_hitbox_rect.w > max_x) {
        max_x = new_hitbox_rect.x + new_hitbox_rect.w;
    }
    if (new_hitbox_rect.y < min_y) {
        min_y = new_hitbox_rect.y;
    }
    if (new_hitbox_rect.y + new_hitbox_rect.h > max_y) {
        max_y = new_hitbox_rect.y + new_hitbox_rect.h;
    }

    e->hit_box->zone.x = min_x;
    e->hit_box->zone.y = min_y;
    e->hit_box->zone.w = max_x - min_x;
    e->hit_box->zone.h = max_y - min_y;
}
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

	SDL_Rect spriteRect = {.x = frame[0] * e->sprite->width, .y = frame[1] * e->sprite->height, .w = e->sprite->width, .h = e->sprite->height};

	return init_rect_box(spriteRect.x, spriteRect.y, spriteRect.w, spriteRect.h); // vu que le reste semble pas marcher

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
			if (pixel != 0) {  // Assuming transparent pixels have a value of 0
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

Uint32 getPixel(SDL_Surface *loadingSurface, int x, int y) {

    Uint32 *pixels = (Uint32*)loadingSurface->pixels;
    return pixels[(y * loadingSurface->pitch / 4) + x]; // I noticed that each y selection was off by 4 pixels in the y so I divided by 4. Why this is the case remains a mystery.

}

SDL_Color getPixelColor(SDL_Surface *loadingSurface, int x, int y) {

    SDL_Color getColor = {0,0,0,0};
    SDL_PixelFormat *format;
    Uint32 pixel, index;
    Uint8 red, green, blue, alpha;

    format = loadingSurface->format;
    SDL_LockSurface(loadingSurface);
    pixel = getPixel(loadingSurface, x, y);
    SDL_UnlockSurface(loadingSurface);

    index = pixel & format->Rmask;  
    index = index >> format->Rshift; 
    index = index << format->Rloss;  
    red = (Uint8)index;

    index = pixel & format->Gmask;   
    index = index >> format->Gshift; 
    index = index << format->Gloss;  
    green = (Uint8)index;

    index = pixel & format->Bmask;   
    index = index >> format->Bshift; 
    index = index << format->Bloss;  
    blue = (Uint8)index;

    index = pixel & format->Amask;
    index = index >> format->Ashift;
    index = index << format->Aloss;
    alpha = (Uint8)index;

    getColor.r = red;
    getColor.g = green;
    getColor.b = blue;
    getColor.a = alpha;

    return getColor;

}

Box* init_rect_box_from_structure(GameData* game, Structure* s) {
	// Final goal : returns the smallest bouding box in which the structure fits (so without the transparent pixels)
	// Right now : returns the bounding box that is the whole structure
	
	if (s == NULL) {
		return NULL;
	}

	printf("Structure : %s\n", s->identifier);
	SDL_Texture* texture = s->texture;
	SDL_Texture* valid_texture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, s->position.w, s->position.h);
	
	SDL_Rect rect = s->position;

	return init_rect_box(rect.x, rect.y, rect.w, rect.h);

	// Create a surface to hold the texture's pixel data
	// SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, SDL_PIXELFORMAT_RGBA8888);

	// Set the texture as the render target
	SDL_SetRenderTarget(game->renderer, valid_texture);

	SDL_RenderClear(game->renderer);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	// Read the pixel data from the texture into the surface
	Uint32* pixels = malloc(rect.w * rect.h * sizeof(Uint32));
	SDL_RenderReadPixels(game->renderer, &rect, SDL_PIXELFORMAT_RGBA8888, pixels, rect.w * sizeof(Uint32));

	// Reset the render target
	SDL_SetRenderTarget(game->renderer, NULL);
	// Now you can access the pixel data through the surface
	// Uint32* pixels = (Uint32*)surface->pixels;
	for (int y = 0; y < rect.h; y++) {
		for (int x = 0; x < (rect.w * sizeof(Uint32)/4); x++) {
			// printf("%i ", getPixelColor(surface, x, y).b);
			printf("%i ", (pixels[y * (rect.w * sizeof(Uint32)/4) + x]) & 0x000000FF);
		}
		printf("\n");
	}

	// Uint32* pixels = (Uint32*)surface->pixels;

	// int min_x = rect.w;
	// int max_x = 0;
	// int min_y = rect.h;
	// int max_y = 0;

	//
	// for (int y = 0; y < rect.h; y++) {
	//     for (int x = 0; x < rect.w; x++) {
	//         Uint32 pixel = pixels[(y + rect.y) * surface->w + (x + rect.x)];
	//         Uint8 alpha = (pixel << 24) >> 24;

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
			Uint32 pixel = pixels[y * rect.w + x];
			Uint8 alpha = (pixel << 24) >> 24;
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
			Uint32 pixel = pixels[y * rect.w + x];
			Uint8 alpha = (pixel << 24) >> 24;
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
			Uint32 pixel = pixels[y * rect.w + x];
			Uint8 alpha = (pixel << 24) >> 24;
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
			Uint32 pixel = pixels[y * rect.w + x];
			// printf("Pixel : %d\n", pixel);
			Uint8 alpha = (pixel << 24) >> 24;
			// printf("Alpha : %d\n", alpha);
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

	// SDL_FreeSurface(surface);
	free(pixels);
	SDL_DestroyTexture(valid_texture);

	int w = max_x - min_x;
	int h = max_y - min_y;

	return init_rect_box(rect.x + min_x, rect.y + min_y, w, h);
}

bool are_colliding(Box* a, Box* b) {
	if (a == NULL || b == NULL) {
		return false;
	}

	SDL_Rect zone1 = a->zone;
	SDL_Rect zone2 = b->zone;

	// printf("Comparing A : %d, %d, %d, %d AND B : %d, %d, %d, %d\n", zone1.x, zone1.y, zone1.w, zone1.h, zone2.x, zone2.y, zone2.w, zone2.h);

	if (SDL_HasIntersection(&zone1, &zone2)) {
		return true;
	}
	return false;
}

Structure* is_entity_colliding_with_structures(Entity* e, List* structures) {
	// Returns NULL if no collision, or the structure with which the entity is colliding
	if (e == NULL) {
		return NULL;
	}
	// pour l'instant balek des pass_through, a prendre en compte après
	Box* entity_box = e->collision_box;

	// printf("structures : %p\n", structures);
	List* current = structures;
	while (current != NULL) {
		// ("Checking %d\n", ((Structure*)(current->value))->position.x);
        Structure* s = ((Structure*)(current->value));

		int allow_pass_through = s->allow_pass_through;
		if (allow_pass_through != 0 && are_colliding(e->prev_collision_box, s->collision_box)) {
		    current = current->next;
		    continue;
		}

		bool left_allow = (allow_pass_through & 0x8) >> 3 == 1;
		bool up_allow = (allow_pass_through & 0x4) >> 2 == 1;
		bool right_allow = (allow_pass_through & 0x2) >> 1 == 1;
		bool down_allow = (allow_pass_through & 0x1) == 1;

		// printf("Allow pass through : %d, %d, %d, %d, %d\n", allow_pass_through, allow_pass_through & 0b1000, allow_pass_through & 0b0100, allow_pass_through & 0b0010, allow_pass_through & 0b0001);

		if (left_allow && e->prev_collision_box->zone.x + e->prev_collision_box->zone.w <= s->collision_box->zone.x) {
			current = current->next;
			continue;
		}
		if (up_allow && e->prev_collision_box->zone.y + e->prev_collision_box->zone.h <= s->collision_box->zone.y) {
            current = current->next;
            continue;
        }
        if (right_allow && e->prev_collision_box->zone.x >= s->collision_box->zone.x + s->collision_box->zone.w) {
            current = current->next;
            continue;
        }
        if (down_allow && e->prev_collision_box->zone.y >= s->collision_box->zone.y + s->collision_box->zone.h) {
            current = current->next;
            continue;
        }

		Box* struct_box = s->collision_box;
		if (are_colliding(entity_box, struct_box)) {
			return s;
		}
		current = current->next;
	}
	return NULL;
}

void free_box(Box* box) {
	if (box == NULL) {
		return;
	}
	free(box);
}

void update_entity_boxes(Entity* e) {
	// non indépendant du type de zone
	if (e == NULL) {
		return;
	}
	int delta_x, delta_y;
	// printf("delta_x : %d, delta_y : %d\n", delta_x, delta_y);

	if (e->collision_box != NULL) {
		delta_x = e->x_position - e->prev_collision_box->zone.x;
		delta_y = e->y_position - e->prev_collision_box->zone.y;

		e->collision_box->zone.x += delta_x;
		e->collision_box->zone.y += delta_y;
	}

	if (e->hurt_box != NULL) {
		delta_x = e->x_position - e->prev_collision_box->zone.x;
		delta_y = e->y_position - e->prev_collision_box->zone.y;
		e->hurt_box->zone.x += delta_x;
		e->hurt_box->zone.y += delta_y;
	}

	if (e->hit_box != NULL) {
		delta_x = e->x_position - e->prev_collision_box->zone.x;
		delta_y = e->y_position - e->prev_collision_box->zone.y;
		e->hit_box->zone.x += delta_x;
		e->hit_box->zone.y += delta_y;
	}

	// printf("after change : %d, %d, %d, %d\n", e->collision_box->zone.x, e->collision_box->zone.y, e->collision_box->zone.w, e->collision_box->zone.h);
	// todo : other boxes
}

Box* copy_box(Box* a) {
	if (a == NULL) {
		return NULL;
	}
	Box* new_box = malloc(sizeof(Box));
	if (new_box == NULL) {
		return NULL;
	}
	new_box->zone = a->zone;
	// printf("Origin box : %d, %d, %d, %d\n", a->zone.x, a->zone.y, a->zone.w, a->zone.h);
	// printf("New box : %d, %d, %d, %d\n", new_box->zone.x, new_box->zone.y, new_box->zone.w, new_box->zone.h);
	return new_box;
}

void enlarge_entity_hitbox(Entity* e, Box* new_hitbox) {
	// Prends une entité et une hitbox et AGRANDIT (ne remplace pas) la hitbox de l'entité avec la nouvelle hitbox
	// non indépendant du type de zone
	if (e == NULL || new_hitbox == NULL) {
		return;
	}
	if (e->hit_box == NULL) {
		e->hit_box = copy_box(new_hitbox);
		return;
	}
	SDL_Rect old_hitbox = e->hit_box->zone;
	SDL_Rect new_hitbox_rect = new_hitbox->zone;
	int min_x, max_x, min_y, max_y;

	min_x = old_hitbox.x < new_hitbox_rect.x ? old_hitbox.x : new_hitbox_rect.x;
	min_y = old_hitbox.y < new_hitbox_rect.y ? old_hitbox.y : new_hitbox_rect.y;

	max_x = old_hitbox.x + old_hitbox.w > new_hitbox_rect.x + new_hitbox_rect.w ? old_hitbox.x + old_hitbox.w : new_hitbox_rect.x + new_hitbox_rect.w;
	max_y = old_hitbox.y + old_hitbox.h > new_hitbox_rect.y + new_hitbox_rect.h ? old_hitbox.y + old_hitbox.h : new_hitbox_rect.y + new_hitbox_rect.h;

	e->hit_box->zone.x = min_x;
	e->hit_box->zone.y = min_y;
	e->hit_box->zone.w = max_x - min_x;
	e->hit_box->zone.h = max_y - min_y;
	// printf("With old box : %d, %d, %d, %d\n", old_hitbox.x, old_hitbox.y, old_hitbox.w, old_hitbox.h);
	// printf("With new box : %d, %d, %d, %d\n", new_hitbox_rect.x, new_hitbox_rect.y, new_hitbox_rect.w, new_hitbox_rect.h);
	// printf("Result : %d, %d, %d, %d\n", e->hit_box->zone.x, e->hit_box->zone.y, e->hit_box->zone.w, e->hit_box->zone.h);
}

void change_structure_coordinates(Structure* s, int x, int y) {
	if (s == NULL) {
		return;
	}
	s->collision_box->zone.x = x;
	s->collision_box->zone.y = y;
	s->position.x = x;
	s->position.y = y;
}

Structure* is_entity_touching_the_top_of_a_structure(Entity* e, List* s_list) {
	// name is explicit :)
	
	if (s_list == NULL || e == NULL) {
		return NULL;
	}

	List* current = s_list;
	while (current != NULL) {
		Structure* s = (Structure*)(current->value);
		if (e->collision_box->zone.y + e->sprite->height >= s->position.y) {
			return s;
		}

		current = current->next;
	}


	return NULL;
}
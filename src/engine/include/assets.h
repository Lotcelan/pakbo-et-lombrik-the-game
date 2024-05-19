#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include <string.h>
#include "game.h"
#include "../../resources.h"
#include "collisions.h"
#include "entity.h"
#include "weapon.h"
#include "modifiers.h"

typedef struct GameData GameData;
typedef struct Box Box;
typedef struct Entity Entity;
typedef struct SceneModifier SceneModifier;

typedef struct Structure {
    const char* identifier;
    SDL_Texture* texture;
    SDL_Rect position;
    int allow_pass_through;
    const char* teleport_to_scene;
    Box* collision_box;
} Structure;

typedef struct RenderEntry {
    void* key;
    bool is_temporary;
    void (*render)(GameData* game, void* key);
    void (*destroy)(void* key);
} RenderEntry;

typedef struct Text {
    const char* text;
    SDL_Color color;
    SDL_Rect position;
    TTF_Font* font;
    SDL_Texture* texture;
} Text;

typedef struct Texture {
    char* name;
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect* srcRect;
    SDL_Rect* dstRect;
} Texture;

typedef struct Rectangle {
    int x;
    int y;
    int w;
    int h;
    SDL_Color outline_color;
    SDL_Color fill_color;
} Rectangle;

typedef struct Circle {
    int x;
    int y;
    int radius;
    SDL_Color color;
} Circle;


typedef struct MemTexture {
    int size;
    unsigned char* data;
} MemTexture;

SDL_Texture* loadTextureFromMemory(GameData* game, const char* resource);

void render_texture(GameData* game, void* key);
void render_structure(GameData* game, void* key);
void render_text(GameData* game, void* key);
void render_rectangle(GameData* game, void* key);
void render_circle(GameData* game, void* key);
void render_scene_modifier(GameData* game, void* key);

void render_entity(GameData* game, Entity* e, float delta);
void render_wrap_text(GameData* game, void* key, int wrap_length);

Text* init_text(GameData* game, const char* text, SDL_Color color, int x, int y, TTF_Font* font);
Structure* init_structure(GameData* game, const char* identifier, const char* resource, int x, int y, int allow_pass_through, const char* teleport_to_scene);
Rectangle* init_rectangle(int x, int y, int w, int h, SDL_Color outline_color, SDL_Color fill_color);
Texture* init_texture_from_memory(GameData* game, char* name, int x, int y);
Circle* init_circle(int x, int y, int radius, SDL_Color color);

void free_structure(void* s);
void free_text(void* t);
void free_rectangle(void* r);
void free_texture(void* t);
void free_mem_texture(void* t);
void free_circle(void* c);

void push_render_stack(GameData* game, void* key, void (*render)(GameData*, void*), void (*destroy)(void*), bool is_temporary);
void push_render_stack_text(GameData* game, Text* text, bool is_temporary);
void push_render_stack_structure(GameData* game, Structure* structure, bool is_temporary);
void push_render_stack_texture(GameData* game, Texture* texture, bool is_temporary);
void push_render_stack_rect(GameData* game, Rectangle* rect, bool is_temporary);
void push_render_stack_circle(GameData* game, Circle* circle, bool is_temporary);
void push_render_stack_scene_modifier(GameData* game, SceneModifier* sm, bool is_temporary);

void push_background_structures(GameData* game);

void render_stack(GameData* game);
void render_no_destroy(GameData* game);
void destroy_render_stack(GameData* game);

void destroy_font(void* f);

#endif

#ifndef ENTITY_H
#define ENTITY_H

#include <jansson.h>
#include "linked_list.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

typedef enum EntityType {
    // List of names of entities in the folder entities/
    player,
    monster,
    weapon,
    
} EntityType;

typedef struct sprite {
    float framerate;    // dans l'idéal c'est le meme opur chaque sprite, sert a reset le timer
    float timer;    // état du timer (mis a jour à chaque tour de boucle)
    SDL_Texture* spriteSheet;   // une grande texture contenant toutes les frames cote à cote
    // les champs width et height permettent de simplifier les coordonnonées dans la liste frames 
    int width;  // nombre de pixels de large pour une frame de l'animation
    int height;     // nombre de pixels de haut pour une frame de l'animation
    // exemple : lom bric aura certainement height = width = 16 (son sprite étant un carré de taille 16)
    List* frames;   // liste chainée CYCLIQUE de coordonnées vis à vis du tileSet
                    //les valeurs des maillons sont des quadruplets [x, y]
} Sprite;

typedef struct Entity {
    // position
    int x_position;
    int y_position;
    // vitesse
    float x_velocity;
    float y_velocity;
    // entier qui correspond à l'indice de l'animation qu'on veut afficher
    int etat;
    // modifie l'entier self.etat pour mettre a jour l'animation de l'entité
    void (*update_sprite)(struct Entity*, float);
    // tableau contenant les différentes animations 
    Sprite** animations;
    // le pointeur vers le sprite actuel est donc accessible par : Entity->animations[etat]

    void (*update)(struct Entity*);
} Entity;

// On pourra en rajouter
typedef struct Entity_old {
    // SDL_Texture* textures[4];
    // Mix_Chunk* sounds[4];
    TTF_Font* font;
    SDL_Rect position;
    
    void (*update)(struct Entity_old* e);
    
    int x_position;
    int y_position;
    int x_velocity;
    int y_velocity;

    EntityType *entity_type;
    int respawn_delay;
} Entity_old;



Sprite* get_sprite(Entity* e);
Entity* init_entity(char* entity, int respawn_delay, int x, int y);
void free_entity(Entity* e);
void update_entities(List* entities);
void update_self(Entity* e);
void update_pos_speed(Entity *e, float a_x, float a_y, int dt);

void update_animation(Sprite* sprite, float delta);
void print_entity(Entity* e);
#endif

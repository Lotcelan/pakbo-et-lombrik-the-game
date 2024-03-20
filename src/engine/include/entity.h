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
    List* frames;   // liste chainée de coordonnées vis à vis du tileSet
                    //les valeurs des maillons sont des quadruplets [x1, y1, x2, y2] 
} Sprite;


// On pourra en rajouter
typedef struct Entity {
    SDL_Texture* textures[4];
    Mix_Chunk* sounds[4];
    TTF_Font* font;
    SDL_Rect position;
    
    void (*update)(struct Entity* e);
    
    int x_position;
    int y_position;
    int x_velocity;
    int y_velocity;

    EntityType *entity_type;
    int respawn_delay;
} Entity;

typedef struct Entity_2 {
    // position
    int x_position;
    int y_position;
    // vitesse
    int x_velocity;
    int y_velocity;
    int etat;   // entier qui correspond à l'indice de l'animation qu'on veut afficher
    // modifie l'entier self.etat pour mettre a jour l'animation de l'entité
    void (*update_sprite)(struct Entity_2*, int);
    // liste des différentes animations 
    Sprite** animations;
    // le pointeur vers la frame actuelle est donc accessible par : Entity->animations[etat]->value
} Entity_2;


Entity* init_entity(char* entity, int respawn_delay, int x, int y);
void update_entities(List* entities);
void update_self(Entity* e);
void free_entity(Entity* e);

void update_pos_speed(Entity *e, float a_x, float a_y, int dt);

#endif

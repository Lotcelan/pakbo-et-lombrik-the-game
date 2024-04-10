#ifndef ENTITY_H
#define ENTITY_H

#include <jansson.h>
#include "game.h"
#include "linked_list.h"
#include "hashtable.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

typedef struct GameData GameData;


typedef enum EntityType {
    // List of names of entities in the folder entities/
    player,
    monster,
    weapon,
    
} EntityType;

typedef struct sprite {
    int framerate;    // dans l'idéal c'est le meme opur chaque sprite, sert a reset le timer
    float timer;    // état du timer (mis a jour à chaque tour de boucle)
    SDL_Texture* spriteSheet;   // une grande texture contenant toutes les frames cote à cote
    // les champs width et height permettent de simplifier les coordonnonées dans la liste frames 
    int width;  // nombre de pixels de large pour une frame de l'animation
    int height;     // nombre de pixels de haut pour une frame de l'animation
    // exemple : lom bric aura certainement height = width = 16 (son sprite étant un carré de taille 16)
    List** frames;  // tableau de listes chainées CYCLIQUES de coordonnées vis à vis du spriteSheet
                    // les valeurs des maillons sont des quadruplets [x, y]
    List* currentFrame; // la valeur est un tableau de taille 2 de forme [x, y]
    // LockSprite : tableau d'entiers associant a chaque état un booléen
    // 0 si l'animation boucle
    // un entier si l'animation doit se jouer jusqu'au bout (exemple : coup d'épée)
    int* Lock_liste;
    int Lock;
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
    // modifie l'entité self.etat pour mettre a jour l'animation de l'entité
    // le flottant correspond au deltaT (temps depuis la frame précédente, en secondes)
    void (*update_animation)(struct Entity*, float);
    // sprite (framerate, timer, spriteSheet, width, height)
    Sprite* sprite;

    void (*update)(struct Entity*, float delta_t);
    void (*event_handler)(struct Entity*, GameData*);
    HashTable* objects;
} Entity;

typedef Entity* (*EntityInitFunc)(GameData*, int, int);


Sprite* get_sprite(Entity* e);
void free_entity(void* e);

void update_frame(Entity* e, float delta);
void print_entity(Entity* e);
Entity* init_entity(int x, int y, int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste, void (*update)(Entity* e, float d), void (*event_handler)(Entity* e, GameData* game), void (*update_animation)(Entity* e, float delta));
Sprite* init_sprite(int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste);
#endif

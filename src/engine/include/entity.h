#ifndef ENTITY_H
#define ENTITY_H

#include <jansson.h>
#include "game.h"
#include "linked_list.h"
#include "hashtable.h"
#include "collisions.h"
#include "weapon.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


typedef struct GameData GameData;
typedef struct Box Box;
typedef struct Weapon Weapon;

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
                    // les valeurs des maillons sont des couples [x, y]
    List* currentFrame; // la valeur est un tableau de taille 2 de forme [x, y]
    // LockSprite : tableau d'entiers associant a chaque état un booléen
    // 0 si l'animation boucle
    // un entier si l'animation doit se jouer jusqu'au bout (exemple : coup d'épée)
    // cet entier étant le nombre de frames que dure cette animation
    int* Lock_liste;
    int Lock;

    int* nbFrames;
    // orientation permet de ne pas avoir a faire un sprite qui regarde a droite et un sprite qui regarde a gauche
    SDL_RendererFlip orientation;
} Sprite;

typedef struct Entity {
    // position
    int x_position;
    int y_position;
    // vitesse
    double x_velocity;
    double y_velocity;
    // entier qui correspond à l'indice de l'animation qu'on veut afficher
    int etat;
    // modifie l'entité self.etat pour mettre a jour l'animation de l'entité
    // le flottant correspond au deltaT (temps depuis la frame précédente, en secondes)
    void (*update_animation)(struct Entity* e, float d);
    // sprite (framerate, timer, spriteSheet, width, height)
    Sprite* sprite;

    void (*update)(GameData* game, struct Entity* e, float delta_t);
    void (*event_handler)(struct Entity* e, GameData* game);
    HashTable* objects;
    List* modifiers; // Les modifiers sont les effets bonus ou malus

    Box* collision_box;
    Box* hurt_box;
    Box* hit_box;

    Box* prev_collision_box; // Useful in many scenarios
    Box* prev_hurt_box;
    Box* prev_hit_box;

    int max_hp;
    int current_hp;

    int damage_delay; // amount of `ms` to wait before being able to receive damage again
    int stagger_duration; // amount of `ms` to wait before being able to move again
    
    Weapon* weapon;
    struct Entity* parent; // CAN BE USEFUL (for projectiles for instance)
} Entity;

typedef Entity* (*EntityInitFunc)(GameData*, int, int);

Sprite* get_sprite(Entity* e);
void free_entity(void* e);

void update_frame(Entity* e, float delta);
void print_entity(Entity* e);
Entity* init_entity(int x, int y, int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste, void (*update)(GameData* game, Entity* e, float d), void (*event_handler)(Entity* e, GameData* game), void (*update_animation)(Entity* e, float delta), int max_hp, bool should_have_hitbox);
Sprite* init_sprite(int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste);
void damage_entity(GameData* game, Entity* e, int damage, int delay, int stagger_duration, bool should_repulse_attacker, Entity* attacker);
int compare_entities(void* e1, void* e2);
void clear_entities(GameData* game);
void change_entity_coordinates(Entity* e, int x, int y);
void free_entity_list(void* lst);
void* copy_entity(void* e);
void* copy_sprite(void* sprite);
void* copy_tuple(void* t);
#endif

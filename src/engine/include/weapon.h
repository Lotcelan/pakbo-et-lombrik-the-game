#ifndef WEAPON_H
#define WEAPON_H

#include<SDL2/SDL.h>

#include "game.h"
#include "collisions.h"

typedef struct GameData GameData;
typedef struct Entity Entity;


typedef struct Weapon {
    char *name;
    int damage_value;
    int max_durability;
    int current_durability;
    
    void (*update)(GameData* game, Entity* e, float delta_t);
    void (*event_handler)(GameData* game, struct Weapon* weapon, Entity* e); //Entity pour savoir a qui appartient l'arme, weapon pour l'arme en elle meme, et game car on en a tjrs besoin
    void (*render)(GameData* game, Entity* e, float delta_t);
    
    HashTable* objects;

   
    

} Weapon;

typedef Weapon* (*WeaponInitFunc)(GameData* game);

void render_weapon(GameData* game, Entity* e, float delta_t);
int delete_weapon(Weapon* weapon);

#endif
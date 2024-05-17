#ifndef MODIFIERS_H
#define MODIFIERS_H

#include "assets.h"
#include "game.h"
#include "linked_list.h"

typedef struct Texture Texture;


typedef enum {
    N_JUMP,
    POISON_EFFECT,
    FIRE_EFFECT,
    SPEED_HOOF
} ModifierName;

typedef struct Modifier {
    int value; // En gros, tous les modifiers (n-saut, effet de poison, effet de feu etc...  auront tous une valeur numérique (genre dégât à infliger, nombre de saut à ajouter etc) et cette valeur ne fera sens que dans le cadre du modifier étudié
    ModifierName name;
    int quantity;
} Modifier;

bool is_modifier_name_effect(ModifierName name);
Texture* modifier_name_to_texture(GameData* game, ModifierName name, int x, int y);
Modifier* create_modifier(ModifierName name, int value);
void add_modifier_to_entity(GameData* game, Entity* e, ModifierName name, int value);
void destroy_modifier(void* mo);
Modifier* get_entity_modifier(Entity* e, ModifierName name);


#endif
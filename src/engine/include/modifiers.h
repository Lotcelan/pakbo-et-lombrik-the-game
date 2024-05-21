#ifndef MODIFIERS_H
#define MODIFIERS_H

#include "assets.h"
#include "game.h"
#include "linked_list.h"

typedef struct Texture Texture;
typedef struct Scene Scene;


typedef enum {
    N_JUMP, // value n'a pas d'effet, c'est la quantité d'items qui compte ici
    POISON_EFFECT, // (qui va être infligé à l'attaqué) value indique le nombre en ms de délai  entre chaque proc de poison sur les 16 premiers bits, puis la durée que l'affect aura sur les 16 suivants, La quantité d'items est le nombre de points de vie perdu a chaque fois
    POISON_AFFECT, // (qui va être infligé à l'attaquant) value indique le nombre en ms de délai entre chaque proc de poison, La quantité d'items est le nombre de points de vie perdu a chaque fois
    SPEED_HOOF, // value n'a pas d'effet, c'est la quantité qui applique un multiplicateur
    N_LIFE, // value représente le nombre de point de vie à récupérer, l'objectif est qu'il soit consommé instantanément
    BALL_AND_CHAIN, // comme speed_hoof mais inversé
    SWORD
} ModifierName;

typedef struct Modifier {
    int value; // En gros, tous les modifiers (n-saut, effet de poison, effet de feu etc...  auront tous une valeur numérique (genre dégât à infliger, nombre de saut à ajouter etc) et cette valeur ne fera sens que dans le cadre du modifier étudié
    ModifierName name;
    int quantity;

    int current_time_alive; // combien de temps le modifier a passé sur le joueur
    int max_time_alive; // combien de temps le modifier peut rester max sur le joueur. Une valeur de -1 signifie infini
} Modifier;

typedef struct SceneModifier {
    Modifier* modifier;
    int x;
    int y;
} SceneModifier;

bool is_modifier_name_effect(ModifierName name);
Texture* modifier_name_to_texture(GameData* game, ModifierName name, int x, int y);
Modifier* create_modifier(ModifierName name, int value, int max_time_alive);
void add_modifier_to_entity(GameData* game, Entity* e, ModifierName name, int value, int max_time_alive);
void destroy_modifier(void* mo);
Modifier* get_entity_modifier(Entity* e, ModifierName name);
SceneModifier* create_scene_modifier(Modifier* modifier, int x, int y);
void spawn_modifier_in_scene(GameData* game, Scene* scene, Modifier* modifier, int x, int y);
void update_entity_modifiers(GameData* game, List* entity_list);
void destroy_scene_modifier(void* sm);
SceneModifier* copy_scene_modifier(SceneModifier* sm);
Modifier* copy_modifier(Modifier* to_copy);
void update_modifiers(GameData* game);
#endif
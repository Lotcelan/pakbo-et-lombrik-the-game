#include "./include/modifiers.h"

bool is_modifier_name_effect(ModifierName name) {
    // Effect : items qui vont à droite, qui sont "positifs"
    // Affect : items qui vont à guahce, qui sont "négatifs"
    
    switch (name) {
        case N_JUMP:
            return true;
        case SPEED_HOOF:
            return true;
        case POISON_EFFECT:
            return false;
        case FIRE_EFFECT:
            return false;
    }
}

Texture* modifier_name_to_texture(GameData* game, ModifierName name, int x, int y) {
    char mem_name[100];
    switch (name) {
        case N_JUMP:
            strcpy(mem_name, "src_assets_modifiers_N_JUMP");
            break;
        case POISON_EFFECT:
            strcpy(mem_name, "src_assets_modifiers_POISON_EFFECT");
            break;
        case FIRE_EFFECT:
            strcpy(mem_name, "src_assets_modifiers_FIRE_EFFECT");
            break;
        case SPEED_HOOF:
            strcpy(mem_name, "src_assets_modifiers_N_JUMP");
            break;
    }

    Texture* t = init_texture_from_memory(game, mem_name, x, y);
    return t;
}
Modifier* create_modifier(ModifierName name, int value) {
    Modifier* m = (Modifier*)malloc(sizeof(Modifier));
    if (m == NULL) {
        printf("Could not create modifier\n");
        return;
    }
    m->value = value;
    m->name = name;
    m->quantity = 1;

    return m;
}
void add_modifier_to_entity(GameData* game, Entity* e, ModifierName name, int value) {
    (void)game;
    if (e == NULL) return;
    List* current = e->modifiers;
    while (current != NULL) {
        Modifier* m = (Modifier*)(current->value);
        if (m->name == name && m->value == value) {
            m->quantity++;
            return;
        }
        
        current = current->next;
    }

    Modifier* m = create_modifier(name, value);
    if (m != NULL && e != NULL) {
        e->modifiers = append_first(m, e->modifiers);
    }
}

void destroy_modifier(void* mo) {
    if (mo == NULL) return;
    Modifier* m = (Modifier*)mo;
    free(m);
}

Modifier* get_entity_modifier(Entity* e, ModifierName name) {
    if (e == NULL) return NULL;;
    List* current = e->modifiers;
    while (current != NULL) {
        Modifier* m = (Modifier*)(current->value);
        if (m->name == name) {
            return m;
        }
        
        current = current->next;
    }
    return NULL;
}
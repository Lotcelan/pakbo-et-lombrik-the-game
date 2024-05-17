#include "./include/modifiers.h"


Texture* modifier_name_to_texture(GameData* game, ModifierName name, int x, int y) {
    char mem_name[100];
    switch (name) {
        case N_JUMP:
            strcpy(mem_name, "src_assets_modifiers_NJUMP");
            break;
        case POISON_EFFECT:
            strcpy(mem_name, "src_assets_modifiers_NJUMP");
            break;
        case FIRE_EFFECT:
            strcpy(mem_name, "src_assets_modifiers_NJUMP");
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

    return m;
}
void add_modifier_to_entity(GameData* game, Entity* e, ModifierName name, int value) {
    (void)game;
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
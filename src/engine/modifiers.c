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
            return true;
        case POISON_AFFECT:
            return false;
        case N_LIFE:
            return true; // de tte facon il se fait tej instant
        case BALL_AND_CHAIN:
            return false;
        case SWORD:
            return true;
    }

    return false;
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
        case POISON_AFFECT:
            strcpy(mem_name, "src_assets_modifiers_POISON_AFFECT");
            break;
        case SPEED_HOOF:
            strcpy(mem_name, "src_assets_modifiers_SPEED_HOOF");
            break;
        case BALL_AND_CHAIN:
            strcpy(mem_name, "src_assets_modifiers_BALL_AND_CHAIN");
            break;
        case N_LIFE:
            strcpy(mem_name, "src_assets_modifiers_N_LIFE");
            break;
        case SWORD:
            strcpy(mem_name, "src_assets_modifiers_SWORD");
            break;
    }

    Texture* t = init_texture_from_memory(game, mem_name, x, y);
    return t;
}
Modifier* create_modifier(ModifierName name, int value, int max_time_alive) {
    // max time alive in in ms
    Modifier* m = (Modifier*)malloc(sizeof(Modifier));
    if (m == NULL) {
        printf("Could not create modifier\n");
        return NULL;
    }
    m->value = value;
    m->name = name;
    m->quantity = 1;
    m->current_time_alive = 0;
    m->max_time_alive = max_time_alive;

    return m;
}
void add_modifier_to_entity(GameData* game, Entity* e, ModifierName name, int value, int max_time_alive) {
    (void)game;
    if (e == NULL) return;
    List* current = e->modifiers;
    while (current != NULL) {
        Modifier* m = (Modifier*)(current->value);
        if (m->name == name && m->value == value) {
            m->quantity++;
            m->max_time_alive = (m->max_time_alive - m->current_time_alive > max_time_alive) ? m->max_time_alive - m->current_time_alive : max_time_alive; // c'est cumulable du coup
            m->current_time_alive = 0; // et on reset
            return;
        }
        
        current = current->next;
    }

    Modifier* m = create_modifier(name, value, max_time_alive);
    if (m != NULL && e != NULL) {
        e->modifiers = append_first(m, e->modifiers);
    }
}

Modifier* copy_modifier(Modifier* to_copy) {
    if (to_copy == NULL) return NULL;
    Modifier* m = (Modifier*)malloc(sizeof(Modifier));
    if (m == NULL) {
        printf("Could not create modifier\n");
        return NULL;
    }
    m->value = to_copy->value;
    m->name = to_copy->name;
    m->quantity = to_copy->quantity;
    m->current_time_alive = to_copy->current_time_alive;
    m->max_time_alive = to_copy->max_time_alive;

    return m;
}

void destroy_modifier(void* mo) {
    if (mo == NULL) return;
    Modifier* m = (Modifier*)mo;
    free(m);
}

void remove_entity_modifier(Entity* e, Modifier* m) {
    if (!m || !e) return;

    List* current = e->modifiers;
    List* previous = NULL;
    bool found = false;
    while (current) {
        Modifier* m_current = current->value;
        if (m_current == m) {
            found = true;
            break;
        }
        previous = current;
        current = current->next;
    }

    if (found && current) {
        if (previous) {
            previous->next = current->next;
        } else {
            e->modifiers = current->next;
        }
        destroy_modifier(current->value);
        free(current);
    }
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

SceneModifier* create_scene_modifier(Modifier* modifier, int x, int y) {
    SceneModifier* sm = (SceneModifier*)malloc(sizeof(SceneModifier));

    sm->x = x;    
    sm->y = y;    
    sm->modifier = modifier;

    return sm;
}

void spawn_modifier_in_scene(GameData* game, Scene* scene, Modifier* modifier, int x, int y) {
    // va spawn un collectible sur lequel on peut passer pour obtenir le modifier
    // x et y numéros de cases
    // ici le time duration de `modifier` n'a pas d'importance, autant mettre -1

    (void)game;

    if (scene == NULL) return;
    scene->modifiers = append_first(create_scene_modifier(modifier, x, y), scene->modifiers); // y'a pas de null qui tienne ici (c'est du déni)
}

void update_entity_modifiers(GameData* game, List* entity_list) {
    // ajoute le temps écoulé depuis la dernière frame au current_time_alive des modifiers
    // supprime ceux qui ont écoulé leur temps
    
    List* current = entity_list;
    while (current != NULL) {
        Entity* e = (Entity*)(current->value);
        if (e == NULL) continue;
        List* current_modifiers = e->modifiers;
        List* previous = NULL;
        while (current_modifiers != NULL) {
            Modifier* m = (Modifier*)(current_modifiers->value);
            if (m != NULL) {
                m->current_time_alive = m->current_time_alive + game->deltaT;
                if (m->max_time_alive != -1) { // en vrai pas nécessaire vu le test en dessous, mais c pour le principe
                    if (m->current_time_alive >= m->max_time_alive) {
                        if (previous == NULL) {
                            e->modifiers = current_modifiers->next;
                        } else {
                            previous->next = current_modifiers->next;
                        }
                        destroy_modifier(m);
                        current_modifiers = e->modifiers;
                        previous = NULL;
                    }
                }
            }
            previous = current_modifiers;
            if (current_modifiers != NULL){
                current_modifiers = current_modifiers->next;
            }else{
                continue;
            }
        }

        current = current->next;
    }
    
}

void update_modifiers(GameData* game) {
    if (game->current_scene == NULL) return;

    // logique sur la scène
    // y a t il collision entre le joueur et un modifier sur la scène à récupérer ?
    List* current = game->current_scene->modifiers;
    List* previous = NULL;
    while (current != NULL) {
        SceneModifier* sm = (SceneModifier*)current->value;
        Modifier* m = sm->modifier;
        if (m == NULL) {
            previous == current;
            current = current->next;
            continue;
        }
        Box* sm_box = init_rect_box(sm->x * CELL_WIDTH, sm->y * CELL_HEIGHT, 16, 16);
        if (are_colliding(game->player->collision_box, sm_box)) {
            add_modifier_to_entity(game, game->player, m->name, m->value, m->max_time_alive);
            if (previous == NULL) {
                game->current_scene->modifiers = current->next;
            } else {
                previous->next = current->next;
            }
            destroy_scene_modifier(sm);
            current = game->current_scene->modifiers;
            previous = NULL;
            continue;
        }
        previous = current;
        current = current->next;
    }

    
    // logique sur les entités
    update_entity_modifiers(game, append_first(game->player, game->current_scene->entities));

}

void destroy_scene_modifier(void* sm) {
    if (sm == NULL) return;
    SceneModifier* scene_mod = (SceneModifier*)sm;
    destroy_modifier(scene_mod->modifier);
    free(scene_mod);
}

SceneModifier* copy_scene_modifier(SceneModifier* sm) {
    if (sm == NULL) return NULL;
    
    SceneModifier* new_sm = (SceneModifier*)malloc(sizeof(SceneModifier));

    new_sm->x = sm->x;    
    new_sm->y = sm->y;    
    new_sm->modifier = copy_modifier(sm->modifier);

    return new_sm;
}
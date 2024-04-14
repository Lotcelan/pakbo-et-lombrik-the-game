#include "include/entity.h"



void free_entity(void* entite) {
    Entity* e = (Entity*)entite;
    int width, height;
    SDL_QueryTexture(e->sprite->spriteSheet, NULL, NULL, &width, &height);
    // on libère les listes de coordonnées
    for (int i = 0 ; i < (height/e->sprite->height) ; i++){
        list_cyclic_delete(e->sprite->frames[i], &free);
    }
    free(e->sprite->frames);
    free(e->sprite->Lock_liste);
    SDL_DestroyTexture(e->sprite->spriteSheet);
    free(e->sprite);
    free(e);
}

Sprite* get_sprite(Entity* e){
    return e->sprite;
}


// attention : ce n'est pas la fonction update_animation de la structure entity
// en revanche, update_sprite sera appelée par cette dernière en général (quasiment tout le temps)
// update_frame sert à aficher la frame suivante si besoin (d'ou l'utilisation de delta)
void update_frame(Entity* e, float delta){
    // int d = delta;
    // // cette boucle sert a gérer les cas ou delta est assez grand pour passer plusieurs frames d'un coup
    // // (exemple : si il y a un lag, on va vouloir sauter une frame)
    // while (d - e->sprite->timer > 0){
    //     d = d - e->sprite->timer;
    //     e->sprite->currentFrame = e->sprite->currentFrame->next;
    //     e->sprite->timer = 1/e->sprite->framerate;    // on reset le timer
    // }
    // e->sprite->timer -= d;

    //delta en ms
    if(delta > e->sprite->timer){
        e->sprite->currentFrame = e->sprite->currentFrame->next;
        e->sprite->timer = 1000/(e->sprite->framerate);
    }
    else{
        e->sprite->timer = e->sprite->timer - delta;
    }
}

void print_entity(Entity* e){
    printf("position : (%d, %d)\n", e->x_position, e->y_position);
    printf("velocité : (%.2f, %.2f)\n", e->x_velocity, e->y_velocity);
    printf("état : %d\n", e->etat);
}

Entity* init_entity(int x, int y, int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste, void (*update)(GameData* game, Entity* e, float d), void (*event_handler)(Entity* e, GameData* game), void (*update_animation)(Entity* e, float delta), int max_hp) {
    Entity* res = malloc(sizeof(Entity));
    res->x_position = x;
    res->y_position = y;
    res->x_velocity = 0;
    res->y_velocity = 0;
    res->etat = 0;
    res->sprite = init_sprite(framerate, spriteSheet, width, height, nbFrames, lock_liste);
    res->update = update;
    res->event_handler = event_handler;
    res->update_animation = update_animation;
    HashTable* objects = createHashTable(10);
    res->objects = objects;

    res->max_hp = max_hp;
    res->current_hp = max_hp;

    res->collision_box = init_rect_box(x,y,width, height);
    res->hurt_box = res->collision_box; // could be different later, but weird
    res->hit_box = init_rect_box(x,y,width, height); // s'adaptera au sprite

    res->damage_delay = -1;
    res->weapon = NULL;
    return res;
}

// init_Sprite renvoie un sprite
// le tableau nbFrames contient le nb de frame de chaque animation dans l'ordre
// nbFrames[i] est le nombre de frames de l'animation de l'état i
// (toutes les frames de l'entité ont les memes dimentions sinon c'est chiant)
// à terme on va virer ce paramètre et la fonction init_sprite lira la sprite sheet pour déterminer automatiquement la longueur des animations
Sprite* init_sprite(int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste){
    Sprite* res = malloc(sizeof(Sprite));
    res->framerate = framerate;
    res->timer = 1/framerate;
    res->timer = res->timer*1000;   // on passe le timer en ms
    res->spriteSheet = spriteSheet;
    res->width = width;
    res->height = height;
    res->Lock_liste = lock_liste;
    res->Lock = lock_liste[0];
    res->orientation = SDL_FLIP_NONE;
    
    // on cherche le nb d'animations différentes de l'entité 
    int sswidth, ssheight;  //ss pour spriteSheet
    SDL_QueryTexture(spriteSheet, NULL, NULL, &sswidth, &ssheight);
    int nb_etats = ssheight/res->height;
    List** frames = malloc(nb_etats*sizeof(List));
    List* current;
    // on remplit les champs de List** frames (non automatisé)
    for (int etat = 0 ; etat<nb_etats ; etat++){
        current = NULL;
        for (int i = nbFrames[etat] ; i>0 ; i--){
            int* co = malloc(2*sizeof(int));
            co[0] = i-1;
            co[1] = etat;
            current = append_cyclic_first(co, current);
        }
        frames[etat] = current;
    }
    res->frames = frames;
    res->currentFrame = frames[0];
    return res;
}


void damage_entity(GameData* game, Entity* e, int damage, bool should_add_delay){
    // Si on veut que sur le dégât un délai soit appliquer, on met should_add_delay à true
    if(e->damage_delay < 0){
        e->current_hp -= damage;
        if (should_add_delay) {
            e->damage_delay = 1500;
        }
    }

    // if (e->current_hp <= 0){
    //     game->current_scene->entities = delete_compare(game->current_scene->entities, e, compare_entities, free_entity);   
    // }
}

void clear_entities(GameData* game){
    List* current = game->current_scene->entities;
    while (current != NULL){
        Entity* e = (Entity*)current->value;
        if (e->current_hp <= 0){
            game->current_scene->entities = delete_compare(game->current_scene->entities, e, compare_entities, free_entity);
            current = game->current_scene->entities;
            continue;
        }
        current = current->next;
    }
}

int compare_entities(void* e1, void* e2){
    Entity* ent1 = (Entity*)e1;
    Entity* ent2 = (Entity*)e2;
    return (int)(ent1 == ent2);
}
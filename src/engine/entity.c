#include "include/entity.h"

// TODO
void free_entity(void* entite) {
    // Entity* e = (Entity*)entite;
    free(entite);
}

// /!\ PAS ENCORE TESTÉE (mais normalement elle fonctionne vu la compliexité du bousin)
Sprite* get_sprite(Entity* e){
    return e->sprite;
}


// attention : ce n'est pas la fonction update_animation de la structure entity
// en revanche, update_sprite sera appelée par cette dernière en général (quasiment tout le temps)
// update_frame sert à aficher la frame suivante si besoin (d'ou l'utilisation de delta)
void update_frame(Entity* e, float delta){
    int d = delta;
    // cette boucle sert a gérer les cas ou delta est assez grand pour passer plusieurs frames d'un coup
    // (exemple : si il y a un lag, on va vouloir sauter une frame)
    while (d - e->sprite->timer > 0){
        d = d - e->sprite->timer;
        e->sprite->currentFrame = e->sprite->currentFrame->next;
        e->sprite->timer = 1/e->sprite->framerate;    // on reset le timer
    }
    e->sprite->timer -= d;
}

void print_entity(Entity* e){
    printf("position : (%d, %d)\n", e->x_position, e->y_position);
    printf("velocité : (%.2f, %.2f)\n", e->x_velocity, e->y_velocity);
    printf("état : %d\n", e->etat);
}

Entity* init_entity(int x, int y){
    Entity* res = malloc(sizeof(Entity));
    res->x_position = x;
    res->y_position = y;
    res->x_velocity = 0;
    res->y_velocity = 0;
    res->etat = 0;
    return res;
}

// init_Sprite renvoie un sprite
// le tableau nbFrames contient le nb de frame de chaque animation dans l'ordre
// nbFrames[i] est le nombre de frames de l'animation de l'état i
// (toutes les frames de l'entité ont les memes dimentions sinon c'est chiant)
// à terme on va virer ce paramètre et la fonction init_sprite lira la sprite sheet pour déterminer automatiquement la longueur des animations
Sprite* init_sprite(int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames){
    Sprite* res = malloc(sizeof(Sprite));
    res->framerate = framerate;
    res->timer = 1/framerate;
    res->spriteSheet = spriteSheet;
    res->width = width;
    res->height = height;
    // partie à automatiser, création de List**frames :
    // on cherche le nb d'animations différentes de l'entité (deja automatisé)
    int sswidth, ssheight;  //ss pour spriteSheet
    SDL_QueryTexture(spriteSheet, NULL, NULL, &sswidth, &ssheight);
    printf("entity.c : %d, %d\n", sswidth, ssheight);
    int nb_etats = ssheight/res->height;
    List** frames = malloc(nb_etats*sizeof(List));
    List* current;
    int co[2];
    // on remplit les champs de List** frames (non automatisé)
    for (int etat = 0 ; etat<nb_etats ; etat++){
        current = NULL;
        for (int i = nbFrames[etat] ; i>0 ; i--){
            co[0] = i;
            co[1] = etat;
            current = create_list_cyclic(co, current);
        }
        frames[etat] = current;
    }
    res->frames = frames;
    res->currentFrame = frames[0];
    return res;
}

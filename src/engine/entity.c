#include "include/entity.h"

void free_entity(void* entite) {
	if  (entite == NULL) return;
	Entity* e = (Entity*)entite;
	int width, height;
	if (e->sprite == NULL) {
		free(e);
		return;
	}
	SDL_QueryTexture(e->sprite->spriteSheet, NULL, NULL, &width, &height);
	// on libère les listes de coordonnées
	for (int i = 0; i < (height / e->sprite->height); i++) {
		list_cyclic_delete(e->sprite->frames[i], free);
	}
	free(e->sprite->frames);
	free(e->sprite->Lock_liste);
	SDL_DestroyTexture(e->sprite->spriteSheet);
	free(e->sprite);
	list_delete(e->modifiers, destroy_modifier);
	free(e);
}

Sprite* get_sprite(Entity* e) {
	return e->sprite;
}

// attention : ce n'est pas la fonction update_animation de la structure entity
// en revanche, update_sprite sera appelée par cette dernière en général (quasiment tout le temps)
// update_frame sert à aficher la frame suivante si besoin (d'ou l'utilisation de delta)
void update_frame(Entity* e, float delta) {
	// int d = delta;
	// // cette boucle sert a gérer les cas ou delta est assez grand pour passer plusieurs frames d'un coup
	// // (exemple : si il y a un lag, on va vouloir sauter une frame)
	// while (d - e->sprite->timer > 0){
	//     d = d - e->sprite->timer;
	//     e->sprite->currentFrame = e->sprite->currentFrame->next;
	//     e->sprite->timer = 1/e->sprite->framerate;    // on reset le timer
	// }
	// e->sprite->timer -= d;

	// delta en ms
	if (delta > e->sprite->timer) {
		e->sprite->currentFrame = e->sprite->currentFrame->next;
		e->sprite->timer = 1000 / (e->sprite->framerate);
	} else {
		e->sprite->timer = e->sprite->timer - delta;
	}
}

void print_entity(Entity* e) {
	printf("position : (%d, %d)\n", e->x_position, e->y_position);
	printf("velocité : (%.2f, %.2f)\n", e->x_velocity, e->y_velocity);
	printf("état : %d\n", e->etat);
}

Entity* init_entity(int x, int y, int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste, void (*update)(GameData* game, Entity* e, float d), void (*event_handler)(Entity* e, GameData* game), void (*update_animation)(Entity* e, float delta), int max_hp, bool should_have_hitbox) {
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
	res->modifiers = NULL;

	res->max_hp = max_hp;
	res->current_hp = max_hp;
    res->stagger_duration = -1;
	res->collision_box = init_rect_box(x, y, width, height);
	res->prev_collision_box = copy_box(res->collision_box);
	res->hurt_box = copy_box(res->collision_box);  // could be different later, but weird
	res->prev_hurt_box = copy_box(res->hurt_box);
	if (should_have_hitbox) {
		res->hit_box = init_rect_box(x, y, width, height);	// s'adaptera au sprite
		res->prev_hit_box = copy_box(res->hit_box);
	} else {
		res->hit_box = NULL;
		res->prev_hit_box = NULL;
	}
	res->damage_delay = -1;
	res->weapon = NULL;

	res->parent = NULL;

	//AUDIO
	res->soundEffectManager = initSoundEffectManager();

	return res;
}

void change_entity_coordinates(Entity* e, int x, int y) {
    if (e->stagger_duration > 0) {
        return;
    }
    
	free(e->prev_collision_box);
	free(e->prev_hurt_box);
	free(e->prev_hit_box);

	e->prev_collision_box = copy_box(e->collision_box);
	e->prev_hurt_box = copy_box(e->hurt_box);
	e->prev_hit_box = copy_box(e->hit_box);

	e->x_position = x;
	e->y_position = y;
	update_entity_boxes(e);
}

// init_Sprite renvoie un sprite
// le tableau nbFrames contient le nb de frame de chaque animation dans l'ordre
// nbFrames[i] est le nombre de frames de l'animation de l'état i
// (toutes les frames de l'entité ont les memes dimentions sinon c'est chiant)
// à terme on va virer ce paramètre et la fonction init_sprite lira la sprite sheet pour déterminer automatiquement la longueur des animations
Sprite* init_sprite(int framerate, SDL_Texture* spriteSheet, int width, int height, int* nbFrames, int* lock_liste) {
	Sprite* res = malloc(sizeof(Sprite));
	res->framerate = framerate;
	res->timer = 1 / framerate;
	res->timer = res->timer * 1000;	 // on passe le timer en ms
	res->spriteSheet = spriteSheet;
	res->width = width;
	res->height = height;
	res->Lock_liste = lock_liste;
	res->Lock = lock_liste[0];
	res->orientation = SDL_FLIP_NONE;
	res->nbFrames = nbFrames;
	// on cherche le nb d'animations différentes de l'entité
	int sswidth, ssheight;	// ss pour spriteSheet
	SDL_QueryTexture(spriteSheet, NULL, NULL, &sswidth, &ssheight);
	int nb_etats = ssheight / res->height;
	List** frames = malloc(nb_etats * sizeof(List));
	List* current;
	// on remplit les champs de List** frames (non automatisé)
	for (int etat = 0; etat < nb_etats; etat++) {
		current = NULL;
		for (int i = nbFrames[etat]; i > 0; i--) {
			int* co = malloc(2 * sizeof(int));
			co[0] = i - 1;
			co[1] = etat;
			current = append_cyclic_first(co, current);
		}
		frames[etat] = current;
	}
	res->frames = frames;
	res->currentFrame = frames[0];
	return res;
}

void* copy_tuple(void* t) {
	if (t == NULL) return NULL;
	int* co = malloc(2*sizeof(int));
	int* tuple = (int*)t;
	co[0] = tuple[0];
	co[1] = tuple[1];

	return co;
}

void* copy_sprite(void* s) {
	if (s == NULL) return NULL;
	Sprite* sprite = (Sprite*) s;
	Sprite* copy = malloc(sizeof(Sprite));
	copy->framerate = sprite->framerate;
	copy->timer = sprite->timer;
	copy->spriteSheet = sprite->spriteSheet;
	copy->width = sprite->width;
	copy->height = sprite->height;
	copy->Lock_liste = malloc(sizeof(int) * sprite->height);
	for (int i = 0; i < sprite->height; i++) {
		copy->Lock_liste[i] = sprite->Lock_liste[i];
	}
	copy->Lock = sprite->Lock;
	copy->orientation = sprite->orientation;
	copy->nbFrames = malloc(sizeof(int) * sprite->height);
	for (int i = 0; i < sprite->height; i++) {
		copy->nbFrames[i] = sprite->nbFrames[i];
	}
	copy->frames = malloc(sizeof(List*) * sprite->height);
	int sswidth, ssheight;	// ss pour spriteSheet
	SDL_QueryTexture(sprite->spriteSheet, NULL, NULL, &sswidth, &ssheight);
	int nb_etats = ssheight / sprite->height;
	for (int i = 0; i < nb_etats; i++) {
		printf("%i\n", nb_etats);
		copy->frames[i] = copy_cyclic_list(sprite->frames[i], copy_tuple);
	}
	copy->currentFrame = copy->frames[0];
	return copy;
}


void damage_entity(GameData* game, Entity* e, int damage, int delay, int stagger_duration, bool should_repulse_attacker, Entity* attacker) {
	// Si on veut que sur le dégât un délai soit appliquer, on met should_add_delay à true
	if (e->damage_delay < 0) {
		e->current_hp -= damage;
        e->stagger_duration = stagger_duration;

        if (compare_entities(e, game->player)) {
            ScreenShake* shake = init_screen_shake(10, 5);
            game->current_scene->screen_shake = shake;

        }
        
		if (delay >= 0) {
			e->damage_delay = delay;
		}

		(void)should_repulse_attacker;
		(void)attacker;
		// if (should_repulse_attacker && attacker != NULL) {
		// 	int s_x = (attacker->x_velocity > 0) ? 1 : -1;
		// 	printf("a l'atak\n");
		// 	int s_y = (attacker->y_velocity > 0) ? 1 : -1;
		// 	attacker->x_velocity = -s_x * 50 -attacker->x_velocity;
		// 	// attacker->y_velocity = -s_y * 20 -attacker->y_velocity;
		// }

		if (attacker && e){
			Modifier *m = get_entity_modifier(attacker, POISON_EFFECT);
			if (m){
				int value = m->value;
				int proc_delay = (value & 0xFFFF);
				int poison_duration = (value >> 16) & 0xFFFF;
				add_modifier_to_entity(game, e, POISON_AFFECT, proc_delay, poison_duration);
			}
		}
	}

	
	// if (e->current_hp <= 0){
	//     game->current_scene->entities = delete_compare(game->current_scene->entities, e, compare_entities, free_entity);
	// }
}

void clear_entities(GameData* game) {
	List* current = game->current_scene->entities;
	while (current != NULL) {
		Entity* e = (Entity*)current->value;
		if (e->current_hp <= 0) {
			game->current_scene->entities = delete_compare(game->current_scene->entities, e, compare_entities, free_entity);
			current = game->current_scene->entities;
			continue;
		}
		current = current->next;
	}
}

int compare_entities(void* e1, void* e2) {
	Entity* ent1 = (Entity*)e1;
	Entity* ent2 = (Entity*)e2;
	return (int)(ent1 == ent2);
}

void free_entity_list(void* lst) {
	List* l = (List*)lst;
	list_delete(l, free_entity);
}

void* copy_entity(void* entity) {
	if (entity == NULL) return NULL;
	Entity* e = (Entity*) entity;
	Entity* copy = malloc(sizeof(Entity));
	copy->x_position = e->x_position;
	copy->y_position = e->y_position;
	copy->x_velocity = e->x_velocity;
	copy->y_velocity = e->y_velocity;
	copy->etat = e->etat;
	copy->sprite = (Sprite*)copy_sprite(e->sprite);
	copy->update = e->update;
	copy->event_handler = e->event_handler;
	copy->update_animation = e->update_animation;
	copy->objects = createHashTable(10);
	copy->max_hp = e->max_hp;
	copy->current_hp = e->current_hp;
	copy->stagger_duration = e->stagger_duration;
	copy->collision_box = copy_box(e->collision_box);
	copy->prev_collision_box = copy_box(e->prev_collision_box);
	copy->hurt_box = copy_box(e->hurt_box);
	copy->prev_hurt_box = copy_box(e->prev_hurt_box);
	if (e->hit_box != NULL) {
		copy->hit_box = copy_box(e->hit_box);
		copy->prev_hit_box = copy_box(e->prev_hit_box);
	} else {
		copy->hit_box = NULL;
		copy->prev_hit_box = NULL;
	}
	copy->damage_delay = e->damage_delay;
	copy->weapon = e->weapon;
	copy->parent = e->parent;
	return copy;
}
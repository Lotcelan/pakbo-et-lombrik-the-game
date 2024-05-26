# Smol Game Engine Tutorial

## Structure of the engine

```
- include/ : Contient tous les headers
- structures/ : Contient les structures de données intéressantes
- entities/ : Contient des dossiers relatifs à chaque entité
- scenes/ : Même chose pour les scènes
```

## Structures

### Tas binaire

Le tas mis en place ici est un tas binaire "min". Il servira à faire des files de priorité (pour un A* par exemple).

Les primitives implémentées sont :
- create
- insert
- extract
- "heapify" (d'un tableau)

### Liste chaînées

Littéralement un maillon essentiel à la construction d'autres structures et aussi utile dans le code (pour stocker les entités d'une scène par exemple).

Beaucoup de primitives sur les listes chaînées et listes chaînées cycliques ont été implémentées

## Scènes

Un dossier contenant une scène doit avoir :
- {nom_de_scene}.json : Cf juste après
- {nom_de_scene}.c/h : Contiendra la logique de la scène

<details>
<summary>Format de data.json</summary>
Le fichier `data.json` doit suivre ce format :

```json
{
    "name": "Exemple level", // The name can not be 'none'
    "background" : "src_assets_{name_of_the_file_including_the_path_with_underscores}", // Key of the resource hashmap
    "structures" : [
        {
			"identifier" : "wall00", // Un nom, si possible unique, auquel on pourra se référer dans le code
            "x" : 0, // Grid position
            "y" : 0, // Grid position
            "texture" : "src_assets_structures_wall", // Ici on suit le chemin dans assets du fichier png (un "_" pour rentrer dans un sous dossier). Ne pas oublier de laner assests_to_code pour ajouter les images !
            "allow_pass_through" : 8, // On 4 bits : first bit : left, then cyclig clockwise
            "teleport_to_scene" : "none"
        },
        {
			"identifier" : "door105",
            "x" : 10,
            "y" : 5,
            "texture" : "src_assets_structures_door",
            "allow_pass_through" : 8,
            "teleport_to_scene" : "scene02_3_2" // On indique le nom de la scène et où se TP dedans
        }
    ],
    "entities" : [
        {
            "x" : 50,
            "y" : 50,
            "entity" : "monster1" // Name of the key in the hashtable
        }
    ]
}
```

Allow pass through est un paramètre entier qui représente en réalité la valeur codée sur 4 bits (abcd) où :
- a représente à gauche
- b en haut
- c à droite
- d en bas
Et si (par exemple) a vaut 1 alors le joueur peut passer à travers l'objet s'il arrive par la gauche

</details>

<details>
    <summary>Format nom_de_scene.c/h</summary>

```c
void update_nom_de_scene(GameData* game) {
    // update the scene
    return;
}

void event_handler_nom_de_scene(GameData* game) {
    // update the scene
    return;
}


Scene* init_scene01(GameData* game) {
    Scene* scene = init_scene("nom_de_scene"); // Le nom ici DOIT ABSOLUMENT CORRESPONDRE au nom du dossier dans lequel le fichier .c est stocké
    
    scene->update = update_nom_de_scene;
    scene->event_handler = event_handler;
    return scene;
}

```

</details>

### Processus d'ajout d'une scène

- Créer un dossier avec le nom de la scène en dupliquant une scène déjà existante
- Renommer (je conseille de garder dans le presse papier le nouveau nom) le dossier/fichiers avec le nom de la scène
- Aller dans les fichiers .c/.h et renommer partout (raccourci sur VS Code : Ctrl+D) le nom de l'ancienne scène avec le nouveau
- Aller dans main.c et ajouter ces deux éléments :
```c
#include "scenes/nom_de_scene/nom_de_scene.h" // au début
```
```c
SceneInit* nom_de_scene = (SceneInit*)malloc(sizeof(SceneInit)); // A l'endroit où il y a tous les init de scenbe
*nom_de_scene = init_nom_de_scene;
insert(game->scenes, "nom_de_scene", nom_de_scene, free);

```

## Entités

Un dossier contenant une entité doit avoir :
- {nom_de_scene}.c/h : Contiendra la logique de l'entité

<details>
    <summary>Format nom_entite.c/h</summary>

```c
#include "nom_entite.h"

#include <SDL2/SDL.h>

void update_nom_entite(GameData* game, Entity* nom_entite, float delta_t) {
	if (nom_entite == NULL) {
		return;
	}
    // Exemple de logique de monstre

	// int* damage = get(nom_entite->objects, "damage", strcmp);
	// if (damage == NULL) {
	// 	return;
	// }

	// bool* is_attacking = get(nom_entite->objects, "is_attacking", strcmp);
	// if (is_attacking == NULL) {
	// 	return;
	// }
	
	// follow_player(game, nom_entite, 30, 30);
	// update_entity_movement(game, nom_entite, delta_t, true);
	// if (are_colliding(nom_entite->hit_box, game->player->hurt_box)) {
	// 	damage_entity(game, game->player, *damage, 1000, -1);
	// 	*is_attacking = true;
	// }
	// else {
	// 	*is_attacking = false;
    // }
	return;
}
void event_handler_nom_entite(Entity* nom_entite, GameData* game) {
	(void)nom_entite;
	(void)game;
    // utilse si PNJ ou joueur
    
	return;
}

void update_animation_nom_entite(Entity* e, float delta) {
	(void)delta;
	// On vient juste modifier e->etat selon certaines conditions

	return;
}

Entity* init_nom_entite(GameData* game, int x, int y) {
	int* nbs = malloc(nombre de ligne dans la sheet * sizeof(int));
	nbs[0] = nb de frame sur la 1ere ligne;	 // idle
	nbs[1] = nb de frame sur la 2eme ligne
	...
	int* lock = malloc(nombre de ligne dans la sheet  * sizeof(int));
	lock[0] = nb de frames qu on veut "lock" sur la 1ere ligne;
	...

	SDL_Texture* spritesheet = loadTextureFromMemory(game, "src_assets_entities_NOM DE LA SPRITE SHEET");	// to change

    // Changer ici les FPS, la taille d'une case dans la sprite sheet, le nombre d'HP et si l'entité doit avoir une hitbox ou non
	Entity* nom_entite = init_entity(x, y, 14, spritesheet, 16, 16, nbs, lock, update_nom_entite, event_handler_nom_entite, update_animation_nom_entite, 9, true);

    // Exemple de l'utilisation de la hashtable objects
	// int* duck_damage = malloc(sizeof(int));
	// *duck_damage = 1;
	// insert(nom_entite->objects, "damage", duck_damage, free);

	// bool* is_attacking = malloc(sizeof(bool));
	// *is_attacking = false;
	// insert(nom_entite->objects, "is_attacking", is_attacking, free);

	return nom_entite;
}

```

### Processus d'ajout d'une entité

Le même (modulo les chemins à changer) que pour les scènes. (Création de dossier/fichier avec bon nom + ajout dans main.c)

</details>

## Armes

Un dossier contenant une arme doit avoir :
- {nom_arme}.c/h : Contiendra la logique de l'arme

C'est encore le même principe (très proche des entités, regardez le fichier basic_sword.c/h pour voir comment cela fonctionne)

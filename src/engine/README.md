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

Les primitives implémentées sont :
- init
- append
- map

## Scènes

Un dossier contenant une scène doit avoir :
- data.json : Cf juste après
- nom_de_scene.c/h : Contiendra la logique de la scène

<details>
<summary>Format de data.json</summary>
Le fichier `data.json` doit suivre ce format :
```json
{
    "name": "Exemple level", // The name can not be 'none'
    "background" : "background.png", // In the assets folder
    "structures" : [
        {
            "x" : 0,
            "y" : 0,
            "texture" : "wall.png",
            "allow_pass_through" : 8, // On 4 bits : first bit : left, then cyclig clockwise
            "teleport_to_scene" : "none"
        },
        {
            "x" : 100,
            "y" : 100,
            "texture" : "door.png",
            "allow_pass_through" : 8,
            "teleport_to_scene" : "scene02"
        }

    ],
    "entities" : [
        {
            "x" : 50,
            "y" : 50,
            "respawn_delay" : 5000, // In ms, the amount of time to wait AFTER leaving the room to have the entity respawn (if killed). Negative value if no respawn
            "entity" : "monster1"
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
void update_nom_de_scene() {
    // update the scene
    return;
}

Scene* init_scene01() {
    Scene* scene = init_scene("nom_de_scene"); // Le nom ici DOIT ABSOLUMENT CORRESPONDRE au nom du dossier dans lequel le fichier .c est stocké
    
    scene->update = update_nom_de_scene;
    return scene;
}

```
</details>


## Entités

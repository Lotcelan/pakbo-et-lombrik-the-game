# La documentation

## Introduction

Ce document introduit le fonctionnement principal du jeu, et redirige vers les bons fichiers si vous voulez en savoir plus sur certains composants.

## Fonctionnement général

Ce jeu fonctionne avec la librairie SDL2, et est décomposé en plusieurs catégories :
- Les "scènes" : ce sont les niveaux, des contenants d'entités (joueur, non joueur) et de structures (éléments du décor, choses avec lesquelles les entités pourront intéragir)
- Les "entités" : ce sont les joueurs et non-joueurs, des conteneurs d'armes
- Les "armes" : chaque arme peut être spéciale et avoir ses propres besoins, elles ont donc leur propre code

Le jeu suit donc une boucle princpale :
```
Récupérations des évènements (1)
Mises à jour des scènes, entités et armes selon les évènements (2)
Mises à jour des scènes, entités et armes selon leur propre logique (3)
Supprimer les entités mortes (4)
Afficher (5)
```

## Moteur de jeu

Un légèr moteur de jeu "The Smol Game engine" a été développé à l'occasion. Il permet d'intéragir avec la `render stack` des scènes.
Tout tourne autour d'une structure principale qui représent le jeu : `GameData` :
```c
typedef enum GameStatus {
    RUNNING,
    CHANGING, // changement de scène
    PAUSED,
    CLOSING,
} GameStatus;

typedef struct GameData {
    GameStatus state;
    Scene* current_scene;
    Dialog* current_dialog;

    SDL_Window* window;
    int width_amount; // nombre de cases de largeur
    int height_amount; // nombre de cases de hauteur
    SDL_Renderer* renderer; // le renderer
    SDL_Event event; // le dernier event récupéré
    const Uint8* keyboardState; // Update grâce à un PumpEvent. Informations plus précises sur les inputs clavier


    HashTable* resources; // Les images obtenues grâce à assets_to_code
    HashTable* fonts; // Des TTF_Font*
    HashTable* scenes; // FONCTIONS d'initialisation
    HashTable* entities; // FONCTIONS d'initialisation
    HashTable* weapons; // FONCTIONS d'initialisation

    Entity* player; // on sépare le joueur du reste des entités

    FrameRateManager* frm; // Gère les FPS du jeu
    float deltaT; // ajouté très tard dans la structure, donc bcp de fonctions le prenne encore en paramètre
} GameData;
```

De manière générale, toute les scènes, entités, armes ont des fichiers .c/.h associés, et dans main.c on les inclut et on ajoute les fonctions d'initialisation de ces objets dans des Hashtables du même nom dans la structure GameData.
Une documentation de son fonctionnement est [ici](../src/engine/README.md).

## Généralités sur les scenes/entités/armes

Chacun de ces objets a une structure associée (détaille ci-après), mais chaque instance a des besoins différents. (Exemple : un joueur a besoin de tracker combien de saut ont été fait, une mouche non. Exemple 2 : Une scène avec un puzzle qui compte combien de torches ont été allumées a besoin d'avoir dans sa structure ce nombre, mais une scène avec un combat n'a pas besoin de cette valeur).
Pour pallier à ceci, chaque objet a une Hashtable "objects" qui représente les variables locales de l'instance étudiée.

## Scènes

Une scène est définie par la structure
```c
typedef struct Scene {
    char title[200];
    List* render_stack;
    List* structures;
    List* entities;
    char background[200];
    void (*update)(GameData* game);
    void (*populate)(GameData* game);
    void (*event_handler)(GameData* game);
    ScreenShake* screen_shake;

    HashTable* objects;

} Scene;
```

Explications :
- title : nom de scène
- render_stack : Contient des RenderEntry*, soit QUELQUE CHOSE à afficher, et une FONCTION qui affiche ce quelque chose. Chaque RenderEntry* peut être "temporaire" ou non (ce qui est push dans populate est NON temporaire, ce qui est push dans update EST temporaire). Cela facilite l'ajout de nouvelles entrées.
- sturctures : les structures instanciées évoquées précédemment
- entities : les entités instanciées évoquées précédemment
- background : nom de la clé à aller chercher pour obtenir le fond (séparé des structures)
- update : fonction appelée dans le tour de boucle en (3)
- populate : fonction appelée au moment de l'instanciation de la scène : elle met dans la render stack les structures et fond d'écran
- event_handler : fonction appelée dans le tour de boucle en (2) qui permet de mettre à jour la scène en fonction de l'entrée utilisateur
- objects : comme décrit avant

Chaque scène va donc remplir ces différents champs.

Chaque fonction d'initialisation de scène se base sur la fonction init_scene_with_json("cle_scene") qui va lire un fichier `.json` qui décrit différentes informations. Son format est décrit dans la documentation de l'engine.

## Entités

Une entité est définie par les structures
```c
typedef struct sprite {
    int framerate;    // dans l'idéal c'est le même pour chaque sprite, sert à reset le timer
    float timer;    // état du timer (mis à jour à chaque tour de boucle)
    SDL_Texture* spriteSheet;   // une grande texture contenant toutes les frames côte à côte
    // les champs width et height permettent de simplifier les coordonnonées dans la liste frames 
    int width;  // nombre de pixels de large pour une frame de l'animation
    int height;     // nombre de pixels de haut pour une frame de l'animation
    // exemple : lom bric aura certainement height = width = 16 (son sprite étant un carré de taille 16x16)
    List** frames;  // tableau de listes chainées CYCLIQUES de coordonnées vis à vis du spriteSheet
                    // les valeurs des maillons sont des couples [x, y]
    List* currentFrame; // la valeur est un tableau de taille 2 de forme [x, y]
    // LockSprite : tableau d'entiers associant à chaque état un booléen
    // 0 si l'animation boucle
    // un entier si l'animation doit se jouer jusqu'au bout (exemple : coup d'épée)
    // cet entier étant le nombre de frames que dure cette animation
    int* Lock_liste;
    int Lock;

    int* nbFrames;
    // orientation permet de ne pas avoir à faire un sprite qui regarde à droite et un sprite qui regarde à gauche
    SDL_RendererFlip orientation;
} Sprite;

typedef struct Entity {
    // position
    int x_position;
    int y_position;
    // vitesse
    double x_velocity;
    double y_velocity;
    // entier qui correspond à l'indice de l'animation qu'on veut afficher
    int etat;
    // modifie l'entité self.etat pour mettre à jour l'animation de l'entité
    // le flottant correspond au deltaT (temps depuis la frame précédente, en secondes)
    void (*update_animation)(struct Entity* e, float d);
    // sprite (framerate, timer, spriteSheet, width, height)
    Sprite* sprite;

    void (*update)(GameData* game, struct Entity* e, float delta_t);
    void (*event_handler)(struct Entity* e, GameData* game);
    HashTable* objects;

    Box* collision_box;
    Box* hurt_box;
    Box* hit_box;

    Box* prev_collision_box; // Useful in many scenarios
    Box* prev_hurt_box;
    Box* prev_hit_box;

    int max_hp;
    int current_hp;

    int damage_delay; // amount of `ms` to wait before being able to receive damage again
    int stagger_duration; // amount of `ms` to wait before being able to move again
    
    Weapon* weapon;
    struct Entity* parent; // CAN BE USEFUL (for projectiles for instance)
} Entity;
```

Explication succincte :
- On va retrouver comme pour les scènes des fonctions qui vont être appelées dans la boucle principale
- Une entité peut avoir une arme, et un parent dont elle dépend
- Il y a 3 types de Box : Collision (en général = Hurtbox) qui permet de savoir si une structure/entité est en collision avec une autre. Une hurt box qui permet de savoir où est-ce que l'entité peut se prendre des dégâts. Enfin une hit box pour savoir où est-ce que l'entité inflige des dégâts.
- max_hp/current_hp : explicite
- sprite est détaillé dans la documentation de l'engine.

## Armes

Une arme est définie par la structure
```c

typedef struct Weapon {
    char *name;
    int damage_value;
    int max_durability;
    int current_durability;
    
    void (*update)(GameData* game, Entity* e, float delta_t);
    void (*event_handler)(GameData* game, struct Weapon* weapon, Entity* e); //Entity pour savoir à qui appartient l'arme, weapon pour l'arme en elle même, et game car on en à tjrs besoin
    void (*render)(GameData* game, Entity* e, float delta_t);
    
    HashTable* objects;

} Weapon;
```

Explications :
- Même principe que précédemment
- Le reste est explicite

## Les 'dialogues'

Un système de dialogue a été implementé, on peut charger depuis un fichier `.json` un arbre de dialogue.
Chaque noeud est du texte et les fils correspondent à différents choix possibles. Cela permet d'intéragir directement avec le joueur, les dialogues mettant en pause le jeu.

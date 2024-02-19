# Bâtô & Ver2Ter
*Ou bien Paquebots & Lombrics*

## Installation

**Section destinée aux développeurs**

Setup de SDL2 (sous Linux avec `apt`) :

```sh
sudo apt-get install libsdl2-dev
```

Voilà c'est tout. N'hésitez pas à changer le README pour Mac

## Structure du projet :

- src/ : Contient les fichiers sources
	| - main.c : Fichier principal qui lance le jeu et gère la logique
	| - scenes/ : Continedra ce qu'il faut pour chaque zone/biome
	| - engine/ : Contient les fichiers du moteur de jeu
		| - physics / audio / scene etc...
- assets/ :
	| - audio/
	| - sprites/
	| ...
- Makefile : Pour construire le jeu (selon architecture) et effectuer les tests


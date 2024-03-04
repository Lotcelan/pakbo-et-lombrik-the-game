# Bâtô & Ver2Ter
*Ou bien Paquebots & Lombrics*

## Installation

**Section destinée aux développeurs**

Setup de SDL2 (sous Linux avec `apt`) & Jansson (librairie pour parse du JSON) :

```sh
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libjansson-dev
```

Setup de SDL2 (sous Arch avec `yay`) :

```sh
yay -S sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

Setup de SDL2 (sous Mac OSX avec `brew`) :

```sh
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer sdl2_ttf
```

Voilà c'est tout. 

## Structure du projet :

```
- src/ : Contient les fichiers sources
	| - main.c : Fichier principal qui lance le jeu et gère la main loop
	| - scenes/ : Continedra ce qu'il faut pour chaque zone/biome
		| - exemple_scene/
			| - data.json : suit un format particulier pour décrire un niveau
			| - exemple_scene.h/c : pour la logique du niveau
	| - entities/ : Contiendra ce qu'il faut pour chaque entité
		| - exemple_monster/
			| - data.json : suit un format particulier pour décrire un monstre
			| - exemple_monster.h/c : pour la logique du mob
	| - engine/ : Contient les fichiers du moteur de jeu
		| - physics / audio / scene etc...
		| - structures/ : Structures de données intéressantes

- assets/ :
	| - audio/
	| - sprites/
	| ...
- Makefile : Pour construire le jeu (selon architecture) et effectuer les tests
```

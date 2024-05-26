# Bâtô & Ver2Ter
*Ou bien Paquebots & Lombrics*

## Présentation

Pakbo é Lombrik est un jeu qui se veut dynamique, avec des combats amusants et du platforming qui donne envie d'explorer un monde qui tourne autour de TN mais pas que !

![Trailer](./TRAILER-2.mp4)

## Installation

**Section destinée aux développeurs**

### Linux

Setup de SDL2 (sous Linux avec `apt`) & Jansson (librairie pour parse du JSON) :

```sh
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libjansson-dev
```

Setup de SDL2 (sous Arch avec `yay`) :

```sh
yay -S sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

### Mac OSX

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
			| - exemple_scene.json : suit un format particulier pour décrire un niveau
			| - exemple_scene.h/c : pour la logique du niveau
	| - entities/ : Contiendra ce qu'il faut pour chaque entité
		| - exemple_monster/
			| - exemple_monster.h/c : pour la logique du mob
	| - weapons/ :
		| - exemple_weapon/
				| - exemple_weapon.h/c : pour la logique de l'arme
	| - engine/ : Contient les fichiers du moteur de jeu
		| - include/ : tous les .h (+ facile pour la compilation)
		| - structures/ : structure de données utiles (hashtable, linked lists...)
		| - fichiers .c utiles pour le game engine
	| - assets/ : Contient les fichiers images et autres utiles
		| - audio/
		| - sprites/
		| ...
- Makefile : Pour construire le jeu (selon architecture)
```

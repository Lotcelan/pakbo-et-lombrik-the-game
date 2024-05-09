#ifndef GRID_GRAPH_H
#define GRID_GRAPH_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct GridNode {
    int x; // following same direction as SDL2
    int y;
    void* value; // Pour A* on aura 2 graphes : un qui représentera les parentés, et l'autre l'état du jeu (0 si on ne peut pas passer, 1 si on peut)
    void (*destroy_value)(void* v);
} GridNode;

typedef struct GridGraph {
    // graphe sous forme de grille : chaque noeud est connecté à ses voisins du haut, de droite, du bas, de gauche et diagonales aussi (SI POSSIBLE).
    int w;
    int h;
    GridNode** nodes; // tableau à 1D de GridNode* (je préfère travailler avec des pointeurs car faciles à comparer) (sinon comment différencier deux noeuds différents ?)
} GridGraph;

int idx(int x, int y, GridGraph* g); // transformer une input 2D pour le tableau 1D
GridGraph* create_grid_graph(int w, int h);
// a coté faudra faire une fonction game_to_grid_graph qui prend l'état actuel et met des 1 là où y'a rien qui bloque et 0 sinon (prendre une MARGE pour la taille de l'entité qui va se déplacer)
GridNode* get_grid_node(int x, int y, GridGraph* g);
void update_value_of_grid_node(int x, int y, void* value, void (*destroy_value)(void* v), GridGraph* g);
GridNode** get_neighbours(int x, int y, GridGraph* g); // renvoie un tableau à 8 valeurs en partant de en haut à gauche puis chaque axe cardinal (NULL si y'a pas de voisin dans une certaine direction. e.g : les coins)
void display_grid_graph_bool(GridGraph* g);
void display_grid_graph_float(GridGraph* g);
void display_grid_graph_grid_node_coords(GridGraph* g);
void destroy_grid_graph(GridGraph* g);
void destroy_grid_node(void* n);
GridNode* copy_grid_node(GridNode* n);
#endif
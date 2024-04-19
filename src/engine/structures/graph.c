#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "../include/graph.h"


// Fonction pour créer un noeud
Node* createNode(char* vertex, int weight, FunctionPointer func) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    newNode->func = func;  // Initialisez à la fonction passée
    return newNode;
}

// Fonction pour créer un graphe
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->vertices = malloc(vertices * sizeof(char*));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->vertices[i] = NULL;
    }

    return graph;
}


void addEdge(Graph* graph, char* src, char* dest, int weight, FunctionPointer func) {
    // Vérifiez si une arête existe déjà
    if (hasEdge(graph, src, dest)) {
        // Si l'arête existe déjà, trouvez-la et mettez à jour le poids et la fonction
        Node* temp = graph->adjLists[*src - 'A'];
        while (temp != NULL) {
            if (strcmp(temp->vertex, dest) == 0) {
                temp->weight = weight;
                temp->func = func;
                return;
            }
            temp = temp->next;
        }
    } else {
        // Si l'arête n'existe pas, créez une nouvelle arête
        Node* newNode = createNode(dest, weight, func);
        newNode->next = graph->adjLists[*src - 'A'];
        graph->adjLists[*src - 'A'] = newNode;
    }
}



void maFonction(void) {
    printf("Ceci est une fonction stockée dans un sommet.\n");
}

void maFonction_2(void){
    printf("nill");
}

void maFonction_3(void){
    // printf("");
    return;
}

void printGraph(Graph* graph) {
    (void)graph;
    // Dl_info info;
    // for (int v = 0; v < graph->numVertices; v++) {
    //     Node* temp = graph->adjLists[v];
    //     while (temp) {
    //         dladdr(temp->func, &info);
    //         printf("%s -> %s [Fonction : %s]\n", graph->vertices[v], temp->vertex, info.dli_sname);
    //         temp = temp->next;
    //     }
    // }
    printf("coucou je suis un graphe\n");
}

Node* getVertex(Graph* graph, char* name) {
    //Permet de récupérer le Node associé à la chaine de caractère
    //et donc toutes les données stockées dans le sommet
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcmp(graph->vertices[i], name) == 0) {
            return graph->adjLists[i];
        }
    }
    return NULL;
}

void printNeighbors(Graph* graph, char* name){
    //Affichage de tous les voisins, pratique pour le debug
    Node* vertex = getVertex(graph, name);
    if (vertex == NULL) {
        printf("Sommet non trouvé.\n");
        return;
    }
    printf("Les voisins du sommet %s sont :\n", name);
    while (vertex != NULL) {
        printf("%s \n", vertex->vertex);
        vertex = vertex->next;
    }
}


FunctionPointer getFunction(Graph* graph, char* src, char* dest){
    // Trouver le noeud source
    Node* srcNode = getVertex(graph, src);
    if (srcNode == NULL) {
        printf("Sommet source non trouvé.\n");
        return NULL;
    }

    // Parcourir la liste des arêtes du noeud source
    Node* temp = srcNode;
    while (temp != NULL) {
        // Si le sommet de destination est trouvé
        if (strcmp(temp->vertex, dest) == 0) {
            // Renvoyer la fonction associée à cette arête
            return temp->func;
        }
        temp = temp->next;
    }

    // Si le sommet de destination n'est pas trouvé
    printf("Sommet de destination non trouvé.\n");
    return NULL;
}


// Fonction pour vérifier si une arête existe
int hasEdge(Graph* graph, char* vertex_src, char* vertex_dest) {
    Node* vertex = getVertex(graph, vertex_src);
    if (vertex == NULL) {
        return 0;
    }
    while (vertex != NULL) {
        if (strcmp(vertex->vertex, vertex_dest) == 0) {
            return 1;
        }
        vertex = vertex->next;
    }
    return 0;
}

void deleteEdge(Graph* graph, char* src, char* dst) {
    int i = *src - 'A';
    Node* temp = graph->adjLists[i];
    Node* prev = NULL;

    // Parcourir la liste d'adjacence du sommet src
    while (temp != NULL && strcmp(temp->vertex, dst) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // Si l'arête n'existe pas
    if (temp == NULL) {
        printf("Aucune arête trouvée entre %s et %s\n", src, dst);
        return;
    }

    // Si l'arête est la première de la liste
    if (prev == NULL) {
        graph->adjLists[i] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
}



// Fonction pour créer un voisin
Neighbor* createNeighbor(char* vertex) {
    Neighbor* newNeighbor = malloc(sizeof(Neighbor));
    newNeighbor->vertex = vertex;
    newNeighbor->next = NULL;
    return newNeighbor;
}

// Fonction pour obtenir les voisins d'un sommet
Neighbor* getNeighbors(Graph* graph, char* src) {
    // Trouver le noeud source
    Node* srcNode = getVertex(graph, src);
    if (srcNode == NULL) {
        printf("Sommet source non trouvé.\n");
        return NULL;
    }

    // Créer une liste de voisins
    Neighbor* neighbors = NULL;
    Neighbor* last = NULL;

    Node* temp = srcNode;
    while (temp != NULL) {
        
        Neighbor* newNeighbor = createNeighbor(temp->vertex);

        
        if (neighbors == NULL) {
            neighbors = newNeighbor;
        } else {
            last->next = newNeighbor;
        }
        last = newNeighbor;

        temp = temp->next;
    }

    return neighbors;
}



// int main() {
//     Graph* graph = createGraph(3);
//     graph->vertices[0] = "A";
//     graph->vertices[1] = "B";
//     graph->vertices[2] = "C";

//     addEdge(graph, "A", "B", 1, maFonction);
//     addEdge(graph, "A", "B", 4, maFonction_2); //Cette ligne écrase la précédente
//     addEdge(graph, "B", "A", 4, maFonction_3);
//     addEdge(graph, "B", "C", 2, maFonction);
//     printGraph(graph);

//     printf("Before delete\n");

//     deleteEdge(graph, "B", "A");

//     printf("After delete\n");
//     printGraph(graph);
//     printNeighbors(graph, "A");

//     FunctionPointer func = getFunction(graph, "A", "B"); // renvoie maFonction_2

    
//     if (func != NULL) {
//         func();
//     }
    

//     return 0;
// }

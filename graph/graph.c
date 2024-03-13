#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include"str2.h"



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



void maFonction() {
    printf("Ceci est une fonction stockée dans un sommet.\n");
}

void maFonction_2(){
    printf("nill");
}

void maFonction_3(){
    printf("");
}

void printGraph(Graph* graph) {
    Dl_info info;
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        while (temp) {
            dladdr(temp->func, &info);
            printf("%s -> %s [Fonction : %s]\n", graph->vertices[v], temp->vertex, info.dli_sname);
            temp = temp->next;
        }
    }
}

Node* getVertex(Graph* graph, char* name) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcmp(graph->vertices[i], name) == 0) {
            return graph->adjLists[i];
        }
    }
    return NULL;
}

void getNeighbors(Graph* graph, char* name) {
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

FunctionPointer getFunction(Graph* graph, char* name) {
    Node* vertex = getVertex(graph, name);
    if (vertex == NULL) {
        printf("Sommet non trouvé.\n");
        return NULL;
    }
    return vertex->func;
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




int main() {
    Graph* graph = createGraph(3);
    graph->vertices[0] = "A";
    graph->vertices[1] = "B";
    graph->vertices[2] = "C";

    addEdge(graph, "A", "B", 1, maFonction);
    addEdge(graph, "A", "B", 4, maFonction_2);
    addEdge(graph, "B", "A", 4, maFonction_3);
    addEdge(graph, "B", "C", 2, maFonction);
    printGraph(graph);

    printf("Before delete\n");

    deleteEdge(graph, "B", "A");

    printf("After delete\n");
    printGraph(graph);
    getNeighbors(graph, "A");

    FunctionPointer func = getFunction(graph, "A");

    
    if (func != NULL) {
        func();
    }
    

    return 0;
}

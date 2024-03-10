#include <stdio.h>
#include <stdlib.h>
#incldude"graph.h"




// Fonction pour créer un nœud
Node* create_Node(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour créer un graphe
Graph* create_Graph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    // Allocation de la mémoire pour les listes d'adjacence
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));

    // Initialisation des listes d'adjacence à NULL
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Fonction pour ajouter une arête à un graphe non orienté
void add_edge(struct Graph* graph, int src, int dest) {
    // Ajout d'une arête de src à dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Comme le graphe est non orienté, on ajoute également une arête de dest à src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Fonction pour afficher le graphe
void print_Graph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("Adjacency list of vertex %d\n ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


void get_neighbors(struct Graph* graph, int vertex) {
    struct Node* temp = graph->adjLists[vertex];
    printf("Neighbors of vertex %d are: ", vertex);
    while (temp) {
        printf("%d ", temp->vertex);
        temp = temp->next;
    }
    printf("\n");
}

//int main() {
//    int vertices = 5;
//    struct Graph* graph = createGraph(vertices);
//    addEdge(graph, 0, 1);
//    addEdge(graph, 0, 4);
//    addEdge(graph, 1, 2);
//    addEdge(graph, 1, 3);
//    addEdge(graph, 1, 4);
//    addEdge(graph, 2, 3);
//    addEdge(graph, 3, 4);
//
//    printGraph(graph);
//    getNeighbors(graph, 1);
//
//    return 0;
//}

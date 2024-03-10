#include <stdio.h>
#include <stdlib.h>
#incldude"graph.h"





// Fonction pour créer un nœud
Node* create_Node(int v, int weight) { // Modification pour inclure le poids
    Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = weight; // Initialisation du poids
    newNode->vertex_function = vertex_function;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour créer un graphe
Graph* create_Graph(int vertices) {
    Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
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
void add_edge(struct Graph* graph, int src, int dest, int weight, bool (*vertex_function(void))) { // Modification pour inclure le poids
    // Ajout d'une arête de src à dest
    Node* newNode = createNode(dest, weight, vertex_function); // Création du nœud avec le poids
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Comme le graphe est non orienté, on ajoute également une arête de dest à src
    newNode = createNode(src, weight); // Création du nœud avec le poids
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Fonction pour afficher le graphe
void print_Graph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("Adjacency list of vertex %d\n ", v);
        while (temp) {
            printf("%d (%d) -> ", temp->vertex, temp->weight); // Affichage du poids
            temp = temp->next;
        }
        printf("\n");
    }
}

Node *get_neighbors(struct Graph* graph, int vertex) {
    // Renvoie un pointeur vers le premier nœud de la liste d'adjacence de ce sommet.
    return graph->adjLists[vertex];
}

//int main() {
//    int vertices = 5;
//    struct Graph* graph = createGraph(vertices);
//    addEdge(graph, 0, 1, 10); // Ajout de poids
//    addEdge(graph, 0, 4, 5);  // Ajout de poids
//    addEdge(graph, 1, 2, 8);  // Ajout de poids
//    addEdge(graph, 1, 3, 12); // Ajout de poids
//    addEdge(graph, 1, 4, 4);  // Ajout de poids
//    addEdge(graph, 2, 3, 7);  // Ajout de poids
//    addEdge(graph, 3, 4, 3);  // Ajout de poids
//
//    printGraph(graph);
//
//    return 0;
//}






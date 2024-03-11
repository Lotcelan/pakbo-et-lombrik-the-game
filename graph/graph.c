#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#incldude"graph.h"
#include"list.h"





// Fonction pour créer un nœud
Node* create_Node(int v, int weight) { // Modification pour inclure le poids
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = weight; // Initialisation du poids
    newNode->vertex_function = vertex_function;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour créer un graphe
Graph* create_Graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Allocation de la mémoire pour les listes d'adjacence
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));

    // Initialisation des listes d'adjacence à NULL
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Fonction pour ajouter une arête à un graphe non orienté
void add_edge(Graph* graph, int src, int dest, int weight, bool (*vertex_function(void))) { // Modification pour inclure le poids
    // Ajout d'une arête de src à dest
    Node* newNode = createNode(dest, weight, vertex_function); // Création du nœud avec le poids
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Comme le graphe est non orienté, on ajoute également une arête de dest à src
    newNode = createNode(src, weight); // Création du nœud avec le poids
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void print_Node(Node *node) {
    if(node == NULL){
        printf("NULL\n");
        return;
    }
    printf("%d -> ",node->vertex);
    print_node(node->next);
}

// Fonction pour afficher le graphe
void print_Graph(Graph* graph) {
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

Node* get_Node_from_Graph(Graph* graph, int vertex) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* current = graph->adjLists[i];
        while (current != NULL) {
            if (current->vertex == vertex) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL; // Retourne NULL si le nœud n'est pas trouvé
}

Node *get_neighbors(Graph* graph, int vertex) {
    // Renvoie un pointeur vers le premier nœud de la liste d'adjacence de ce sommet.
    return graph->adjLists[vertex];
}

void print_neighbors(Graph* graph, int vertex) {
    Node *head = get_neighbors(graph, vertex);
    print_Node(head);
    return;
}

bool has_edge(Graph* graph, int src, int dest) {
    Node *src_neighbors = get_neighbors(graph, src);
    while(src_neigbors != NULL){
        if(src_neibors->vertex == dest){
            return true;
        }
        src_neighbors = src_neigbors->next;
    }
    return false;
    
}

List *get_vertex_sprites(Graph* graph, int vertex) {
    Node *node = get_Node_from_Graph(graph, vertex);
    return node->sprites
}

void delete_edge(Graph* graph, int src, int dest) {
    // Suppression de l'arête de src à dest
    Node* prev = NULL;
    Node* curr = graph->adjLists[src];
    while (curr != NULL && curr->vertex != dest) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != NULL) {
        if (prev != NULL) {
            prev->next = curr->next;
        } else {
            graph->adjLists[src] = curr->next;
        }
        free(curr);
    }

    // Suppression de l'arête de dest à src
    prev = NULL;
    curr = graph->adjLists[dest];
    while (curr != NULL && curr->vertex != src) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != NULL) {
        if (prev != NULL) {
            prev->next = curr->next;
        } else {
            graph->adjLists[dest] = curr->next;
        }
        free(curr);
    }
}

bool (*get_vertex_function(Node* node))(void) {
    
}

//int main() {
//    int vertices = 5;
//    struct Graph* graph = createGraph(vertices);
//    addEdge(graph, 0, 1, 10);
//    addEdge(graph, 0, 4, 5);  
//    addEdge(graph, 1, 2, 8);
//    addEdge(graph, 1, 3, 12);
//    addEdge(graph, 1, 4, 4);
//    addEdge(graph, 2, 3, 7);
//    addEdge(graph, 3, 4, 3);
//
//    printGraph(graph);
//
//    return 0;
//}






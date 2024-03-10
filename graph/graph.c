#include"graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


AdjListNode* newAdjListNode(char *dest, float weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = strdup(dest);
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


Graph* createGraph(int num_vertices, bool directed) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->directed = directed;

    graph->array = (AdjList*)malloc(num_vertices * sizeof(AdjList));

    for (int i = 0; i < num_vertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(Graph* graph, char *src, char *dest, float weight) {
    // Ajouter une arête de src à dest
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Si le graphe n'est pas orienté, ajouter également une arête de dest à src
    if (!graph->directed) {
        newNode = newAdjListNode(src, weight);
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->num_vertices; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %s\n head ", graph->array[v].head->dest);
        while (pCrawl) {
            printf("-> %s(%.2f)", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Exemple d'utilisation

//int main() {
//    int num_vertices = 5;
//    Graph* graph = createGraph(num_vertices, false);
//
//    addEdge(graph, "A", "B", 2.5);
//    addEdge(graph, "A", "C", 1.8);
//    addEdge(graph, "B", "D", 3.2);
//
//    printGraph(graph);
//
//    return 0;
//}



// Structure pour un nœud d'une liste d'adjacence
typedef struct AdjListNode {
    char *dest;
    float weight;
    struct AdjListNode* next;
} AdjListNode;

// Structure pour représenter une liste d'adjacence
typedef struct {
    AdjListNode *head;
} AdjList;


typedef struct {
    int num_vertices;
    bool directed;
    AdjList* array;
} Graph;


AdjListNode* newAdjListNode(char *dest, float weight);

Graph* createGraph(int num_vertices, bool directed);

void addEdge(Graph* graph, char *src, char *dest, float weight);

void printGraph(Graph* graph);



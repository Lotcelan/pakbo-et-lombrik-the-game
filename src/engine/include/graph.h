
// Définition de la structure pour un noeud
typedef void (*FunctionPointer)(void);

typedef struct Node {
    char* vertex;
    int weight;
    struct Node* next;
    FunctionPointer func;  // Ajout d'un pointeur de fonction
} Node;

// Structure pour une liste de voisins
//(en vrai il faut le remplacer par les listes chainées de Flo, mais pour ca faut merge...)
typedef struct Neighbor {
    char* vertex;
    struct Neighbor* next;
} Neighbor;

// Définition de la structure pour le graphe
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    char** vertices;
} Graph;

void addEdge(Graph* graph, char* src, char* dest, int weight, FunctionPointer func);



Graph* createGraph(int vertices);

Node* createNode(char* vertex, int weight, FunctionPointer func);

void printGraph(Graph* graph);

FunctionPointer getFunction(Graph* graph, char* src, char* dst);

void printNeighbors(Graph* graph, char* name);

Node* getVertex(Graph* graph, char* name); 

int hasEdge(Graph* graph, char* vertex_src, char* vertex_dest);

void maFonction(void);
void maFonction_2(void);
void maFonction_3(void);

void deleteEdge(Graph* graph, char* src, char* dst);

Neighbor* createNeighbor(char* vertex);

Neighbor* getNeighbors(Graph* graph, char* src);





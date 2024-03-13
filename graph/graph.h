
// Définition de la structure pour un noeud
typedef void (*FunctionPointer)();

typedef struct Node {
    char* vertex;
    int weight;
    struct Node* next;
    FunctionPointer func;  // Ajout d'un pointeur de fonction
} Node;

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

FunctionPointer getFunction(Graph* graph, char* name);

void getNeighbors(Graph* graph, char* name);

Node* getVertex(Graph* graph, char* name);

int hasEdge(Graph* graph, char* vertex_src, char* vertex_dest);

void maFonction();
void maFonction_2();
void maFonction_3();

void deleteEdge(Graph* graph, char* src, char* dst);



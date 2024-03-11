

// Structure de nœud pour la liste d'adjacence
struct _Node {
    int vertex;
    int weight;
    List *sprites;
    bool (*vertex_function(void);
    struct _Node* next;
};

// Structure de graphe
struct _Graph {
    int numVertices;
    struct _Node** adjLists; //tableau de pointeurs vers les listes d'adjacence. Chaque élément du tableau pointe vers le premier nœud de la liste d'adjacence d'un sommet particulier.
};

typedef struct _Node Node;

typedef struct _Graph Graph;

Node* create_Node(int v, bool (*vertex_function(voide)));

Graph* create_Graph(int vertices);

void add_edge(Graph* graph, int src, int dest);

void print_Node(Node *node);

void print_Graph(Graph* graph);

Node* get_Node_from_Graph(Graph* graph, int vertex);

Node *get_neighbors(Graph* graph, int vertex);

void print_neighbors(Graph* graph, int vertex);

bool has_edge(Graph* graph, int src, int dest);

void delelete_edge(Graph* graph, char *src, char *dest);



List *get_vertex_sprites(Graph* graph, int vertex);

bool (*get_vertex_function(Node* node))(void);


float get_weight(Graph* graph, char *src, char *dest);





#include "../include/grid_graph.h"

int idx(int x, int y, GridGraph* g) {
    return y * g->w + x;
}

GridGraph* create_grid_graph(int w, int h) {
    GridGraph* graph = malloc(sizeof(GridGraph));
    graph->w = w;
    graph->h = h;
    graph->nodes = malloc(sizeof(GridNode*) * w * h);
    
    for (int i = 0; i < w * h; i++) {
        graph->nodes[i] = malloc(sizeof(GridNode));
        graph->nodes[i]->x = i % w;
        graph->nodes[i]->y = i / w;
        graph->nodes[i]->value = NULL;
        graph->nodes[i]->destroy_value = NULL;
    }
    
    return graph;
}


GridNode* get_grid_node(int x, int y, GridGraph* g) {
    if (g == NULL) return NULL;
    if (x >= 0 && x < g->w && y >= 0 && y < g->h) {
        return g->nodes[idx(x, y, g)];
    }
    return NULL;
}

void update_value_of_grid_node(int x, int y, void* value, void (*destroy_value)(void* v), GridGraph* g) {
    if (g == NULL) return;
    GridNode* node = get_grid_node(x, y, g);
    if (node != NULL) {
        if (node->destroy_value != NULL) {
            node->destroy_value(node->value); // on ne détruit que la value, pas besoin de casser tout le noeud
        }

        node->value = value;
        node->destroy_value = destroy_value;
    }
}

GridNode** get_neighbours(int x, int y, GridGraph* g) {
    if (g == NULL) return NULL;
    GridNode** neighbours = malloc(sizeof(GridNode*) * 8);
    
    // Get the neighbours in the cardinal directions
    neighbours[0] = get_grid_node(x, y - 1, g); // Up    
    neighbours[1] = get_grid_node(x + 1, y - 1, g); // Up-Right
    neighbours[2] = get_grid_node(x + 1, y, g); // Right
    neighbours[3] = get_grid_node(x + 1, y + 1, g); // Down-Right
    neighbours[4] = get_grid_node(x, y + 1, g); // Down
    neighbours[5] = get_grid_node(x - 1, y + 1, g); // Down-Left
    neighbours[6] = get_grid_node(x - 1, y, g); // Left
    neighbours[7] = get_grid_node(x - 1, y - 1, g); // Up-Left
    
    return neighbours;
}

void display_grid_graph_bool(GridGraph* g) {
    if (g == NULL) {
        return;
    }
    for (int y = 0; y < g->h; y++) {
        for (int x = 0; x < g->w; x++) {
            GridNode* node = get_grid_node(x, y, g);
            if (node != NULL) {
                if (node->value != NULL) {
                    printf("%i ", *(bool*)(node->value));
                } else {
                    printf("-1 ");
                }
            }
        }
        printf("\n");
    }
}

void display_grid_graph_float(GridGraph* g) {
    if (g == NULL) {
        return;
    }
    for (int y = 0; y < g->h; y++) {
        for (int x = 0; x < g->w; x++) {
            GridNode* node = get_grid_node(x, y, g);
            if (node != NULL) {
                if (node->value != NULL) {
                    printf("%f ", *(float*)(node->value));
                } else {
                    printf("-1 ");
                }
            }
        }
        printf("\n");
    }
}

void display_grid_graph_grid_node_coords(GridGraph* g) {
    if (g == NULL) {
        return;
    }
    for (int y = 0; y < g->h; y++) {
        for (int x = 0; x < g->w; x++) {
            GridNode* node = get_grid_node(x, y, g);
            if (node != NULL) {
                if (node->value != NULL) {
                    printf("(%d %d)", ((GridNode*)(node->value))->x, ((GridNode*)(node->value))->y);
                } else {
                    printf("(-1 -1)");
                }
            }
        }
        printf("\n");
    }   
}

void destroy_grid_graph(GridGraph* g) {
    if (g == NULL) return;
    for (int i = 0; i < g->w * g->h; i++) {
        GridNode* node = g->nodes[i];
        if (node->destroy_value != NULL) {
            node->destroy_value(node->value);
        }
        free(node);
    }
    free(g->nodes);
    free(g);
}

void destroy_grid_node(void* n) {
    if (n == NULL) return;
    GridNode* node = (GridNode*) n;
    if (node->destroy_value != NULL) {
        node->destroy_value(node->value);
    }
    // printf("deleting : %i %i\n", node->x, node->y);
    // if (node != NULL) free(node); // Il faudrait vérifier di destroy_value destroy le noeud ou pas. Faut prier que oui
    
}

GridNode* copy_grid_node(GridNode* n) {
    if (n == NULL) {
        return NULL;
    }
    GridNode* new = (GridNode*)malloc(sizeof(GridNode));
    new->destroy_value = n->destroy_value;
    new->value = n->value;
    new->x = n->x;
    new->y = n->y;

    return new;
}

// bool are_grid_node_equal(void* n1, void* n2) {

// }
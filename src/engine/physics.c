#include "./include/physics.h"

Structure* do_the_moves(GameData* game, Entity* e, int delta_x, int delta_y) {
    // On peut avoir besoin de modifier la position en fonction dx ou dy hors de update_entity_movement

    Structure* result = NULL;
    int sign_x = delta_x > 0 ? 1 : -1;
    int sign_y = delta_y > 0 ? 1 : -1;
    delta_x = abs(delta_x);
    delta_y = abs(delta_y);

    bool is_colliding = false;
    bool has_collided = false;

    while (delta_x >= 0) {
        // e->x_position = e->x_position + sign_x * delta_x;
        // printf("Je pourrai être en X : %d\n", e->x_position);
        // update_entity_boxes(e, prev_x, prev_y);
        // temp_prev = e->x_position;
        change_entity_coordinates(e, e->x_position + sign_x * delta_x, e->y_position);
        Structure* s = is_entity_colliding_with_structures(e, game->current_scene->structures);
        if (s != NULL) {
            is_colliding = true;
            has_collided = true;
            result = s;
        } else {
            break;
        }
        if (is_colliding) {
            change_entity_coordinates(e, e->prev_collision_box->zone.x, e->prev_collision_box->zone.y);

            // update_entity_boxes(e, temp_prev, prev_y);
            // prev_x = e->x_position;
            delta_x--; // d'ici a ce qu'on fasse du raymarching :)
            is_colliding = false;
            if (strcmp(result->teleport_to_scene, "none") != 0 && e == game->player) {
                change_scene(game, result->teleport_to_scene);
                return result;
            }
        }
    }
    if (has_collided) {
        e->x_velocity = 0;
    }
    has_collided = false;
    is_colliding = false;

    while (delta_y >= 0) {
        // e->y_position = e->y_position + sign_y * delta_y;
        // printf("Je pourrai être en Y : %d, delta = %d\n", e->y_position, delta_y);
        // update_entity_boxes(e, prev_x, prev_y);
        // temp_prev = e->y_position;
        change_entity_coordinates(e, e->x_position, e->y_position + sign_y * delta_y);
        Structure* s = is_entity_colliding_with_structures(e, game->current_scene->structures);
        if (s != NULL) {
            is_colliding = true;
            has_collided = true;
            result = s;
        } else {
            break;
        }
        if (is_colliding) {
            // e->y_position = prev_y;
            // update_entity_boxes(e, prev_x, temp_prev);
            change_entity_coordinates(e, e->x_position, e->prev_collision_box->zone.y);
            // prev_y = e->y_position;
            delta_y--; // d'ici a ce qu'on fasse du raymarching :)
            is_colliding = false;
            if (strcmp(result->teleport_to_scene, "none") != 0 && e == game->player) {
                change_scene(game, result->teleport_to_scene);
                return result;
            }
            
        }
    }
    if (has_collided) {
        e->y_velocity = 0;
    }

    return result;
}

Structure* update_entity_movement(GameData* game, Entity* e, float delta_t, bool gravity_enabled) {
    // returns NULL if no collision or the structure there was collision with
    
    if (gravity_enabled) {
        update_gravity(game, e, delta_t);
    }
    if (game->current_scene == NULL) {
        return false;
    }

    if ((e->x_velocity == 0 && e->y_velocity == 0) || (e->x_position == -1 && e->y_position == -1)) {
        return false;
    }

    // int prev_x = e->x_position;
    // int prev_y = e->y_position;
    
    // todo : normalisation de la vitesse en diagonale avec un /sqrt(2)
    // int delta_x = floor(delta_t * e->x_velocity / 1000); // delta_t en ms
    // int sign_x = delta_x > 0 ? 1 : -1;
    // for (int current = 0; current < delta_x; current++) {
    //     e->x_position = e->x_position + delta_x + sign_x * current;
    //     update_entity_boxes(e);
        
    //     if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
    //         e->x_position = prev_x;
    //         update_entity_boxes(e);
    //         continue;
    //     }
    //     break;
    // }
    // int delta_y = floor(delta_t * e->y_velocity / 1000); // delta_t en ms
    // int sign_y = delta_y > 0 ? 1 : -1;
    // for (int current = 0; current < delta_y; current++) {
    //     e->y_position = e->y_position + delta_y + sign_y * current;
    //     printf("Prev : %d, Current : %d, Delta : %d\n", prev_y, e->y_position, delta_y);
    //     update_entity_boxes(e);
    //     if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
    //         e->y_position = prev_y;
    //         update_entity_boxes(e);
    //         continue;
    //     }
    //     break;
    // }
    int delta_x, delta_y;
    Structure* result = NULL;
    // double velocityMagnitude = sqrt(e->x_velocity * e->x_velocity + e->y_velocity * e->y_velocity);
    // if (velocityMagnitude > 0) {
    //     double normalizedXVelocity = e->x_velocity / velocityMagnitude;
    //     double normalizedYVelocity = e->y_velocity / velocityMagnitude;

    //     delta_x = delta_t * normalizedXVelocity / 1000; // delta_t en ms
    //     delta_y = delta_t * normalizedYVelocity / 1000; // delta_t en ms
    // }
    // printf("Delta X : %d, Delta Y : %d\n", delta_x, delta_y);

    double modifier_multiplier = 1;
    Modifier* m = get_entity_modifier(e, SPEED_HOOF);
    if (m != NULL) {
        modifier_multiplier += 0.15 * m->quantity;
    }

    m = get_entity_modifier(e, BALL_AND_CHAIN);
    if (m != NULL) {
        modifier_multiplier -= 0.15 * m->quantity;
    }

    delta_x = delta_t * e->x_velocity * modifier_multiplier / 1000; // delta_t en ms
    delta_y = delta_t * e->y_velocity * modifier_multiplier / 1000; // delta_t en ms

    result = do_the_moves(game, e, delta_x, delta_y);
    
    return result;

}

void update_gravity(GameData* game, Entity* e, float delta_t) {
    // just changes the y velocity to add gravity
    if (game->current_scene == NULL) {
        return;
    }

    float gravity = 300;
    e->y_velocity += gravity * delta_t / 1000;
    // if (is_entity_colliding_with_structures(e, game->current_scene->structures)) {
    //     e->y_position = prev_y;
    //     update_entity_boxes(e, e->x_position, prev_y);
    // }
    
}

void follow_player(GameData* game, Entity* e, int x_speed, int y_speed) {
    // will change the velocity of the entity e to follow game->player
    (void) y_speed;
    if (game->current_scene == NULL) {
        return;
    }
    Entity* player = game->player;
    if (player == NULL) {
        return;
    }
    int player_x = player->x_position;
    int e_x = e->x_position;
    if (player_x > e_x) {
        e->x_velocity = x_speed;
    } else if (player_x < e_x) {
        e->x_velocity = -x_speed;
    } else {
        e->x_velocity = 0;
    }
    // if (player_y > e_y) {
    //     e->y_velocity = y_speed;
    // } else if (player_y < e_y) {
    //     e->y_velocity = -y_speed;
    // } else {
    //     e->y_velocity = 0;
    // }

}

float heuristic_a_star(int x1, int y1, int x2, int y2) {
    // distnace à vol d'oiseau
    
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

GridGraph* create_grid_graph_from_game(GameData* game, Entity* entity_from) {
    // on a besoin de l'entité source pour ajouter une "marge" autour des structure pour pas qu'elle se "cogne" dedans
    // on a besoin d'ajouter la marge que sur le côté nord et ouest (car (x,y) = point supérieur gauche de l'entité)
    
    GridGraph* result = create_grid_graph(game->width_amount, game->height_amount);

    if (game->current_scene == NULL || entity_from == NULL) return NULL;

    int x_margin = entity_from->sprite->width / CELL_WIDTH - 1;
    int y_margin = entity_from->sprite->height / CELL_HEIGHT - 1;

    if (x_margin == -1) x_margin++; // pour le cas des entités qui ont une collision plus petite qu'une case, vu qu'on n'a pas assez de précision on prend de la marge
    if (y_margin == -1) y_margin++;

    List* current = game->current_scene->structures;
    while (current != NULL) {
        Box* coll = ((Structure*)current->value)->collision_box;
        if (coll == NULL) {
            current = current->next;
            continue;
        }
        int x_from = coll->zone.x / CELL_WIDTH - x_margin;
        int y_from = coll->zone.y / CELL_HEIGHT - y_margin;

        int x_end = (coll->zone.x + coll->zone.w) / CELL_WIDTH;
        int y_end = (coll->zone.y + coll->zone.h) / CELL_HEIGHT;

        // "remplir" la zone de 0, on ne peut pas passer

        // printf("From : (%d, %d), To : (%d, %d)\n", x_from, y_from, x_end, y_end);

        for (int x = x_from; x <= x_end; x++) {
            for (int y = y_from; y <= y_end; y++) {
                bool* val = (bool*)malloc(sizeof(bool));
                *val = false;
                update_value_of_grid_node(x,y, val, free, result);
            }
        }
        current = current->next;
    }

    // on remplie le reste avec des 1 pour dire qu'on peut passer
    for (int x = 0; x < game->width_amount; x++) {
        for (int y = 0; y < game->height_amount; y++) {
            GridNode* current = get_grid_node(x, y, result);
            if (current != NULL) {
                if (current->value != NULL) {
                    if (*((bool*)(current->value)) == false) {
                        continue;
                    }
                }
            }
            bool* val = (bool*)malloc(sizeof(bool));
            *val = 1;
            update_value_of_grid_node(x,y, val, free, result);
        }
    }

    return result;
}


void print_binary_heap_grid_node(binary_heap* bh) {
    if (bh == NULL) return;
    printf("[ ");
    for (int i = 0; i < bh->size; i++) {
        GridNode* n = (GridNode*)((binary_heap_basic_entry*)bh->array[i])->value;
        printf("(%i %i) ", n->x, n->y);
    }
    printf("]\n");

}

bool compare_grid_node_game(void* n1, void* n2) {
    if (n1 == n2) {
        return true; // litterally same object (can be NULL)
    }
    if (n1 == NULL || n2 == NULL) {
        return false;
    }
    binary_heap_basic_entry* e1 = (binary_heap_basic_entry*)n1;
    GridNode* node1 = (GridNode*)(e1->value); // dans le contexte dans lequel on l'appelera, on compare une entrée binary heap et un voisin
    GridNode* node2 = (GridNode*)n2;

    if (node1->x == node2->x && node1->y == node2->y && node1->destroy_value == node2->destroy_value) {
        bool* val1 = node1->value;
        bool* val2 = node2->value;
        if (val1 == val2) {
            return true;
        } else if (val1 == NULL || val2 == NULL) {
            return false;
        } else {
            return *val1 == *val2;
        }
    } else {
        return false;
    }
}


GridGraph* a_star(Entity* entity_from, Entity* entity_to, GameData* game) {
    // Renvoie un graphe donc chaque élément (g->nodes[index]->value) est UN POINTEUR GridNode* vers SON PARENT dans le parcours de A*

    if (entity_from == NULL || entity_to == NULL) {
        return NULL;
    }

    binary_heap* pqueue = binary_heap_create(game->width_amount * game->height_amount, binary_heap_basic_entry_compare); // contiendra les GridNode*
    // binary_heap* pqueue = binary_heap_create(game->width_amount * game->height_amount, binary_heap_basic_entry_compare, binary_heap_basic_entry_free); // contiendra les GridNode*

    int x_from = (entity_from->collision_box->zone.x + entity_from->sprite->width / 2)  / CELL_WIDTH;
    int y_from = (entity_from->collision_box->zone.y + entity_from->sprite->height / 2) / CELL_HEIGHT;


    int x_to = (entity_to->collision_box->zone.x + entity_to->sprite->width / 2) / CELL_WIDTH;
    int y_to = (entity_to->collision_box->zone.y + entity_to->sprite->height / 2) / CELL_HEIGHT;

    if (x_from < 0 || x_from >= game->width_amount || y_from < 0 || y_from >= game->height_amount || 
        x_to < 0 || x_to >= game->width_amount || y_to < 0 || y_to >= game->height_amount) {
            return NULL;
    }

    GridGraph* distances = create_grid_graph(game->width_amount, game->height_amount);
    for (int x = 0; x < game->width_amount; x++) {
        for (int y = 0; y < game->height_amount; y++) {
            float* val = malloc(sizeof(float));
            if (x == x_from && y == y_from) {
                *val = 0.0;
            } else {
                *val = INFINITY;
            }
            update_value_of_grid_node(x, y, val, free, distances);
        }
    }
    GridGraph* origins = create_grid_graph(game->width_amount, game->height_amount); // Chaque value est un GridNode avec le x,y de son parent et une value de NULL
    for (int x = 0; x < game->width_amount; x++) {
        for (int y = 0; y < game->height_amount; y++) {
            update_value_of_grid_node(x, y, copy_grid_node(get_grid_node(x, y, origins)), destroy_grid_node, origins); // au début, tout le monde est sa propre origine
        }
    }



    GridGraph* game_graph = create_grid_graph_from_game(game, entity_from);
    // display_grid_graph_bool(game_graph);

    // A PARTIR DE MAINTEANT ON FAIT CONFIRANCE A L'UNVIERS ET JE CHECK PAS QUE TOUT CE QUI EST RENVOYE EST NON NULL
    // [Modifier ceci petit à petit] Temps de débug supplémentaire à cause de cette flemme : 50min

    binary_heap_basic_entry* initial = create_binary_heap_basic_entry(get_grid_node(x_from, y_from, game_graph), *(float*)(get_grid_node(x_from, y_from, distances)->value));
    // binary_heap_basic_entry* initial = create_binary_heap_basic_entry(get_grid_node(x_from, y_from, game_graph), *(float*)(get_grid_node(x_from, y_from, distances)->value), destroy_grid_node);
    binary_heap_insert(pqueue, initial);

    while (!is_binary_heap_empty(pqueue)) {
        // print_binary_heap_grid_node(pqueue);
        binary_heap_basic_entry* current = binary_heap_extract(pqueue);
        GridNode* current_node = (GridNode*)current->value;
        int x_current = current_node->x;
        int y_current = current_node->y;

        if (x_current == x_to && y_current == y_to) {
            return origins;
        }

        GridNode** neighbours = get_neighbours(x_current, y_current, game_graph);
        // display_grid_graph_float(distances);
        for (int i = 0; i < 8; i++) {
            // printf("%p\n", get_grid_node(x_current, y_current, distances));
            // printf("%d %d\n", x_current, y_current);
            if (neighbours[i] == NULL) {
                continue;
            }

            if (*((bool*)neighbours[i]->value) == false) {
                continue;
            }

            float distance_to_current = *(float*)(get_grid_node(x_current, y_current, distances)->value);
            float distance_to_neighbour = *(float*)(get_grid_node(neighbours[i]->x, neighbours[i]->y, distances)->value);

            float weight = (i == 0 || i == 2 || i == 4 || i == 6) ? 1.0 : 1.4; // en diagonale c'est sqrt(2) la distance :)
            // printf("%f %f %f\n", distance_to_current, weight, distance_to_neighbour);
            if (distance_to_current + weight < distance_to_neighbour) {
                // printf("salut\n");
                float* new_distance = malloc(sizeof(float));
                *new_distance = distance_to_current + weight;
                update_value_of_grid_node(neighbours[i]->x, neighbours[i]->y, new_distance, free, distances); // on a trouvé une meilleure distance

                update_value_of_grid_node(neighbours[i]->x, neighbours[i]->y, copy_grid_node(get_grid_node(x_current, y_current, origins)), destroy_grid_node, origins); // et donc on change le parent

                float* heuristic_distance = malloc(sizeof(float));
                *heuristic_distance = *new_distance + heuristic_a_star(neighbours[i]->x, neighbours[i]->y, x_to, y_to);
                if (is_present_in_binary_heap(pqueue, neighbours[i], compare_grid_node_game)) {
                    binary_heap_modify(pqueue, neighbours[i], create_binary_heap_basic_entry(neighbours[i], *heuristic_distance), compare_grid_node_game);
                    // binary_heap_modify(pqueue, neighbours[i], create_binary_heap_basic_entry(neighbours[i], *heuristic_distance, destroy_grid_node), compare_grid_node_game);
                } else {
                    binary_heap_insert(pqueue, create_binary_heap_basic_entry(neighbours[i], *heuristic_distance));
                    // binary_heap_insert(pqueue, create_binary_heap_basic_entry(neighbours[i], *heuristic_distance, destroy_grid_node));
                }
            }
        }
    }

    // si on n'a rien trouvé
    return NULL;
}
void follow_player_using_a_star(GameData* game, Entity* e, int x_speed, int y_speed) {
    GridGraph* path = a_star(e, game->player, game);
    // display_grid_graph_grid_node_coords(path);

    if (path == NULL) {
        return;
    }

    int x_to = game->player->collision_box->zone.x / CELL_WIDTH;
    int y_to = game->player->collision_box->zone.y / CELL_HEIGHT;

    GridNode* current = get_grid_node(x_to, y_to, path);
    if (current == NULL) return;
    GridNode* previous = current;
    // display_grid_graph_grid_node_coords(path);
    
    while (current != NULL) {
        // Circle* c = init_circle(current->x * CELL_WIDTH + CELL_WIDTH / 2, current->y * CELL_HEIGHT + CELL_HEIGHT / 2, 5, (SDL_Color){255, 0, 0, 255});
        // push_render_stack_circle(game, c, true); // pour le debug
        
        GridNode* next = get_grid_node(((GridNode*)current->value)->x, ((GridNode*)current->value)->y, path);
        // if ( ((GridNode*)next->value)->x == e->collision_box->zone.x / CELL_WIDTH && ((GridNode*)next->value)->y == e->collision_box->zone.y / CELL_HEIGHT) {
        //     break;
        // }

        if (next == NULL) {
            break;
        }

        if ( current->x == next->x && current->y == next->y ) {
            break;
        }


        previous = current;
        current = next;
    }

    // Circle* c = init_circle(previous->x * CELL_WIDTH + CELL_WIDTH / 2, previous->y * CELL_HEIGHT + CELL_HEIGHT / 2, 5, (SDL_Color){0, 255, 0, 255});
    // push_render_stack_circle(game, c, true); // pour le debug


    x_to = previous->x * CELL_WIDTH;
    y_to = previous->y * CELL_HEIGHT;

    if (e->collision_box->zone.x < x_to) {
        e->x_velocity = x_speed;
    } else if (e->collision_box->zone.x > x_to) {
        e->x_velocity = -x_speed;
    } else {
        e->x_velocity = 0;
    }
    

    if (e->collision_box->zone.y < y_to) {
        e->y_velocity = y_speed;
    } else if (e->collision_box->zone.y > y_to) {
        e->y_velocity = -y_speed;
    } else {
        e->y_velocity = 0;
    }
}
bool detect_player(GameData* game, Entity* e, int radius) {
    // will change the velocity of the entity e to follow game->player
    if (game->current_scene == NULL) {
        return false;
    }
    Entity* player = game->player;
    if (player == NULL) {
        return false;
    }
    int player_x = player->x_position;
    int e_x = e->x_position;
    if (e_x - player_x < radius && player_x < e_x) {
        return true; 
    }

    if (player_x - e_x < radius + CELL_WIDTH && player_x > e_x + CELL_WIDTH) {
        return true; 
    }
    return false;
}
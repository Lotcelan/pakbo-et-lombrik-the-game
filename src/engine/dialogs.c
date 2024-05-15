#include "./include/dialogs.h"

Dialog* init_dialog(char* message, char* font_name, List* options, List* branches, Dialog* previous) {
    Dialog* dialog = (Dialog*)malloc(sizeof(Dialog));
    if (dialog == NULL) {
        exit(-1);
    }
    dialog->message = message;
    dialog->font_name = font_name;
    dialog->options = options;
    dialog->branches = branches;
    dialog->previous = previous;
    dialog->selected_option = 0;
    return dialog;
}

// Dialog* create_dialog_from_format(char* format) {
//     // Format : "|message;font_name;option1;option2|message2;font_name2;option1|message3;font_name3|message4;font_name4|"
//     // Avec message à l'origine de message 1 et message 4. 
//     // Et message2 à l'origine de message 3

//     // On commence par séparer les messages
//     char* saveptr;
//     char* message = strtok_r(format, "|", &saveptr);
//     char* root_message = message;
//     Dialog* root = NULL;
//     Dialog* current = NULL;
//     while (message != NULL) {
//         // On sépare les éléments
//         char* saveptr2;
//         char* message_elements = strtok_r(message, ";", &saveptr2);
//         char* message = message_elements;
//         char* font_name = strtok_r(NULL, ";", &saveptr2);
//         List* options = NULL;
//         List* branches = NULL;
//         while (message_elements != NULL) {
//             message_elements = strtok_r(NULL, ";", &saveptr2);
//             if (message_elements != NULL) {
//                 if (options == NULL) {
//                     options = append_first(strdup(message_elements), options);
//                 } else {
//                     branches = append_first(create_dialog_from_format(message_elements), branches);
//                 }
//             }
//         }
//         if (root == NULL) {
//             root = init_dialog(strdup(root_message), strdup(font_name), options, branches, NULL);
//             current = root;
//         } else {
//             current->branches = append_first(init_dialog(strdup(message), strdup(font_name), options, branches, root), current->branches);
//             current = current->branches->data;
//         }
//         message = strtok_r(NULL, "|", &saveptr);
//     }

// }

Dialog* create_dialog_from_json(json_t* root, Dialog* previous) {
    const char* message = json_string_value(json_object_get(root, "message"));
    const char* font_name = json_string_value(json_object_get(root, "font_name"));
    List* options = NULL;
    List* branches = NULL;
    
    Dialog* result = init_dialog(strdup(message), strdup(font_name), options, branches, previous);

    json_t* options_json = json_object_get(root, "options");
    size_t index;
    json_t* value;
    json_array_foreach(options_json, index, value) {
        options = append_first(strdup(json_string_value(value)), options);
    }
    result->options = reverse(options);
    json_t* branches_json = json_object_get(root, "branches");
    index = 0;
    value = NULL;
    json_array_foreach(branches_json, index, value) {
        branches = append_first(create_dialog_from_json(value, result), branches);
    }

    result->branches = reverse(branches);

    return result;
}

Dialog* get_dialog_from_json(const char* dialog_name) {
    // Fonction à utiliser pour charger un dialogue : juste indiquer l'entrée dans le json dialogs.json et ca renvoie l'objet Dialog* à mettre dand game->current_dialog


    FILE *file = fopen("./dialogs.json", "r");

    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return NULL;
    }

    json_error_t error;
    json_t *root = json_loadf(file, 0, &error);
    fclose(file);

    
    if (root == NULL) {
        return NULL;
    }

    json_t* dialog_j = json_object_get(root, dialog_name);
    if (dialog_j == NULL) {
        return NULL;
    }


    return create_dialog_from_json(dialog_j, NULL);
}

void dialog_event_handler(GameData* game) {
    if (game->current_dialog == NULL) {
        return;
    }

    if (game->event.type == SDL_KEYDOWN) {
        if (game->event.key.keysym.sym == SDLK_RETURN) {

            if (game->current_dialog->branches == NULL) {
                destroy_dialog(game->current_dialog);
                game->current_dialog = NULL;
            } else {
                // On affiche le premier branch pour tester
                Dialog* next = get_i_element(game->current_dialog->branches, game->current_dialog->selected_option); // Changer la logique de head
                if (next == NULL) {
                    destroy_dialog(game->current_dialog);
                }
                game->current_dialog = next;
                game->current_dialog->selected_option = 0;
            }
        }
        if (game->event.key.keysym.sym == SDLK_UP) {
            if (game->current_dialog->selected_option > 0) {
                game->current_dialog->selected_option--;
            }
        }
        if (game->event.key.keysym.sym == SDLK_DOWN) {
            if (game->current_dialog->selected_option < length(game->current_dialog->options) - 1) {
                game->current_dialog->selected_option++;
            }
        }
    }
}

void update_dialog(GameData* game) {
    (void)game;
    return;
}

void render_dialog(GameData* game) {

    // On  ne peut avoir qu'un seul dialoge à la fois, donc on utilise celui de game
    if (game->current_dialog == NULL) {
        return;
    }

    render_no_destroy(game); // On "freeze" le temps

    int win_h, win_w; 
    SDL_RenderGetLogicalSize(game->renderer, &win_w, &win_h); // On récupère la taille de la fenêtre (en pixels

    // Create a rectangle that takes up half the screen
    Rectangle* box = init_rectangle(CELL_WIDTH, CELL_HEIGHT, win_w - CELL_WIDTH*2, win_h / 2, (SDL_Color){10, 10, 255, 255}, (SDL_Color){10, 10, 75, 255});
    render_rectangle(game, box);

    TTF_Font* font = (TTF_Font*)get(game->fonts, game->current_dialog->font_name, strcmp);

    if (font == NULL) {
        fprintf(stderr, "Font not found\n");
        return;
    }

    SDL_Color color = (SDL_Color){255, 255, 255, 255};

    // Display the message within the box
    Text* text = init_text(game, game->current_dialog->message, color, box->x + 5, box->y + 5, font);
    render_wrap_text(game, text, box->w - CELL_WIDTH);

    // Display the dialog's options line by line underneath the box
    int option_y = box->y + box->h;
    int i = 0;
    for (List* h = game->current_dialog->options; h != NULL; h = tail(h)) {
        if (i == game->current_dialog->selected_option) {
            int r = sin(SDL_GetTicks() / 100.0) * 50 + 255 - 50;
            color = (SDL_Color){255, 0, 0, r};
        } else {
            color = (SDL_Color){255, 255, 255, 255};
        }
        Text* option_text = init_text(game, head(h), color, CELL_WIDTH, option_y, font);
        render_text(game, option_text);
        option_y += CELL_HEIGHT; // Move the y-coordinate down for the next option
        i++;
    }

}


void destroy_dialog(void* d) {

    if (d == NULL) {
        return;
    }
    Dialog* dialog = (Dialog*)d;


    // Go up to the root
    Dialog* current = dialog;

    while (current->previous != NULL) {
        current = current->previous;
    }
    destroy_dialog_down(current);
}

void destroy_dialog_down(void* d) {
    Dialog* dialog = (Dialog*)d;
    
    if (dialog == NULL) {
        return;
    }

    if (dialog->message != NULL) {
        free(dialog->message);
    }
    if (dialog->font_name != NULL) {
        free(dialog->font_name);
    }
    if (dialog->options != NULL) {
        list_delete(dialog->options, free); // On free des char*
    }
    if (dialog->branches != NULL) {
        list_delete(dialog->branches, destroy_dialog_down); // On free des Dialog*
    }
    free(dialog);
}

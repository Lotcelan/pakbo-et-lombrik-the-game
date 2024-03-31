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
    printf("begin\n");
    json_array_foreach(options_json, index, value) {
        printf("Adding %s\n", json_string_value(value));
        options = append_first(strdup(json_string_value(value)), options);
    }
    printf("affecting : %p\n", options);
    result->options = options;
    json_t* branches_json = json_object_get(root, "branches");
    index = 0;
    value = NULL;
    json_array_foreach(branches_json, index, value) {
        branches = append_first(create_dialog_from_json(value, result), branches);
    }

    result->branches = branches;

    printf("In the end %p\n", result->options);
    return result;
}

Dialog* get_dialog_from_json(const char* dialog_name) {

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
                Dialog* next = head(game->current_dialog->branches); // Changer la logique de head
                if (next == NULL) {
                    destroy_dialog(game->current_dialog);
                }
                game->current_dialog = next;
            }
        }
    }
}

void update_dialog(GameData* game) {
    return;
}

void render_dialog(GameData* game) {

    // On  ne peut avoir qu'un seul dialoge à la fois, donc on utilise celui de game
    if (game->current_dialog == NULL) {
        return;
    }

    render_no_destroy(game); // On "freeze" le temps

    int win_h, win_w; 
    SDL_GetWindowSize(game->window, &win_w, &win_h);
    

    Rectangle* blur = init_rectangle(0, 0, win_w, win_h, (SDL_Color){0, 0, 0, 128}, (SDL_Color){0, 0, 0, 128});
    render_rectangle(game, blur);

    TTF_Font* font = (TTF_Font*)get(game->fonts, game->current_dialog->font_name, strcmp);


    SDL_Color color = {255, 255, 255, 255};
    // On affiche le message
    Text* text = init_text(game, game->current_dialog->message, color, 0, 0, font);
    render_text(game, text);

}


void destroy_dialog(void* d) {

    Dialog* dialog = (Dialog*)d;

    if (dialog == NULL) {
        return;
    }

    // Go up to the root
    Dialog* current = dialog;

    while (current->previous != NULL) {
        current = current->previous;
    }
    destroy_dialog_down(current);
}

void destroy_dialog_down(void* d) {
    Dialog* dialog = (Dialog*)d;
    
    printf("e\n");
    if (dialog == NULL) {
        return;
    }
    if (dialog->branches != NULL) {
        printf("d\n");
        list_delete(dialog->branches, destroy_dialog_down); // On free des Dialog*
    }

    if (dialog->message != NULL) {
        printf("a\n");
        free(dialog->message);
    }
    if (dialog->font_name != NULL) {
        printf("b\n");
        free(dialog->font_name);
    }
    if (dialog->options != NULL) {
        printf("c\n");
        print_list(dialog->options); // On free des char*
        list_delete(dialog->options, free); // On free des char*
    }
    free(dialog);
}
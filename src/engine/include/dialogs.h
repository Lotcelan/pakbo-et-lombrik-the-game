#ifndef DIALOGS_H
#define DIALOGS_H

#include "game.h"

typedef struct GameData GameData;

typedef struct Dialog {
    char* message;
    char* font_name;
    List* options; // Liste de char*
    List* branches; // Liste de Dialog*
    struct Dialog* previous; // Pour détruire les dialogue, si NULL on est la racine
    int selected_option;
} Dialog;

Dialog* init_dialog(char* message, char* font_name, List* options, List* branches, Dialog* previous);
void destroy_dialog(void* d);
void destroy_dialog_down(void* d);

Dialog* create_dialog_from_json(json_t* root, Dialog* previous);
Dialog* get_dialog_from_json(const char* dialog_name);
void dialog_event_handler(GameData* game);
void render_dialog(GameData* game);
void update_dialog(GameData* game);



#endif
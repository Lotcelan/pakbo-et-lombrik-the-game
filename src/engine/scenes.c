#include "include/scenes.h"
#include "include/game.h"

Structure* init_structure(GameData* game, char* identifier, char* resource, int x, int y, int allow_pass_through, char* teleport_to_scene) {
    Structure* s = (Structure*)malloc(sizeof(Structure));
    if (s == NULL) {
        exit(-1);
    }
    s->identifier = identifier;
    s->texture = loadTextureFromMemory(game, resource);
    s->position.x = x;
    s->position.y = y;
    SDL_QueryTexture(s->texture, NULL, NULL, &s->position.w, &s->position.h);

    s->allow_pass_through = allow_pass_through;
    s->teleport_to_scene = teleport_to_scene;
    return s;
}

void init_scene_with_json(GameData* game, json_t *root, Scene* scene) {
    const char *name = json_string_value(json_object_get(root, "name"));
    const char *background = json_string_value(json_object_get(root, "background"));

    strcpy(scene->background, background);

    printf("Name: %s\n", name);
    printf("Background: %s\n", background);

    json_t* structures = json_object_get(root, "structures");
    size_t index;
    json_t* value;

    json_array_foreach(structures, index, value) {
        int x = json_integer_value(json_object_get(value, "x"));
        int y = json_integer_value(json_object_get(value, "y"));
        char *resource = json_string_value(json_object_get(value, "resource"));
        int allow_pass_through = json_integer_value(json_object_get(value, "allow_pass_through"));
        char *teleport_to_scene = json_string_value(json_object_get(value, "teleport_to_scene"));

        printf("Structure %zu: x=%d, y=%d, resource=%s, allow_pass_through=%d, teleport_to_scene=%s\n",
               index, x, y, resource, allow_pass_through, teleport_to_scene);
        
        Structure* s = init_structure(game, json_string_value(json_object_get(value, "identifier")),
                                      resource,
                                      json_integer_value(json_object_get(value, "x")),
                                      json_integer_value(json_object_get(value, "y")),
                                      json_integer_value(json_object_get(value, "allow_pass_through")),
                                      json_string_value(json_object_get(value, "teleport_to_scene")));

        scene->structures = append_first(s, scene->structures);
    }

    json_t* entities = json_object_get(root, "entities");
    List* entities_list = NULL;

    json_array_foreach(entities, index, value) {
        Entity* e = init_entity(json_string_value(json_object_get(value, "entity")),
                                json_integer_value(json_object_get(value, "respawn_delay")),
                                json_integer_value(json_object_get(value, "x")),
                                json_integer_value(json_object_get(value, "y")));
        append(e, &entities_list);
        int x = json_integer_value(json_object_get(value, "x"));
        int y = json_integer_value(json_object_get(value, "y"));
        int respawn_delay = json_integer_value(json_object_get(value, "respawn_delay"));
        const char *entity = json_string_value(json_object_get(value, "entity"));

        printf("Entity %zu: x=%d, y=%d, respawn_delay=%d, entity=%s\n",
               index, x, y, respawn_delay, entity);
    }
}

Scene* init_scene(GameData* game, char* title) {
    Scene* new = (Scene*)malloc(sizeof(Scene));

    if (new == NULL) {
        exit(-1);
    }

    strcpy(new->title, title);

    // The path to the json file is in ../src/scenes/{title}/data.json

    char* path = (char*)malloc(strlen(title) + 25);
    json_error_t error;
    
    if (path == NULL) {
        exit(-1);
    }
    strcpy(path, "../src/scenes/");
    strcat(path, title);
    strcat(path, "/data.json");
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return NULL;
    }
    printf("hey\n");
    json_t *root = json_loadf(file, 0, &error);
    printf("heyoo\n");
    fclose(file);
    printf("Loaded JSON data:\n");
    json_dumpf(root, stdout, JSON_INDENT(4));
    new->entities = NULL;
    new->structures = NULL;

    if (root) {
        init_scene_with_json(game, root, new);
        json_decref(root);
    }
    if (!root) {
        fprintf(stderr, "JSON error on line %d: %s\n", error.line, error.text);
        return NULL;
    }

    return new;

}

void render_scene(GameData* game, float delta) {
    // Using game->renderer, render the scene : the background then all the textures

    // Load the background texture contained in game->current_scene->background and resize it to width and height of the window
    // Then render it at (0, 0)
    // delta is the tick time between previous frame and current frame

    int width, height;
    SDL_GetWindowSize(game->window, &width, &height);
    
    SDL_Texture* backgroundTexture = loadTextureFromMemory(game, game->current_scene->background);
    if (backgroundTexture == NULL) {
        fprintf(stderr, "Failed to load background texture\n");
        return;
    }

    // Get the dimensions of the background texture
    int backgroundWidth, backgroundHeight;
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundWidth, &backgroundHeight);

    // Calculate the scale factors to resize the background texture
    float scaleX = (float)width / backgroundWidth;
    float scaleY = (float)height / backgroundHeight;

    // Render the background texture
    SDL_Rect backgroundRect = {0, 0, width, height};
    SDL_RenderCopyEx(game->renderer, backgroundTexture, NULL, &backgroundRect, 0, NULL, SDL_FLIP_NONE);

    // Clean up
    SDL_DestroyTexture(backgroundTexture);


    // Render all the structures
    List* current = game->current_scene->structures;
    while (current != NULL) {
        printf("aleeed\n");
        Structure* s = (Structure*)current->value;
        if (s == NULL) {
            break;
        }
        SDL_Rect rect = s->position;
        SDL_RenderCopy(game->renderer, s->texture, NULL, &rect);
        current = current->next;
    }

    // Render all the entities
    // /!\ PAS ENCORE TESTÉ /!\ 
    List* liste_entites = game->current_scene->entities;
    Entity* e;
    Sprite* sprite;
    while (liste_entites != NULL){
        e = liste_entites->value;
        sprite = get_sprite(e);
        // on met a jour l'animation de l'entité, en général :
            // soit on change l'état de e en fonction de conditions relatives à l'entité e en question
            // soit (si on n'a pas changé d'etat) on met a jour le sprite de e (le timer notamment)
        sprite->update_sprite(e, delta);
        
        // zone de la sprite sheet à afficher
        // rappel : sprite->frames est une liste de coordonnées
        SDL_Rect spriteRect = {.x = sprite->frames->value[0]*sprite->width, .y = sprite->frames->value[1]*sprite->height, .w = sprite->width, .h = sprite->height};
        // position du sprite à l'écran
        SDL_Rect destRect = {.x = e->x_position, .y = e->y_position, .w = sprite->width, .h = sprite->height};
        // On affiche la bonne frame au bon endroit
        SDL_RenderCopy(game->renderer, sprite->spriteSheet, spriteRect, destRect);
    }
}

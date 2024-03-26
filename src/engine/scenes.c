#include "include/scenes.h"
#include "include/game.h"

void init_scene_with_json(GameData* game, json_t *root, Scene* scene) {
    const char *name = json_string_value(json_object_get(root, "name"));
    const char *background = json_string_value(json_object_get(root, "background"));

    strcpy(scene->background, background);

    // printf("Name: %s\n", name);
    // printf("Background: %s\n", background);

    json_t* structures = json_object_get(root, "structures");
    size_t index;
    json_t* value;

    json_array_foreach(structures, index, value) {
        // int x = json_integer_value(json_object_get(value, "x"));
        // int y = json_integer_value(json_object_get(value, "y"));
        char *resource = json_string_value(json_object_get(value, "resource"));
        // int allow_pass_through = json_integer_value(json_object_get(value, "allow_pass_through"));
        // char *teleport_to_scene = json_string_value(json_object_get(value, "teleport_to_scene"));

        // printf("Structure %zu: x=%d, y=%d, resource=%s, allow_pass_through=%d, teleport_to_scene=%s\n",
            //    index, x, y, resource, allow_pass_through, teleport_to_scene);
        
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

        // printf("Entity %zu: x=%d, y=%d, respawn_delay=%d, entity=%s\n",
        //        index, x, y, respawn_delay, entity);
    }
}

Scene* init_scene(GameData* game, char* title) {
    Scene* new = (Scene*)malloc(sizeof(Scene));

    new->render_stack = NULL;

    if (new == NULL) {
        exit(-1);
    }
    HashTable* objects = createHashTable(15);
    if (objects == NULL) {
        exit(-1);
    }
    new->objects = objects;


    strcpy(new->title, title);

    // The path to the json file is in ../src/scenes/{title}/data.json

    char* path = (char*)malloc(strlen(title) + strlen("./scenes/.json") + 1);
    json_error_t error;
    
    if (path == NULL) {
        exit(-1);
    }
    strcpy(path, "./scenes/");
    strcat(path, title);
    strcat(path, ".json");
    FILE *file = fopen(path, "r");

    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return NULL;
    }
    json_t *root = json_loadf(file, 0, &error);
    fclose(file);
    // json_dumpf(root, stdout, JSON_INDENT(4));
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
    new->screen_shake = NULL;
    return new;

}

void render_scene(GameData* game, float delta) {
    // Using game->renderer, render the scene : the background then all the textures

    // Load the background texture contained in game->current_scene->background and resize it to width and height of the window
    // Then render it at (0, 0)
    // delta is the tick time between previous frame and current frame


    if (game->current_scene->screen_shake != NULL) {
        ScreenShake* shake = game->current_scene->screen_shake;
        if (shake->time < shake->duration) {
            int shakeOffsetX = ((int)(sin(shake->time) * shake->intensity));
            int shakeOffsetY = ((int)(sin(shake->time) * shake->intensity));
            printf("Shake offset: %d, %d\n", shakeOffsetX, shakeOffsetY);

            SDL_RenderSetLogicalSize(game->renderer, CELL_WIDTH * game->width_amount + shakeOffsetX, CELL_HEIGHT * game->height_amount );
            shake->time++;
        } else {
            SDL_RenderSetLogicalSize(game->renderer, CELL_WIDTH * game->width_amount, CELL_HEIGHT * game->height_amount);
            destroy_screen_shake(game);
        }
    } else {
        SDL_RenderSetLogicalSize(game->renderer, CELL_WIDTH * game->width_amount, CELL_HEIGHT * game->height_amount);
    }
    render_stack(game);
    // Render all the entities
    // /!\ PAS ENCORE TESTÉ
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

void free_scene(Scene* scene) {
    // Free all the entities and structures of the scene
    if (scene->screen_shake != NULL) {
        free(scene->screen_shake);
    }
    list_delete(scene->entities, free_entity);
    list_delete(scene->structures, free_structure);
    free(scene);
}






ScreenShake* init_screen_shake(int duration, int intensity) {
    ScreenShake* s = (ScreenShake*)malloc(sizeof(ScreenShake));
    if (s == NULL) {
        exit(-1);
    }
    s->duration = duration;
    s->intensity = intensity;
    s->time = 0;
    return s;
}

void destroy_screen_shake(GameData* game) {
    Scene* scene = game->current_scene;
    if (scene->screen_shake != NULL) {
        free(scene->screen_shake);
        scene->screen_shake = NULL;
    }
}

void change_scene(GameData* game, char* next) {
    Scene* next_scene = get(game->scenes, next, strcmp);
    if (next_scene == NULL) {
        fprintf(stderr, "Scene %s not found\n", next);
        return;
    }
    destroy_render_stack(game);
    game->current_scene = next_scene;
    game->current_scene->populate(game);
}


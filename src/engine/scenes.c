#include "include/scenes.h"
#include "include/game.h"

void init_scene_with_json(json_t *root, Scene* scene) {
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
        const char *texture = json_string_value(json_object_get(value, "texture"));
        int allow_pass_through = json_integer_value(json_object_get(value, "allow_pass_through"));
        const char *teleport_to_scene = json_string_value(json_object_get(value, "teleport_to_scene"));

        printf("Structure %zu: x=%d, y=%d, texture=%s, allow_pass_through=%d, teleport_to_scene=%s\n",
               index, x, y, texture, allow_pass_through, teleport_to_scene);
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

Scene* init_scene(char* title) {
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
        return 1;
    }
    printf("hey\n");
    json_t *root = json_loadf(file, 0, &error);
    printf("heyoo\n");
    fclose(file);
    printf("Loaded JSON data:\n");
    json_dumpf(root, stdout, JSON_INDENT(4));

    if (root) {
        init_scene_with_json(root, new);
        json_decref(root);
    }
    if (!root) {
        fprintf(stderr, "JSON error on line %d: %s\n", error.line, error.text);
        return 1;
    }

    // Do something with the loaded JSON data
    // For example, printing it

    return new;

}

SDL_Texture* load_texture(SDL_Renderer* renderer, char* img_path) {
    // Load the image located at img_path and return it as an SDL_Texture
    // If the image cannot be loaded, return NULL
    SDL_Surface* surface = IMG_Load(img_path);
    if (surface == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", img_path);
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        fprintf(stderr, "Failed to create texture from surface: %s\n", img_path);
        return NULL;
    }

    SDL_FreeSurface(surface);
    return texture;


}

void render_scene(GameData* game) {
    // Using game->renderer, render the scene : the background then all the textures

    // Load the background texture contained in game->current_scene->background and resize it to width and height of the window
    // Then render it at (0, 0)

    int width, height;
    SDL_GetWindowSize(game->window, &width, &height);

    // Load the background texture in ../assets/{game->current_scene->background} 
    char* background_path = (char*)malloc(strlen(game->current_scene->background) + 14);
    strcpy(background_path, "../src/assets/");
    strcat(background_path, game->current_scene->background);
    
    SDL_Texture* backgroundTexture = load_texture(game->renderer, background_path);
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
}


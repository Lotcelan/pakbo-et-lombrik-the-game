#include "include/game.h"

GameData* init_game(int width_amount, int height_amount, int final_width, int final_height, const char* title, int capped_fps) {
    // Init the window of the game that is in a grid layout
    // of cells that are CELL_WIDTHxCELL_HEIGHT pixels, with width_amount cells
    // for the width and height_amount cells for the height

    GameData* gameData = (GameData*)malloc(sizeof(GameData));

    gameData->state = CHANGING;
    SDL_Window* window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          final_width, final_height,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    // Init resources
    HashTable* resources = init_resources();
    gameData->resources = resources;

    // displayHashTableResource(resources);

    HashTable* fonts = createHashTable(10);
    gameData->fonts = fonts;

    HashTable* scenes = createHashTable(10);
    gameData->scenes = scenes;

    HashTable* entities = createHashTable(10);
    gameData->entities = entities;

    HashTable* weapons = createHashTable(10);
    gameData->weapons = weapons;

    gameData->event = (SDL_Event){0};
    gameData->window = window;
    gameData->renderer = renderer;
    gameData->current_scene = NULL;
    gameData->current_dialog = NULL;

    gameData->width_amount = width_amount;
    gameData->height_amount = height_amount;
    // Init framerate manager
    FrameRateManager* frm = init_frm(capped_fps);
    gameData->frm = frm;
    gameData->deltaT = 0;

    gameData->player = NULL;

    SDL_RenderSetLogicalSize(renderer, CELL_WIDTH * width_amount, CELL_HEIGHT * height_amount);
    gameData->keyboardState = SDL_GetKeyboardState(NULL);

    return gameData;

}

void free_game(GameData* gameData) {
    destroyFrameRateManager(gameData->frm);
    destroyHashTable(gameData->resources);
    destroyHashTable(gameData->fonts);
    destroyHashTable(gameData->scenes);
    destroyHashTable(gameData->entities);
    destroyHashTable(gameData->weapons);
    SDL_DestroyRenderer(gameData->renderer);
    SDL_DestroyWindow(gameData->window);
    destroy_dialog(gameData->current_dialog);
    // free(gameData->keyboardState); jsuis con c'est un const
    free_entity(gameData->player);
    free(gameData);
}

void event_handler(GameData* gameData) {
    while (SDL_PollEvent(&(gameData->event)) != 0) {
        if ((gameData->event).type == SDL_QUIT) {
            gameData->state = CLOSING;
        }

    }
}



void set_dir(void) {
    char path[1024];
    char *exec_path;

#if defined(_WIN32) || defined(_WIN64)
    _get_pgmptrs(&exec_path);
#elif defined(__APPLE__)
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        exec_path = path;
    } else {
        perror("_NSGetExecutablePath");
        exit(EXIT_FAILURE);
    }
#else
    ssize_t length = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (length != -1) {
        path[length] = '\0';
        exec_path = path;
    } else {
        perror("readlink");
        exit(EXIT_FAILURE);
    }
#endif

    char *dir = dirname(exec_path);
    if (chdir(dir) != 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }
}

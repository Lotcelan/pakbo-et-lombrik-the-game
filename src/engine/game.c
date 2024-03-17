#include "include/game.h"

GameData* init_game(int width_amount, int height_amount, int final_width, int final_height, const char* title, int capped_fps) {
    // Init the window of the game that is in a grid layout
    // of cells that are CELL_WIDTHxCELL_HEIGHT pixels, with width_amount cells
    // for the width and height_amount cells for the height

    GameData* gameData = (GameData*)malloc(sizeof(GameData));

    gameData->state = LOADING;
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

    displayHashTableResource(resources);

    gameData->event = (SDL_Event){0};
    gameData->window = window;
    gameData->renderer = renderer;
    gameData->current_scene = NULL;

    gameData->final_width = final_width;
    gameData->final_height = final_height;
    // Init framerate manager
    FrameRateManager* frm = init_frm(capped_fps);
    gameData->frm = frm;

    SDL_RenderSetLogicalSize(renderer, CELL_WIDTH * width_amount, CELL_HEIGHT * height_amount);

    return gameData;

}

void free_game(GameData* gameData) {
    destroyFrameRateManager(gameData->frm);
    destroyHashTable(gameData->resources);
    SDL_DestroyRenderer(gameData->renderer);
    SDL_DestroyWindow(gameData->window);
    free(gameData);
}

void event_handler(GameData* gameData) {
    while (SDL_PollEvent(&(gameData->event)) != 0) {
        if ((gameData->event).type == SDL_QUIT) {
            gameData->state = CLOSING;
        }

    }
}

void upscale_render(GameData* gameData) {
    // Upscale the render to the window size

    SDL_RenderSetLogicalSize(gameData->renderer, gameData->final_width, gameData->final_height);
}

void downscale_render(GameData* gameData) {
    // Upscale the render to the window size
    int width, height;
    SDL_GetWindowSize(gameData->window, &width, &height);
    SDL_RenderSetLogicalSize(gameData->renderer, width, height);
}
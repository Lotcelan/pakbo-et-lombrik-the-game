#include "include/game.h"

GameData* init_game(int width, int height, const char* title, int capped_fps) {
    GameData* gameData = (GameData*)malloc(sizeof(GameData));

    gameData->state = LOADING;
    SDL_Window* window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
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

    // Init framerate manager
    FrameRateManager* frm = init_frm(capped_fps);
    gameData->frm = frm;

    return gameData;

}

void free_game(GameData* gameData) {
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
#include<SDL2/SDL.h>

struct _player_t{
    char *name;
    int x_position;
    int y_position;
    int *pv;
    int *state;
    int *double_jump;
    int *direction;
    int *speed;
    SDL_Texture* sprite;

};

typedef struct _player_t _player_t;


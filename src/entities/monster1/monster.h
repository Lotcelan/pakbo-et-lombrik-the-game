#include<SDL2/SDL.h>
struct _monster_t{
    char *name;
    int *pv;
    int x_position;
    int y_position;
    SDL_Texture* sprite;

};

typedef struct _monster_t monster_t;


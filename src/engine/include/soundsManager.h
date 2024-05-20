#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct MusicManager {
    Mix_Music *currentMusic;
} MusicManager;

MusicManager* initMusicManager();

void playMusic(MusicManager* manager, const char* filename);

void pauseMusic();

void resumeMusic();

void setMusicVolume(MusicManager* manager, int volume);
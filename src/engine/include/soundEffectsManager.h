#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
    Mix_Chunk* currentEffect;
} SoundEffectManager;

SoundEffectManager* initSoundEffectManager();

void playSoundEffect(SoundEffectManager* manager, const char* filename);

void setSoundEffectVolume(SoundEffectManager* manager, int volume);
void destroySoundEffectsManager(SoundEffectManager* manager);
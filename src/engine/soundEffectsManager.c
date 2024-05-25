#include "include/soundEffectsManager.h"



SoundEffectManager* initSoundEffectManager() {
    SoundEffectManager* manager = (SoundEffectManager*)malloc(sizeof(SoundEffectManager));
    manager->currentEffect = NULL;
    return manager;
}

void playSoundEffect(SoundEffectManager* manager, const char* filename) {
    if(manager->currentEffect != NULL) {
        Mix_FreeChunk(manager->currentEffect);
    }
    manager->currentEffect = Mix_LoadWAV(filename);
    if(manager->currentEffect == NULL) {
        printf("Sound Effect Error: %s\n", Mix_GetError());
    } else {
        Mix_PlayChannel(-1, manager->currentEffect, 0);
        printf("Sound effect played ! \n");
    }
}

void setSoundEffectVolume(SoundEffectManager* manager, int volume) {
    if(manager->currentEffect != NULL) {
        if(volume < 0) {
            volume = 0;
        } else if(volume > MIX_MAX_VOLUME) {
            volume = MIX_MAX_VOLUME;
        }
        Mix_VolumeChunk(manager->currentEffect, volume);
    }
}


void destroySoundEffectsManager(SoundEffectManager* manager){
    free(manager->currentEffect);
    free(manager);
}
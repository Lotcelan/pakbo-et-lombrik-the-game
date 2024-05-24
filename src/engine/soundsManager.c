#include "include/soundsManager.h"





MusicManager* initMusicManager() {
    MusicManager* manager = (MusicManager*)malloc(sizeof(MusicManager));
    manager->currentMusic = NULL;
    return manager;
}


void playMusic(MusicManager* manager, const char* filename) {
    if(manager->currentMusic != NULL) {
        Mix_FreeMusic(manager->currentMusic);
    }
    manager->currentMusic = Mix_LoadMUS(filename);
    if(manager->currentMusic == NULL) {
        printf("Music Error: %s", Mix_GetError());
    } else {
        Mix_PlayMusic(manager->currentMusic, -1);
    }
}


void pauseMusic() {
    if(Mix_PlayingMusic() != 0) {
        Mix_PauseMusic();
    }
}


void resumeMusic() {
    if(Mix_PausedMusic() != 0) {
        Mix_ResumeMusic();
    }
}

void setMusicVolume(MusicManager* manager, int volume) {
    if(manager->currentMusic != NULL) {
        
        if(volume < 0) {
            volume = 0;
        } else if(volume > 128) {
            volume = 128;
        }

        Mix_VolumeMusic(volume);
    }
}


#ifndef FRAMERATE_H
#define FRAMERATE_H

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdlib.h>

typedef struct Timer {
    bool started;
    bool paused;
    int startTime;
    int pausedTime;
} Timer;


typedef struct FrameRateManager {
    int cappedFPS;
    int currentFPS;
    Timer* timer;
} FrameRateManager;


// FrameRate functions
FrameRateManager* init_frm(int capped_fps);
void cap_fps(FrameRateManager* f);
int get_fps(FrameRateManager* f);


// Timer functions
Timer* init_timer();
void start_timer(Timer* t);
void stop_timer(Timer* t);
void pause_timer(Timer* t);
void unpause_timer(Timer* t);
int get_timer_ticks(Timer* t);
bool time_elapsed(Timer* t, int ms);


#endif
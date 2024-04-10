#include "include/framerate.h"

FrameRateManager* init_frm(int capped_fps) {
    FrameRateManager* frm = (FrameRateManager*)malloc(sizeof(FrameRateManager));
    frm->cappedFPS = capped_fps;
    frm->currentFPS = 0;
    frm->timer = init_timer();
    start_timer(frm->timer);
    return frm;
}


Timer* init_timer(void) {
    Timer* timer = (Timer*)malloc(sizeof(Timer));
    timer->started = false;
    timer->paused = false;
    timer->startTime = 0;
    timer->pausedTime = 0;
    return timer;
}

void start_timer(Timer* t) {
    t->started = true;
    t->paused = false;
    t->startTime = SDL_GetTicks();
}

void stop_timer(Timer* t) {
    t->started = false;
    t->paused = false;
}

void pause_timer(Timer* t) {
    if (t->started && !t->paused) {
        t->paused = true;
        t->pausedTime = SDL_GetTicks() - t->startTime;
    }
}

void unpause_timer(Timer* t) {
    if (t->paused) {
        t->paused = false;
        t->startTime = SDL_GetTicks() - t->pausedTime;
        t->pausedTime = 0;
    }
}

int get_timer_ticks(Timer* t) {
    if (t->started) {
        if (t->paused) {
            return t->pausedTime;
        } else {
            return t->startTime;
        }
    }
    return 0;
}

bool time_elapsed(Timer* t, int ms) {
    int elapsed = SDL_GetTicks() - get_timer_ticks(t);
    if (elapsed >= ms) {
        return true;
    }
    return false;
}

void cap_fps(FrameRateManager* frm) {
    int cap = (1000 / frm->cappedFPS);
    if (!time_elapsed(frm->timer, cap)) {
        // Delay until we are ready to continue.
        SDL_Delay(cap - (SDL_GetTicks() - frm->timer->startTime));
    }
    frm->timer->startTime = SDL_GetTicks();

}

int get_fps(FrameRateManager* frm) {
    return frm->cappedFPS;

}

void destroyFrameRateManager(FrameRateManager* frm) {
    free(frm->timer);
    free(frm);
}

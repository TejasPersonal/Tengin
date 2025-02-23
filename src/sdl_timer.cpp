#include "sdl.hpp"
#include <SDL3/SDL_timer.h>

void SDL::sleep(unsigned int milli_seconds) {
    SDL_Delay(milli_seconds);
}
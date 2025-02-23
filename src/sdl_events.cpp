#include "sdl.hpp"
#include <SDL3/SDL_init.h>

SDL::Events::Events() {
    initialized = SDL_InitSubSystem(SDL_INIT_EVENTS);
    if (!initialized) throw Error::INITIALIZATION;
}

SDL::Events::~Events () {
    if (initialized) SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void SDL::Events::quit() {
    if (initialized) SDL_QuitSubSystem(SDL_INIT_EVENTS);
    else {
        SDL_SetError("not initialized");
        throw Error::QUIT;
    }
    initialized = false;
}

bool SDL::Events::pollEvent(SDL_Event& event) {
    return SDL_PollEvent(&event);
}
void SDL::Events::waitEvent(SDL_Event& event) {
    if (!SDL_WaitEvent(&event)) { throw Error::POLL_EVENT; }
}
void SDL::Events::pushEvent(SDL_Event& event) {
    if (!SDL_PushEvent(&event)) { throw Error::PUSH_EVENT; };
}
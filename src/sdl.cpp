#include "sdl.hpp"
#include <SDL3/SDL_init.h>

SDL::SDL(): _quit_(false) {}

void SDL::quit() {
    if (_quit_) {
        SDL_SetError("not initialized");
        throw SDL::Error::QUIT;
    }
    SDL_Quit();
    _quit_ = true;
}

SDL::~SDL() { SDL_Quit(); }

SDL::Events SDL::initEvents() { return SDL::Events(); }

SDL::TTF SDL::initTTF() { return SDL::TTF(); }

void SDL::SimpleMessageBox::show() { if (!SDL_ShowSimpleMessageBox(flag, title, message, nullptr)) throw Error::SHOW; }

SDL::Video SDL::initVideo() { return SDL::Video(); }
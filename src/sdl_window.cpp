#include "sdl.hpp"
#include <SDL3/SDL_video.h>

SDL_DisplayID SDL::Video::Window::id() {
    auto id = SDL_GetWindowID(sdl);
    if (!id) throw Error::ID;
    return id;
}

SDL::Video::Window::Properties SDL::Video::Window::properties() {
    return SDL::Video::Window::Properties(sdl);
}

SDL::Video::Window::Window(const std::string& title, const math::d2::size<int> size, const SDL_WindowFlags& flags): die(true) {
    sdl = SDL_CreateWindow(title.c_str(), size.width, size.height, flags);
    if (!sdl) throw Error::CREATE;
}

SDL::Video::Window::Window(const Config& config): die(true) {
    sdl = SDL_CreateWindowWithProperties(config.id);
    if (!sdl) throw Error::CREATE;
}

SDL::Video::Window::Window(Config&& config): die(true) {
    sdl = SDL_CreateWindowWithProperties(config.id);
    if (!sdl) throw Error::CREATE;
}

void SDL::Video::Window::destroy() {
    if (die){
        if (sdl) {
            SDL_DestroyWindow(sdl);
            sdl = nullptr;
        }
        else {
            SDL_SetError("not valid");
            throw Error::DESTROY;
        }
    }
}

SDL::Video::Window::~Window() {
    if (die) if (sdl) SDL_DestroyWindow(sdl);
}

void SDL::Video::Window::show() {
    if (!SDL_ShowWindow(sdl)) throw Error::SHOW;
}

void SDL::Video::Window::hide() {
    if (!SDL_HideWindow(sdl)) throw Error::HIDE;
}

float SDL::Video::Window::scale() {
    float scale = SDL_GetWindowDisplayScale(sdl);
    if(scale == 0.0f) throw Error::GET_SCALE;
    return scale;
}

void SDL::Video::Window::setMinimumSize(const math::d2::size<int>& size) {
    if (!SDL_SetWindowMinimumSize(sdl, size.width, size.height)) throw Error::SET_MINIMUM_SIZE;
}
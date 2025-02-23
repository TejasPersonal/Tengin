#include "sdl.hpp"
#include <SDL3/SDL_init.h>

SDL::Video::Video () {
    initialized = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (!initialized) throw Error::INITIALIZATION;
}

void SDL::Video::quit() {
    if (initialized) SDL_QuitSubSystem(SDL_INIT_VIDEO);
    else {
        SDL_SetError("not initialized");
        throw Error::QUIT;
    }
    initialized = false;
}

SDL::Video::~Video () {
    if (initialized) SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL::Video::Window SDL::Video::createWindow(const std::string& title, const math::d2::size<int> size, const SDL_WindowFlags& flags) {
    return Window(title, size, flags);
}

SDL::Video::Window SDL::Video::createWindow(const SDL::Video::Window::Config& config) {
    return Window(config);
}

SDL::Video::Window SDL::Video::createWindow(SDL::Video::Window::Config&& config) {
    return Window(config);
}

SDL::Video::Renderer SDL::Video::createRenderer(const SDL::Video::Window& window, const std::string& api) {
    return SDL::Video::Renderer(window, api);
}
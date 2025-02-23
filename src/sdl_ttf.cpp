#include "sdl.hpp"

SDL::TTF::TTF() {
    initialized = TTF_Init();
    if (!initialized) throw Error::INITIALIZATION;
}

void SDL::TTF::quit() {
    if (initialized) TTF_Quit();
    else {
        SDL_SetError("not initialized");
        throw Error::QUIT;
    }
    initialized = false;
}

SDL::TTF::~TTF() {
    if (initialized) TTF_Quit();
}

SDL::TTF::Font SDL::TTF::loadFont(const char* file, float point_size) {
    return Font(file, point_size);
}

SDL::TTF::TextEngine SDL::TTF::createTextEngine(const SDL::Video::Renderer& renderer) {
    return TextEngine(renderer);
}
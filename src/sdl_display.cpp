#include "sdl.hpp"

SDL_DisplayID SDL::Video::primaryDisplay() {
    SDL_DisplayID id = SDL_GetPrimaryDisplay();
    if (!id) throw Error::GET_DISPLAY;
    return id;
}

const SDL_DisplayMode& SDL::Video::displayMode(const SDL_DisplayID& id) {
    auto mode = SDL_GetDesktopDisplayMode(id);
    if (!mode) throw Error::GET_DISPLAY_MODE;
    return *mode;
}
#include "sdl.hpp"

SDL::TTF::Font::Font(const char* file, float point_size) {
    font = TTF_OpenFont(file, point_size);
    if (!font) throw Error::LOAD;
}

void SDL::TTF::Font::destroy() {
    if (font){
        TTF_CloseFont(font);
        font = nullptr;
    }
    else {
        SDL_SetError("not valid");
        throw Error::DESTROY;
    }
}

SDL::TTF::Font::~Font() {
    if (font) TTF_CloseFont(font);
}

void SDL::TTF::Font::size(float point_size) {
    if (!TTF_SetFontSize(font, point_size)) throw Error::SET_SIZE;
}
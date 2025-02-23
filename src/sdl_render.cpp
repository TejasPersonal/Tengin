#include "sdl.hpp"

SDL::Video::Renderer::Renderer(const Window& window, const std::string& api) {
    sdl = SDL_CreateRenderer(window.sdl, api.c_str());
    if (!sdl) throw Error::CREATE;
}

void SDL::Video::Renderer::destroy() {
    if (sdl) {
        SDL_DestroyRenderer(sdl);
        sdl = nullptr;
    }
    else {
        SDL_SetError("not valid");
        throw Error::DESTROY;
    }
}

SDL::Video::Renderer::~Renderer() {
    if (sdl) SDL_DestroyRenderer(sdl);
}

SDL::Video::Renderer::Texture SDL::Video::Renderer::loadTexture(const char* file) {
    return Texture(*this, file);
}

bool SDL::Video::Renderer::renderTexture(
    const Texture& texture,
    const math::Rectangle<int>* destination,
    const math::Rectangle<int>* source
) {
    return SDL_RenderTexture(sdl, texture.texture, (SDL_FRect*) source, (SDL_FRect*) destination);
}

bool SDL::Video::Renderer::clear (const math::Color& color){
    return SDL_SetRenderDrawColor(sdl, color.red, color.green, color.blue, color.alpha) 
            &&
           SDL_RenderClear(sdl);
}
bool SDL::Video::Renderer::present (){
    return SDL_RenderPresent(sdl);
}
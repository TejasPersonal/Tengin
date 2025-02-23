#include "sdl.hpp"
#include <SDL3/SDL_image.h>

SDL::Video::Renderer::Texture::Texture(const Renderer& renderer, const char* file){
    texture = IMG_LoadTexture(renderer.sdl, file);
    if (!texture) throw Error::LOAD;
}

void SDL::Video::Renderer::Texture::destroy() {
    if (texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    else {
        SDL_SetError("Not valid");
        throw Error::DESTROY;
    }
}

SDL::Video::Renderer::Texture::~Texture() {
    if (texture) SDL_DestroyTexture(texture);
}
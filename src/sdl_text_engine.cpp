#include "sdl.hpp"

SDL::TTF::TextEngine::TextEngine(const Video::Renderer& renderer) {
    text_engine = TTF_CreateRendererTextEngine(renderer.sdl);
    if (!text_engine) throw  Error::CREATE;
}

void SDL::TTF::TextEngine::destroy(){
    if (text_engine) {
        TTF_DestroyRendererTextEngine(text_engine);
        text_engine = nullptr;
    }
    else {
        SDL_SetError("not valid");
        throw Error::DESTROY;
    }
}

SDL::TTF::TextEngine::~TextEngine() {
    if (text_engine) TTF_DestroyRendererTextEngine(text_engine);
}

SDL::TTF::TextEngine::Text SDL::TTF::TextEngine::createText(const Font& font, const std::string& text){
    return Text(text_engine, font, text);
}
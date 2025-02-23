#include "sdl.hpp"

SDL::TTF::TextEngine::Text::Text(TTF_TextEngine* text_engine, const Font& font, const std::string& text_) {
    ttf_text = TTF_CreateText(text_engine, font.font, text_.data(), text_.length());
    if (!ttf_text) throw Error::CREATE;
}

void SDL::TTF::TextEngine::Text::destroy() {
    if (ttf_text){
        TTF_DestroyText(ttf_text);
        ttf_text = nullptr;
    }
    else {
        SDL_SetError("Not valid");
        throw Error::DESTROY;
    }
}

SDL::TTF::TextEngine::Text::~Text() {
    if (ttf_text) TTF_DestroyText(ttf_text);
}

void SDL::TTF::TextEngine::Text::color(const math::Color& color) {
    if (!TTF_SetTextColor(ttf_text, color.red, color.green, color.blue, color.alpha)) throw Error::SET_COLOR;
}

void SDL::TTF::TextEngine::Text::draw(const math::d2::position<float> position){
    if (!TTF_DrawRendererText(ttf_text, position.x, position.y)) throw Error::DRAW;
}

void SDL::TTF::TextEngine::Text::text(const std::string& text) {
    if (!TTF_SetTextString(ttf_text, text.data(), text.length())) throw Error::SET_TEXT;
}
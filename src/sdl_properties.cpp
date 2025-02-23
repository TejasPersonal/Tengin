#include "sdl.hpp"
#include <SDL3/SDL_properties.h>

SDL::Video::Window::Properties::Properties (SDL_Window* window) {
    id = SDL_GetWindowProperties(window);
    if (!id) throw Error::CREATE;
}

void SDL::Video::Window::Properties::destroy() {
    if (id) SDL_DestroyProperties(id);
    else {
        SDL_SetError("not valid");
        throw Error::DESTROY;
    }
    id = 0;
}

SDL::Video::Window::Properties::~Properties () {
    if (id) SDL_DestroyProperties(id);
}

bool SDL::Video::Window::Properties::has(const std::string& property) {
    return SDL_HasProperty(id, ("SDL.window." + property).c_str());
}

SDL_PropertyType SDL::Video::Window::Properties::type(const std::string& property) {
    return SDL_GetPropertyType(id, ("SDL.window." + property).c_str());
}


bool SDL::Video::Window::Properties::get(const std::string& property, const bool& default_value) {
    return SDL_GetBooleanProperty(id, ("SDL.window." + property).c_str(), default_value);
}

float SDL::Video::Window::Properties::get(const std::string& property, const float& default_value) {
    return SDL_GetFloatProperty(id, ("SDL.window." + property).c_str(), default_value);
}

long long SDL::Video::Window::Properties::get(const std::string& property, const long long& default_value) {
    return SDL_GetNumberProperty(id, ("SDL.window." + property).c_str(), default_value);
}

int SDL::Video::Window::Properties::get(const std::string& property, const int& default_value) {
    return SDL_GetNumberProperty(id, ("SDL.window." + property).c_str(), default_value);
}

void* SDL::Video::Window::Properties::get(const std::string& property, void* default_value) {
    return SDL_GetPointerProperty(id, ("SDL.window." + property).c_str(), default_value);
}

std::string SDL::Video::Window::Properties::get(const std::string& property, const std::string& default_value) {
    return SDL_GetStringProperty(id, ("SDL.window." + property).c_str(), default_value.c_str());
}

const char* SDL::Video::Window::Properties::get(const std::string& property, const char* default_value) {
    return SDL_GetStringProperty(id, ("SDL.window." + property).c_str(), default_value);
}
#include "sdl.hpp"
#include <SDL3/SDL_properties.h>

SDL::Video::Window::Config::Config () {
    id = SDL_CreateProperties();
    if (!id) throw Error::CREATE;
}

void SDL::Video::Window::Config::destroy() {
    if (id) SDL_DestroyProperties(id);
    else {
        SDL_SetError("not valid");
        throw Error::DESTROY;
    }
    id = 0;
}

SDL::Video::Window::Config::~Config () {
    if (id) SDL_DestroyProperties(id);
}

bool SDL::Video::Window::Config::has(const std::string& property) {
    return SDL_HasProperty(id, ("SDL.window.create." + property).c_str());
}

void SDL::Video::Window::Config::clear (const std::string& property) {
    if (!SDL_ClearProperty(id, property.c_str())) throw Error::CLEAR;
}

SDL_PropertyType SDL::Video::Window::Config::type(const std::string& property) {
    return SDL_GetPropertyType(id, ("SDL.window.create." + property).c_str());
}


bool SDL::Video::Window::Config::get(const std::string& property, const bool& default_value) {
    return SDL_GetBooleanProperty(id, ("SDL.window.create." + property).c_str(), default_value);
}

float SDL::Video::Window::Config::get(const std::string& property, const float& default_value) {
    return SDL_GetFloatProperty(id, ("SDL.window.create." + property).c_str(), default_value);
}

long long SDL::Video::Window::Config::get(const std::string& property, const long long& default_value) {
    return SDL_GetNumberProperty(id, ("SDL.window.create." + property).c_str(), default_value);
}

int SDL::Video::Window::Config::get(const std::string& property, const int& default_value) {
    return SDL_GetNumberProperty(id, ("SDL.window.create." + property).c_str(), default_value);
}

void* SDL::Video::Window::Config::get(const std::string& property, void* default_value) {
    return SDL_GetPointerProperty(id, ("SDL.window.create." + property).c_str(), default_value);
}

std::string SDL::Video::Window::Config::get(const std::string& property, const std::string& default_value) {
    return SDL_GetStringProperty(id, ("SDL.window.create." + property).c_str(), default_value.c_str());
}

const char* SDL::Video::Window::Config::get(const std::string& property, const char* default_value) {
    return SDL_GetStringProperty(id, ("SDL.window.create." + property).c_str(), default_value);
}


void SDL::Video::Window::Config::set(const std::string& property, const bool& value) {
    if (!SDL_SetBooleanProperty(id, ("SDL.window.create." + property).c_str(), value)) throw Error::SET;
}

void SDL::Video::Window::Config::set(const std::string& property, const float& value) {
    if (!SDL_SetFloatProperty(id, ("SDL.window.create." + property).c_str(), value)) throw Error::SET;
}

void SDL::Video::Window::Config::set(const std::string& property, const long long& value) {
    if (!SDL_SetNumberProperty(id, ("SDL.window.create." + property).c_str(), value)) throw Error::SET;
}

void SDL::Video::Window::Config::set(const std::string& property, const int& value) {
    if (!SDL_SetNumberProperty(id, ("SDL.window.create." + property).c_str(), value)) throw Error::SET;
}

void SDL::Video::Window::Config::set(const std::string& property, void* value) {
    if (!SDL_SetPointerProperty(id, ("SDL.window.create." + property).c_str(), value)) throw Error::SET;
}

void SDL::Video::Window::Config::set(const std::string& property, const std::string& value) {
    if (!SDL_SetStringProperty(id, ("SDL.window.create." + property).c_str(), value.c_str())) throw Error::SET;
}

void SDL::Video::Window::Config::set(const std::string& property, const char* value) {
    if (!SDL_SetStringProperty(id, ("SDL.window.create." + property).c_str(), value)) throw Error::SET;
}
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>
#include "math.hpp"
#include <string>
#include <stdexcept>
#include <memory>

#define throw_error throw std::runtime_error(__FUNCSIG__)

#ifdef DEBUG
    #define debug_log(...) SDL_Log(__VA_ARGS__)
#else
    #define debug_log(...)
#endif

class SDL {
    public:
    SDL(): _quit(false) {}

    SDL (SDL&& other) {
        _quit = other._quit;
        other._quit = true;
    }

    SDL& operator=(SDL&& other) {
        if (this != &other) {
            _quit = other._quit;
            other._quit = true;
        }
        return *this;
    }

    void quit() {
        if (_quit) throw_error;
        SDL_Quit();
        _quit = true;
    }

    ~SDL() {
        SDL_Quit();
    };

    class TTF {
        private:
        bool initialized;
        TTF () {
            initialized = TTF_Init();
            if (!initialized) throw_error;
        }
        public:
        friend SDL;
        TTF (TTF&& other) {
            initialized = other.initialized;
            other.initialized = false;
        }
        TTF& operator=(TTF&& other) {
            if (this != &other) {
                initialized = other.initialized;
                other.initialized = false;
            }
            return *this;
        }
        void quit() {
            if (initialized) TTF_Quit();
            else {
                SDL_SetError("Not initialized");
                throw_error;
            }
            initialized = false;
        }
        ~TTF () {
            if (initialized) TTF_Quit();
        }

        class Font {
            public:
            friend TTF;
            friend class Text;
            class Config {
                private:
                SDL_PropertiesID sdl;
                public:
                friend Font;
                Config () {
                    sdl = SDL_CreateProperties();
                    if (!sdl) throw_error;
                }

                Config (Config&& other) {
                    sdl = other.sdl;
                    other.sdl = 0;
                }

                Config& operator=(Config&& other) {
                    if (this != &other) {
                        sdl = other.sdl;
                        other.sdl = 0;
                    }
                    return *this;
                }

                void destroy() {
                    if (sdl) SDL_DestroyProperties(sdl);
                    else {
                        SDL_SetError("Not valid");
                        throw_error;
                    }
                    sdl = 0;
                }
                ~Config () {
                    if (sdl) SDL_DestroyProperties(sdl);
                }
                bool has(const std::string& property) {
                    return SDL_HasProperty(sdl, ("SDL_ttf.font.create." + property).c_str());
                }
                void clear (const std::string& property) {
                    if (!SDL_ClearProperty(sdl, property.c_str())) throw_error;
                }
                SDL_PropertyType type(const std::string& property) {
                    return SDL_GetPropertyType(sdl, ("SDL_ttf.font.create." + property).c_str());
                }
                bool get(const std::string& property, const bool default_value) {
                    return SDL_GetBooleanProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), default_value);
                }
                float get(const std::string& property, const float default_value) {
                    return SDL_GetFloatProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), default_value);
                }
                long long get(const std::string& property, const long long default_value) {
                    return SDL_GetNumberProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), default_value);
                }
                int get(const std::string& property, const int default_value) {
                    return SDL_GetNumberProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), default_value);
                }
                void* get(const std::string& property, void* default_value) {
                    return SDL_GetPointerProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), default_value);
                }
                std::string get(const std::string& property, const std::string& default_value) {
                    return SDL_GetStringProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), default_value.c_str());
                }
                const char* get(const std::string& property, const char* default_value) {
                    return SDL_GetStringProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), default_value);
                }
                void set(const std::string& property, const bool value) {
                    if (!SDL_SetBooleanProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), value)) throw_error;
                }
                void set(const std::string& property, const float value) {
                    if (!SDL_SetFloatProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, const long long value) {
                    if (!SDL_SetNumberProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, const int value) {
                    if (!SDL_SetNumberProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, void* value) {
                    if (!SDL_SetPointerProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, const std::string& value) {
                    if (!SDL_SetStringProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), value.c_str())) throw_error;
                }
                
                void set(const std::string& property, const char* value) {
                    if (!SDL_SetStringProperty(sdl, ("SDL_ttf.font.create." + property).c_str(), value)) throw_error;
                }
            };
            void destroy() {
                if (sdl){
                    TTF_CloseFont(sdl);
                    sdl = nullptr;
                }
                else {
                    SDL_SetError("Not valid");
                    throw_error;
                }
            }
            ~Font() {
                if (sdl) TTF_CloseFont(sdl);
            }
            void size(const float point_size) {
                if (!TTF_SetFontSize(sdl, point_size)) throw_error;
            }
            void sizeAndScale(const float point_size, const float scale) {
                int dpi = 96 * scale;
                if(!TTF_SetFontSizeDPI(sdl, point_size, dpi, dpi)) throw_error;
            }
            Font (Font&& other) {
                sdl = other.sdl;
                other.sdl = nullptr;
            }
            Font& operator=(Font&& other) {
                if (this != &other) {
                    sdl = other.sdl;
                    other.sdl = nullptr;
                }
                return *this;
            }
            private:
            TTF_Font* sdl;
            Font (const char* file, float point_size) {
                sdl = TTF_OpenFont(file, point_size);
                if (!sdl) throw_error;
            }
            Font (const Config& config) {
                sdl = TTF_OpenFontWithProperties(config.sdl);
                if (!sdl) throw_error;
            }
            Font (Config&& config) {
                sdl = TTF_OpenFontWithProperties(config.sdl);
                if (!sdl) throw_error;
            }
        };
        Font loadFont(const char* file, float point_size) {
            return Font(file, point_size);
        }
        Font loadFont(const Font::Config& config) {
            return Font(config);
        }
        Font loadFont(Font::Config&& config) {
            return Font(config);
        }

        std::unique_ptr<Font> loadFontU(const char* file, float point_size) {
            return std::unique_ptr<Font>(new Font(file, point_size));
        }
        std::unique_ptr<Font> loadFontU(const Font::Config& config) {
            return std::unique_ptr<Font>(new Font(config));
        }
        std::unique_ptr<Font> loadFontU(Font::Config&& config) {
            return std::unique_ptr<Font>(new Font(config));
        }
        class TextEngine {
            private:
            TTF_TextEngine* sdl;
            public:
            friend class TTF;
            TextEngine (SDL_Renderer* renderer) {
                sdl = TTF_CreateRendererTextEngine(renderer);
                if (!sdl) throw_error;
            }
            TextEngine (TextEngine&& other) {
                sdl = other.sdl;
                other.sdl = nullptr;
            }
            TextEngine& operator=(TextEngine&& other) {
                if (this != &other) {
                    sdl = other.sdl;
                    other.sdl = nullptr;
                }
                return *this;
            }
            void destroy() {
                if (sdl){
                    TTF_DestroyRendererTextEngine(sdl);
                    sdl = nullptr;
                }
                else {
                    SDL_SetError("Not valid");
                    throw_error;
                }
            }
            ~TextEngine() {
                if (sdl) TTF_DestroyRendererTextEngine(sdl);
            }

            class Text {
                public:
                friend TextEngine;
                void destroy() {
                    if (sdl){
                        TTF_DestroyText(sdl);
                        sdl = nullptr;
                    }
                    else {
                        SDL_SetError("Not valid");
                        throw_error;
                    }
                }
                ~Text() {
                    if (sdl) TTF_DestroyText(sdl);
                }
                void setColor(const math::Color& color) {
                    if (!TTF_SetTextColor(sdl, color.red, color.green, color.blue, color.alpha)) throw_error;
                }
                bool draw(const math::d2::position<float> position) {
                    return TTF_DrawRendererText(sdl, position.x, position.y);
                }
                void setText(const std::string& text) {
                    if (!TTF_SetTextString(sdl, text.data(), text.length())) throw_error;
                }
                bool setWrapWidth(const int width) {
                    return TTF_SetTextWrapWidth(sdl, width);
                }
                Text (Text&& other) {
                    sdl = other.sdl;
                    other.sdl = nullptr;
                }
                Text& operator=(Text&& other) {
                    if (this != &other) {
                        sdl = other.sdl;
                        other.sdl = nullptr;
                    }
                    return *this;
                }
                private:
                TTF_Text* sdl;
                Text (TTF_TextEngine* text_engine, const Font& font, const std::string& text) {
                    sdl = TTF_CreateText(text_engine, font.sdl, text.c_str(), text.length());
                    if (!sdl) throw_error;
                }
            };
            Text createText(const Font& font, const std::string& text) {
                return Text(sdl, font, text);
            }
            std::unique_ptr<Text> createTextU(const Font& font, const std::string& text) {
                return std::unique_ptr<Text>(new Text(sdl, font, text));
            }
        };
    };
    TTF initTTF() { return TTF(); }
    std::unique_ptr<TTF> initTTFU() { return std::unique_ptr<TTF>(new TTF()); }

    class Video {
        public:
        friend SDL;
        Video (Video&& other) {
            initialized = other.initialized;
            other.initialized = false;
        }
        Video& operator=(Video&& other) {
            if (this != &other) {
                initialized = other.initialized;
                other.initialized = false;
            }
            return *this;
        }
        void quit() {
            if (initialized) SDL_QuitSubSystem(SDL_INIT_VIDEO);
            else {
                SDL_SetError("Not initialized");
                throw_error;
            }
            initialized = false;
        }
        ~Video() {
            if (initialized) {
                SDL_QuitSubSystem(SDL_INIT_VIDEO);
            }
        }

        SDL_DisplayID getPrimaryDisplay() {
            auto id = SDL_GetPrimaryDisplay();
            if (!id) throw_error;
            return id;
        }
        const SDL_DisplayMode &getDisplayMode(const SDL_DisplayID &id){
            auto mode = SDL_GetDesktopDisplayMode(id);
            if (!mode) throw_error;
            return *mode;
        }

        class Renderer;

        class Window {
            public:
            friend SDL;
            friend Video;
            friend class Renderer;
            friend class Events;
            class Config {
                private:
                SDL_PropertiesID sdl;
                public:
                friend Window;
                Config () {
                    sdl = SDL_CreateProperties();
                    if (!sdl) throw_error;
                }
                Config (Config&& other) {
                    sdl = other.sdl;
                    other.sdl = 0;
                }

                Config& operator=(Config&& other) {
                    if (this != &other) {
                        sdl = other.sdl;
                        other.sdl = 0;
                    }
                    return *this;
                }
                void destroy() {
                    if (sdl) SDL_DestroyProperties(sdl);
                    else {
                        SDL_SetError("Not valid");
                        throw_error;
                    }
                    sdl = 0;
                }
                ~Config () {
                    if (sdl) SDL_DestroyProperties(sdl);
                }
                bool has(const std::string& property) {
                    return SDL_HasProperty(sdl, ("SDL.window.create." + property).c_str());
                }
                void clear (const std::string& property) {
                    if (!SDL_ClearProperty(sdl, property.c_str())) throw_error;
                }
                SDL_PropertyType type(const std::string& property) {
                    return SDL_GetPropertyType(sdl, ("SDL.window.create." + property).c_str());
                }
                bool get(const std::string& property, const bool default_value) {
                    return SDL_GetBooleanProperty(sdl, ("SDL.window.create." + property).c_str(), default_value);
                }
                float get(const std::string& property, const float default_value) {
                    return SDL_GetFloatProperty(sdl, ("SDL.window.create." + property).c_str(), default_value);
                }
                long long get(const std::string& property, const long long default_value) {
                    return SDL_GetNumberProperty(sdl, ("SDL.window.create." + property).c_str(), default_value);
                }
                int get(const std::string& property, const int default_value) {
                    return SDL_GetNumberProperty(sdl, ("SDL.window.create." + property).c_str(), default_value);
                }
                void* get(const std::string& property, void* default_value) {
                    return SDL_GetPointerProperty(sdl, ("SDL.window.create." + property).c_str(), default_value);
                }
                std::string get(const std::string& property, const std::string& default_value) {
                    return SDL_GetStringProperty(sdl, ("SDL.window.create." + property).c_str(), default_value.c_str());
                }
                const char* get(const std::string& property, const char* default_value) {
                    return SDL_GetStringProperty(sdl, ("SDL.window.create." + property).c_str(), default_value);
                }
                void set(const std::string& property, const bool value) {
                    if (!SDL_SetBooleanProperty(sdl, ("SDL.window.create." + property).c_str(), value)) throw_error;
                }
                void set(const std::string& property, const float value) {
                    if (!SDL_SetFloatProperty(sdl, ("SDL.window.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, const long long value) {
                    if (!SDL_SetNumberProperty(sdl, ("SDL.window.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, const int value) {
                    if (!SDL_SetNumberProperty(sdl, ("SDL.window.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, void* value) {
                    if (!SDL_SetPointerProperty(sdl, ("SDL.window.create." + property).c_str(), value)) throw_error;
                }
                
                void set(const std::string& property, const std::string& value) {
                    if (!SDL_SetStringProperty(sdl, ("SDL.window.create." + property).c_str(), value.c_str())) throw_error;
                }
                
                void set(const std::string& property, const char* value) {
                    if (!SDL_SetStringProperty(sdl, ("SDL.window.create." + property).c_str(), value)) throw_error;
                }
            };
            class Properties {
                private:
                SDL_PropertiesID sdl;
                Properties(SDL_Window* window){
                    sdl = SDL_GetWindowProperties(window);
                    if (!sdl) throw_error;
                }
                public:
                friend class Window;
                Properties (Properties&& other) {
                    sdl = other.sdl;
                    other.sdl = 0;
                }

                Properties& operator=(Properties&& other) {
                    if (this != &other) {
                        sdl = other.sdl;
                        other.sdl = 0;
                    }
                    return *this;
                }
                void destroy() {
                    if (sdl) SDL_DestroyProperties(sdl);
                    else {
                        SDL_SetError("not valid");
                        throw_error;
                    }
                    sdl = 0;
                }
                ~Properties () {
                    if (sdl) SDL_DestroyProperties(sdl);
                }
                bool has (const std::string& property) {
                    return SDL_HasProperty(sdl, ("SDL.window." + property).c_str());
                }
                SDL_PropertyType type (const std::string& property) {
                    return SDL_GetPropertyType(sdl, ("SDL.window." + property).c_str());
                }
                
                bool get(const std::string& property, const bool default_value) {
                    return SDL_GetBooleanProperty(sdl, ("SDL.window." + property).c_str(), default_value);
                }
                
                float get(const std::string& property, const float default_value) {
                    return SDL_GetFloatProperty(sdl, ("SDL.window." + property).c_str(), default_value);
                }
                
                long long get(const std::string& property, const long long default_value) {
                    return SDL_GetNumberProperty(sdl, ("SDL.window." + property).c_str(), default_value);
                }
                
                int get(const std::string& property, const int default_value) {
                    return SDL_GetNumberProperty(sdl, ("SDL.window." + property).c_str(), default_value);
                }
                
                void* get(const std::string& property, void* default_value) {
                    return SDL_GetPointerProperty(sdl, ("SDL.window." + property).c_str(), default_value);
                }
                
                std::string get(const std::string& property, const std::string& default_value) {
                    return SDL_GetStringProperty(sdl, ("SDL.window." + property).c_str(), default_value.c_str());
                }
                
                const char* get(const std::string& property, const char* default_value) {
                    return SDL_GetStringProperty(sdl, ("SDL.window." + property).c_str(), default_value);
                }
            };
            bool die;
            void destroy () {
                if (die){
                    if (sdl) {
                        SDL_DestroyWindow(sdl);
                        sdl = nullptr;
                    }
                    else {
                        SDL_SetError("Not valid");
                        throw_error;
                    }
                }
            }
            Window (Window&& other) {
                die = other.sdl;
                sdl = other.sdl;
                other.sdl = nullptr;
                other.die = false;
            }
            Window& operator=(Window&& other) {
                if (this != &other) {
                    die = other.sdl;
                    sdl = other.sdl;
                    other.sdl = nullptr;
                    other.die = false;
                }
                return *this;
            }
            ~Window () {
                if (die) if (sdl) SDL_DestroyWindow(sdl);
            }
            SDL_DisplayID getID () {
                auto id = SDL_GetWindowID(sdl);
                if (!id) throw_error;
                return id;
            }
            Properties getProperties () {
                return Properties(sdl);
            }
            void raise() {
                if (!SDL_RaiseWindow(sdl)) throw_error;
            }
            void show () {
                if (!SDL_ShowWindow(sdl)) throw_error;
            }
            void hide () {
                if (!SDL_HideWindow(sdl)) throw_error;
            }
            float scale () {
                float scale = SDL_GetWindowDisplayScale(sdl);
                if(scale == 0.0f) throw_error;
                return scale;
            }
            void setMinimumSize(const math::d2::size<int>& size) {
                if (!SDL_SetWindowMinimumSize(sdl, size.width, size.height)) throw_error;
            }
            Renderer createRenderer(const std::string& api) {
                return Renderer(sdl, api);
            }
            std::unique_ptr<Renderer> createRendererU(const std::string& api) {
                return std::unique_ptr<Renderer>(new Renderer(sdl, api));
            }
            private:
            SDL_Window* sdl;
            Window(const std::string &title, const math::d2::size<int>& size, const SDL_WindowFlags &flags): die(true) {
                sdl = SDL_CreateWindow(title.c_str(), size.width, size.height, flags);
                if (!sdl) throw_error;
            }
            Window(const Config &config): die(true) {
                sdl = SDL_CreateWindowWithProperties(config.sdl);
                if (!sdl) throw_error;
            }
            Window(Config &&config): die(true) {
                sdl = SDL_CreateWindowWithProperties(config.sdl);
                if (!sdl) throw_error;
            }
        };
        Window createWindow(
            const std::string &title,
            const math::d2::size<int>& size,
            const SDL_WindowFlags &flags
        ) {
            return Window(title, size, flags);
        }
        Window createWindow(const Window::Config &config) {
            return Window(config);
        }
        Window createWindow(Window::Config &&config) {
            return Window(config);
        }

        std::unique_ptr<Window> createWindowU(
            const std::string &title,
            const math::d2::size<int>& size,
            const SDL_WindowFlags &flags
        ) {
            return std::unique_ptr<Window>(new Window(title, size, flags));
        }
        std::unique_ptr<Window> createWindowU(const Window::Config &config) {
            return std::unique_ptr<Window>(new Window(config));
        }
        std::unique_ptr<Window> createWindowU(Window::Config &&config) {
            return std::unique_ptr<Window>(new Window(config));
        }

        class Renderer {
            public:
            friend Window;
            friend TTF;
            Renderer (Renderer&& other) {
                sdl = other.sdl;
                other.sdl = nullptr;
            }
            Renderer& operator=(Renderer&& other) {
                if (this != &other) {
                    sdl = other.sdl;
                    other.sdl = nullptr;
                }
                return *this;
            }
            void destroy() {
                if (sdl) {
                    SDL_DestroyRenderer(sdl);
                    sdl = nullptr;
                }
                else {
                    SDL_SetError("not valid");
                    throw_error;
                }
            }
            ~Renderer() {
                if (sdl) SDL_DestroyRenderer(sdl);
            }

            class Texture {
                private:
                SDL_Texture* sdl;
                Texture (SDL_Renderer* renderer, const char* file) {
                    sdl = IMG_LoadTexture(renderer, file);
                    if (!sdl) throw_error;
                }
                public:
                friend Renderer;
                Texture (Texture&& other) {
                    sdl = other.sdl;
                    other.sdl = nullptr;
                }
                Texture& operator=(Texture&& other) {
                    if (this != &other) {
                        sdl = other.sdl;
                        other.sdl = nullptr;
                    }
                    return *this;
                }
                void destroy() {
                    if (sdl){
                        SDL_DestroyTexture(sdl);
                        sdl = nullptr;
                    }
                    else {
                        SDL_SetError("Not valid");
                        throw_error;
                    }
                }
                ~Texture() {
                    if (sdl) SDL_DestroyTexture(sdl);
                }
                void setScaleMode(SDL_ScaleMode mode) {
                    if (!SDL_SetTextureScaleMode(sdl, mode)) throw_error;
                }
            };
            Texture loadTexture(const char* file) {
                return Texture(sdl, file);
            }
            std::unique_ptr<Texture> loadTextureU(const char* file) {
                return std::unique_ptr<Texture>(new Texture(sdl, file));
            }
            
            TTF::TextEngine createTextEngine() {
                return TTF::TextEngine(sdl);
            }
            std::unique_ptr<TTF::TextEngine> createTextEngineU() {
                return std::unique_ptr<TTF::TextEngine>(new TTF::TextEngine(sdl));
            }

            bool setBlendMode(SDL_BlendMode mode) {
                return SDL_SetRenderDrawBlendMode(sdl, mode);
            }

            bool clear (const math::Color& color) {
                return SDL_SetRenderDrawColor(sdl, color.red, color.green, color.blue, color.alpha) 
                        &&
                        SDL_RenderClear(sdl);
            }

            bool present() {
                return SDL_RenderPresent(sdl);
            }

            bool renderTexture(
                const Texture& texture,
                const math::Rectangle<float>* const destination,
                const math::Rectangle<float>* const source
            ) {
                return SDL_RenderTexture(sdl, texture.sdl, (SDL_FRect*) source, (SDL_FRect*) destination);
            }
            
            bool renderTextureTiled(
                const Texture& texture,
                const math::Rectangle<float>* const destination,
                const float scale,
                const math::Rectangle<float>* const source
            ) {
                return SDL_RenderTextureTiled(sdl, texture.sdl, (SDL_FRect*) source, scale, (SDL_FRect*) destination);
            }
            
            bool fillRect(const math::Color& color, const math::Rectangle<float>& rectangle) {
                return SDL_SetRenderDrawColor(sdl, color.red, color.green, color.blue, color.alpha)
                        &&
                       SDL_RenderFillRect(sdl, (SDL_FRect*) &rectangle);
            }

            private:
            SDL_Renderer* sdl;
            Renderer (SDL_Window* window, const std::string& api) {
                sdl = SDL_CreateRenderer(window, api.c_str());
                if (!sdl) throw_error;
            }
        };

        private:
        bool initialized;
        Video() {
            initialized = SDL_Init(SDL_INIT_VIDEO);
            if (!initialized) throw_error;
        }
    };
    Video initVideo() { return Video(); }
    std::unique_ptr<Video> initVideoU() { return std::unique_ptr<Video>(new Video()); }

    class Events
    {
    private:
        bool initialized;
        Events() {
            initialized = SDL_Init(SDL_INIT_EVENTS);
            if (!initialized) throw_error;
        }

    public:
        friend SDL;
        Events (Events&& other) {
            initialized = other.initialized;
            other.initialized = false;
        }
        Events& operator=(Events&& other) {
            if (this != &other) {
                initialized = other.initialized;
                other.initialized = false;
            }
            return *this;
        }
        void quit() {
            if (initialized) SDL_QuitSubSystem(SDL_INIT_EVENTS);
            else {
                SDL_SetError("Not initialized");
                throw_error;
            }
            initialized = false;
        }
        ~Events() {
            if (initialized) {
                SDL_QuitSubSystem(SDL_INIT_EVENTS);
            }
        }
        void startTextInput(const Video::Window& window) {
            if (!SDL_StartTextInput(window.sdl)) throw_error;
        }
        void stopTextInput(const Video::Window& window) {
            if (!SDL_StopTextInput(window.sdl)) throw_error;
        }
        bool isTextInputActive(const Video::Window& window) {
            return SDL_TextInputActive(window.sdl);
        }
        bool pollEvent(SDL_Event &event) {
            return SDL_PollEvent(&event);
        }
        void waitEvent(SDL_Event &event) {
            if (!SDL_WaitEvent(&event)) { throw_error; }
        }
        void pushEvent(SDL_Event &event) {
            if (!SDL_PushEvent(&event)) { throw_error; };
        }
    };
    Events initEvents() { return Events(); }
    std::unique_ptr<Events> initEventsU() { return std::unique_ptr<Events>(new Events()); }

    private:
    bool _quit;
};

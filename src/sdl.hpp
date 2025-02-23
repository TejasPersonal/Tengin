#pragma once
#include "math.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_messagebox.h>
#include <xstring>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_ttf.h>

class SDL
{
private:
    bool _quit_;

public:
    enum Error
    {
        QUIT
    };

    struct SimpleMessageBox
    {
        SDL_MessageBoxFlags flag;
        const char *title;
        const char *message;
        enum Error
        {
            SHOW
        };
        void show();
    };

    SDL();
    void quit();
    ~SDL();

    static void sleep(unsigned int milli_seconds);

    class Events
    {
    private:
        bool initialized;
        Events();

    public:
        friend SDL;
        enum Error
        {
            INITIALIZATION,
            QUIT,
            POLL_EVENT,
            PUSH_EVENT
        };
        void quit();
        ~Events();
        bool pollEvent(SDL_Event &event);
        void waitEvent(SDL_Event &event);
        void pushEvent(SDL_Event &event);
    };
    Events initEvents();

    class Video
    {
    private:
        bool initialized;
        Video();

    public:
        friend SDL;
        enum Error
        {
            INITIALIZATION,
            QUIT,
            GET_DISPLAY,
            GET_DISPLAY_MODE,
        };
        void quit();
        ~Video();
        SDL_DisplayID primaryDisplay();
        const SDL_DisplayMode &displayMode(const SDL_DisplayID &id);
        class Window
        {
        public:
            friend SDL;
            class Config
            {
            private:
                SDL_PropertiesID id;
            public:
                friend class Window;
                enum Error
                {
                    CREATE,
                    GET,
                    SET,
                    DESTROY,
                    CLEAR
                };
                Config();
                void destroy();
                ~Config();
                bool has(const std::string &property);
                SDL_PropertyType type(const std::string &property);
                void clear(const std::string &property);
                void set(const std::string& property, const bool& value);
                void set(const std::string& property, const float& value);
                void set(const std::string& property, const long long& value);
                void set(const std::string& property, const int& value);
                void set(const std::string& property, void* value);
                void set(const std::string& property, const char* value);
                void set(const std::string& property, const std::string& value);

                bool        get(const std::string& property, const bool& value);
                float       get(const std::string& property, const float& value);
                long long   get(const std::string& property, const long long& value);
                int         get(const std::string& property, const int& value);
                void*       get(const std::string& property, void* value);
                const char* get(const std::string& property, const char* value);
                std::string get(const std::string& property, const std::string& value);
            };
            class Properties
            {
            private:
                SDL_PropertiesID id;
                Properties(SDL_Window *window);

            public:
                friend Window;
                enum Error
                {
                    CREATE,
                    GET,
                    SET,
                    DESTROY,
                    CLEAR
                };
                void destroy();
                ~Properties();
                bool has(const std::string &property);
                SDL_PropertyType type(const std::string &property);
                
                bool        get(const std::string& property, const bool& value);
                float       get(const std::string& property, const float& value);
                long long   get(const std::string& property, const long long& value);
                int         get(const std::string& property, const int& value);
                void*       get(const std::string& property, void* value);
                const char* get(const std::string& property, const char* value);
                std::string get(const std::string& property, const std::string& value);
            };
            friend Video;
            friend class Renderer;
            SDL_Window *sdl;
            bool die;
            enum Error
            {
                CREATE,
                DESTROY,
                ID,
                SHOW,
                HIDE,
                GET_SCALE,
                SET_MINIMUM_SIZE
            };
            void destroy();
            ~Window();
            SDL_DisplayID id();
            Properties properties();
            void show();
            void hide();
            float scale();
            void setMinimumSize(const math::d2::size<int>& size);
            private:
            Window(const std::string &title, const math::d2::size<int> size,
                   const SDL_WindowFlags &flags);
            Window(const Config &config);
            Window(Config &&config);
        };
        Window createWindow(const std::string &title,
                            const math::d2::size<int> size,
                            const SDL_WindowFlags &flags);
        Window createWindow(const Window::Config &config);
        Window createWindow(Window::Config &&config);
        class Renderer {
            public:
            friend Video;
            friend class Window;
            SDL_Renderer* sdl;
            enum Error {
                CREATE,
                DESTROY
            };
            void destroy();
            ~Renderer();
            class Texture {
                private:
                SDL_Texture* texture;
                Texture(const Renderer& renderer, const char* file);
                public:
                friend Renderer;
                enum Error {
                    LOAD,
                    CREATE,
                    DESTROY
                };
                void destroy();
                ~Texture();
            };

            bool clear (const math::Color& color);
            bool present();
            Texture loadTexture(const char* file);
            bool renderTexture(
                const Texture& texture,
                const math::Rectangle<int>* destination = nullptr,
                const math::Rectangle<int>* source = nullptr
            );
            private:
            Renderer(const Window& window, const std::string& api);
        };
        Renderer createRenderer(const Window& window, const std::string& api);
    };
    Video initVideo();

    class TTF {
        private:
        bool initialized;
        TTF ();
        public:
        friend SDL;
        enum Error {
            INITIALIZATION,
            QUIT,
        };
        void quit();
        ~TTF ();

        class Font {
            private:
            TTF_Font* font;
            Font(const char* file, float point_size);
            public:
            friend TTF;
            enum Error {
                LOAD,
                DESTROY,
                SET_SIZE
            };
            void destroy();
            ~Font();
            void size(float point_size);
        };

        Font loadFont(const char* file, float point_size);

        class TextEngine {
            private:
            TTF_TextEngine* text_engine;
            TextEngine(const Video::Renderer& renderer);
            public:
            friend TTF;
            friend class Text;
            enum Error {
                CREATE,
                DESTROY
            };
            void destroy();
            ~TextEngine();
            class Text {
                public:
                friend TextEngine;
                enum Error {
                    CREATE,
                    DESTROY,
                    SET_COLOR,
                    DRAW,
                    SET_TEXT
                };
                void destroy();
                ~Text();
                void color(const math::Color& color);
                void draw(const math::d2::position<float> position);
                void text(const std::string& text);
                private:
                TTF_Text* ttf_text;
                Text (TTF_TextEngine* text_engine, const Font& font, const std::string& text_);
            };
            Text createText(const Font& font, const std::string& text);
        };

        TextEngine createTextEngine(const Video::Renderer& renderer);
    };

    TTF initTTF();
};
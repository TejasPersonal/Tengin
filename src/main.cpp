#include "sdl.hpp"
#include <iostream>
#include <atomic>
#include <thread>
#include <format>
using std::cout, std::endl;

#define sdl_error_handler(type) \
    catch (type error) { \
        std::string title = std::format("{} ({})", #type, (int) error); \
        SDL::SimpleMessageBox { \
            .flag = SDL_MESSAGEBOX_ERROR, \
            .title = title.data(), \
            .message = std::format("{}\n{}", SDL_GetError(), std::string(title.length(), ' ')).data() \
        }.show(); \
    } \

#define sdl_render_error_handler(type) \
    catch (type error) { \
        std::string title = std::format("{} ({})", #type, (int) error); \
        SDL::SimpleMessageBox { \
            .flag = SDL_MESSAGEBOX_ERROR, \
            .title = title.data(), \
            .message = std::format("{}\n{}", last_render_error, std::string(title.length(), ' ')).data() \
        }.show(); \
    } \

int main(int argc, char* argv[]) {
    SDL sdl;
    std::thread render_thread;
    std::exception_ptr render_exception;
    std::atomic<bool> running = true;
    const char* last_render_error;
    try {
        // start
        auto video = sdl.initVideo();
        auto events = sdl.initEvents();
        auto ttf = sdl.initTTF();
        auto display = video.displayMode(video.primaryDisplay());

        auto window = video.createWindow(
            "Window", 
            math::d2::size{display.w >> 1, display.h >> 1}, 
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN
        );
        std::atomic<float> scale = window.scale();
        std::atomic<bool> scale_change = false;

        render_thread = std::thread([&] {
            try {
                // start
                auto hwnd = window.properties().get("win32.hwnd", (void*) nullptr);
                if (!hwnd) {
                    SDL_SetError("Not valid win32 window handle");
                    throw SDL::Video::Window::Properties::Error::GET;
                }
                SDL::Video::Window::Config window_config;
                window_config.set("win32.hwnd", hwnd);
                window_config.set("opengl", true);

                auto window_proxy = video.createWindow(window_config);

                window_proxy.setMinimumSize(math::d2::size{display.w >> 2, display.h >> 2});

                auto renderer = video.createRenderer(window_proxy, "opengl");
                auto cat = renderer.loadTexture("cat.jpg");
                float font_size = 32.0f;
                auto raleway_font = ttf.loadFont("Raleway-Black.ttf", font_size * scale);
    
                auto text_engine = ttf.createTextEngine(renderer);
                auto text = text_engine.createText(raleway_font, "OMG WOW");

                window_proxy.show();
                while (running) {
                    renderer.renderTexture(cat);
                    text.draw(math::d2::position<float>{10, 10});
                    renderer.present();
                    if (scale_change) {
                        raleway_font.size(font_size * scale);
                        scale_change = false;
                    }
                }
                // end
            }
            catch (...) {
                render_exception = std::current_exception();
                last_render_error = SDL_GetError();
                running = false;
                try {
                    SDL_Event quit_event = {};
                    events.pushEvent(quit_event);
                }
                sdl_error_handler(SDL::Events::Error)
                catch (const std::exception& e) {
                    SDL::SimpleMessageBox {
                        .flag = SDL_MESSAGEBOX_ERROR,
                        .title = "ERROR",
                        .message = e.what()
                    }.show();
                }
                catch (...) {
                    SDL::SimpleMessageBox {
                        .flag = SDL_MESSAGEBOX_ERROR,
                        .title = "ERROR",
                        .message = "Unknown error occured"
                    }.show();
                }
            }
        });

        SDL_Event event;
        while (running) {
            events.waitEvent(event);
            switch (event.window.type)
            {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    running = false;
                    break;

                case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED: {
                    scale = window.scale();
                    scale_change = true;
                    break;
                }
                
                default:
                    break;
            }
        }
        // end
    }
    sdl_error_handler(SDL::Error)
    sdl_error_handler(SDL::Events::Error)
    sdl_error_handler(SDL::Video::Error)
    sdl_error_handler(SDL::Video::Window::Error)
    sdl_error_handler(SDL::Video::Window::Config::Error)
    sdl_error_handler(SDL::Video::Window::Properties::Error)
    catch (const std::exception& e) {
        SDL::SimpleMessageBox {
            .flag = SDL_MESSAGEBOX_ERROR,
            .title = "ERROR",
            .message = e.what()
        }.show();
    }
    catch (...) {
        SDL::SimpleMessageBox {
            .flag = SDL_MESSAGEBOX_ERROR,
            .title = "ERROR",
            .message = "Unknown error occured"
        }.show();
    }
    
    running = false;
    if (render_thread.joinable()) render_thread.join();

    try {
        if (render_exception) std::rethrow_exception(render_exception);
    }
    sdl_render_error_handler(SDL::Error)
    sdl_render_error_handler(SDL::Events::Error)
    sdl_render_error_handler(SDL::Video::Error)
    sdl_render_error_handler(SDL::Video::Window::Error)
    sdl_render_error_handler(SDL::Video::Renderer::Error)
    sdl_render_error_handler(SDL::Video::Window::Config::Error)
    sdl_render_error_handler(SDL::Video::Window::Properties::Error)
    catch (const std::exception& e) {
        SDL::SimpleMessageBox {
            .flag = SDL_MESSAGEBOX_ERROR,
            .title = "ERROR",
            .message = e.what()
        }.show();
    }
    catch (...) {
        SDL::SimpleMessageBox {
            .flag = SDL_MESSAGEBOX_ERROR,
            .title = "ERROR",
            .message = "Unknown error occured"
        }.show();
    }

    return 0;
}
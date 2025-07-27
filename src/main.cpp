#include "sdl.hpp"
#include <iostream>
#include <format>
#include <functional>
#include <vector>

using RectF = math::Rectangle<float>;
using math::Color;
using math::d2::size;
using math::d2::position;

using std::cout, std::endl, std::cerr;

#define CASE(x, task) case x: {task break;}

struct Font {
    std::vector<std::unique_ptr<SDL::TTF::Font>> sizes;
    Font(SDL::TTF& ttf, const char* file, const float max_point_size, const float scale, const unsigned char _sizes) {
        int dpi = 96 * scale;
        min_point_size = max_point_size / _sizes;
        unsigned char i = 0;
        while (i < _sizes) {
            auto config = std::make_unique<SDL::TTF::Font::Config>();
            config->set("filename", file);
            config->set("size", min_point_size * ++i);
            config->set("hdpi", dpi); config->set("vdpi", dpi);
            sizes.push_back(ttf.loadFontU(*config));
        }
    }
    void scale(const float value) {
        unsigned char i = 0;
        while (i < sizes.size()) {
            sizes[i]->sizeAndScale(min_point_size * ++i, value);
        }
    }
    SDL::TTF::Font& get(const unsigned char index) {
        return *sizes[index];
    }
    private:
    float min_point_size;
};

inline void code() {
    SDL sdl;
    auto events = sdl.initEvents();
    auto ttf = sdl.initTTF();
    auto video = sdl.initVideo();

    auto display = video.getDisplayMode(video.getPrimaryDisplay());
    struct {
        bool running = true;
        float scale;
        // position<float> cursor;
        float target_frequency;
        float time;
        // std::unordered_map<unsigned int, bool> keys;
        size<int> viewport;
    } gui;
    gui.viewport = size<int> {display.w >> 1, display.h >> 1};

    auto window = video.createWindow("Totpad", gui.viewport, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    window.setMinimumSize(size<int> {gui.viewport.width >> 1, gui.viewport.height >> 1});

    gui.scale = window.scale();
    gui.target_frequency = (1000.0f * display.refresh_rate_denominator) / display.refresh_rate_numerator;
    gui.time = 0;

    auto renderer = window.createRenderer("opengl");
    auto font = Font(ttf, "Raleway-Black.ttf", 24.0f, gui.scale, 1);
    auto text_engine = renderer.createTextEngine();
    std::string str = "Omzi mam zi mam bing bing boo .. ";
    char cursor = '_';
    auto text = text_engine.createText(font.get(0), str + cursor);
    float text_padding = 10.0f;
    text.setWrapWidth(gui.viewport.width - text_padding);

    events.startTextInput(window);
    window.show();
    SDL_Event event;
    while (gui.running) {
        auto itime = SDL_GetTicks();

        events.waitEvent(event);
            switch (event.type)
            {
                CASE (SDL_EVENT_TEXT_INPUT,
                    str += event.text.text;
                    text.setText(str + cursor);
                )
                CASE (SDL_EVENT_KEY_DOWN,
                    // gui.keys[event.key.key] = true;

                    if (event.key.key == SDLK_BACKSPACE) {
                        if (!str.empty()) {
                            str.pop_back();
                            text.setText(str + cursor);
                        }
                    } else if (event.key.key == 13) {
                        str += '\n';
                        text.setText(str + cursor);
                    }
                )
                // CASE (SDL_EVENT_KEY_UP,
                    // gui.keys[event.key.key] = false;
                // )
                // CASE (SDL_EVENT_MOUSE_MOTION,
                //     gui.cursor.x = event.motion.x;
                //     gui.cursor.y = event.motion.y;
                // )
                CASE (SDL_EVENT_WINDOW_RESIZED,
                    gui.viewport.width = event.window.data1;
                    gui.viewport.height = event.window.data2;
                    text.setWrapWidth(gui.viewport.width - text_padding);
                )
                CASE (SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED,
                    gui.scale = window.scale();
                    font.scale(gui.scale);
                )
                CASE (SDL_EVENT_WINDOW_CLOSE_REQUESTED, 
                    gui.running = false;
                )
            }

        // RENDER

            renderer.clear(Color{0, 0, 0, 255});

            text.draw(position{text_padding, text_padding});

            renderer.present();
        
        // END

        auto etime = SDL_GetTicks();
        if (etime < gui.target_frequency) {
            SDL_Delay(gui.target_frequency - etime);
            gui.time = gui.target_frequency;
        }
        else {
            gui.time = etime;
        }
    }
}

int main (int argc, char* argv[]) {
    try {
        code();
    } catch (const std::exception& error) {
        cout << "Error in " << error.what() << endl;
        cout << "   " << SDL_GetError();
    }

    return 0;
}

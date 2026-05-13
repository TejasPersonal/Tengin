// math.hpp
#pragma once

#include <cstdint>

namespace math {

    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;

        constexpr Color() : red(0), green(0), blue(0), alpha(255) {}
        constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
            : red(r), green(g), blue(b), alpha(a) {}
    };

    template<typename T>
    struct Rectangle {
        T x;
        T y;
        T width;
        T height;

        constexpr Rectangle() : x(0), y(0), width(0), height(0) {}
        constexpr Rectangle(T x_, T y_, T w_, T h_)
            : x(x_), y(y_), width(w_), height(h_) {}
    };

    namespace d2 {

        template<typename T>
        struct position {
            T x;
            T y;

            constexpr position() : x(0), y(0) {}
            constexpr position(T x_, T y_) : x(x_), y(y_) {}
        };

        template<typename T>
        struct size {
            T width;
            T height;

            constexpr size() : width(0), height(0) {}
            constexpr size(T w, T h) : width(w), height(h) {}
        };

    } // namespace d2

} // namespace math

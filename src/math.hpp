#pragma once

namespace math {
    namespace d2 {
        template <typename type>
        struct size
        {
            type width, height;
        };

        template <typename type>
        struct position
        {
            type x, y;
        };
    }

    template <typename type>
    struct Rectangle {
        math::d2::position<type> position;
        math::d2::size<type> size;
    };
    
    struct Color { unsigned char red, green, blue, alpha; };

    template <typename type>
    struct ColorT { type red, green, blue, alpha; };
}
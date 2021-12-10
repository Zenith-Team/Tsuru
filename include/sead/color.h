#pragma once

#include "types.h"

namespace sead {

class Color4f {
public:
    inline Color4f(u32 hex = 0x000000FF) {
        this->r = ((hex >> 24) & 0xFF) / 255.0f;
        this->g = ((hex >> 16) & 0xFF) / 255.0f;
        this->b = ((hex >> 8)  & 0xFF) / 255.0f;
        this->a = (hex & 0xFF) / 255.0f;
    }

    inline Color4f(f32 r, f32 g, f32 b, f32 a = 1.0f) :
        r(r), g(g), b(b), a(a) { }

    inline Color4f(u8 r, u8 g, u8 b, u8 a = 255) :
        r(r / 255), g(g / 255), b(b / 255), a(a / 255) { }

    void set(f32 r, f32 g, f32 b, f32 a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

static const Color4f colorRed     (0xFF0000FF);
static const Color4f colorOrange  (0xFF8000FF);
static const Color4f colorYellow  (0xFFFF00FF);
static const Color4f colorGreen   (0x00FF00FF);
static const Color4f colorCyan    (0x00FFFFFF);
static const Color4f colorBlue    (0x0000FFFF);
static const Color4f colorPurple  (0xC000FFFF);
static const Color4f colorMagenta (0xFF00FFFF);
static const Color4f colorBlack   (0x000000FF);
static const Color4f colorWhite   (0xFFFFFFFF);

}

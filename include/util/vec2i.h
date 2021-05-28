#pragma once

#include "types.h"

struct Vec2i {
    s32 x;
    s32 y;

    Vec2i(s32 v = 0) :
        x(v), y(v) { }

    Vec2i(s32 x, s32 y) :
        x(x), y(y) { }
};

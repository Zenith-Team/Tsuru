#pragma once

#include "types.h"

struct Vec2i {  // size: 0x8
    s32 x;  // 0
    s32 y;  // 4

    Vec2i(s32 v = 0) :
        x(v), y(v) { }

    Vec2i(s32 x, s32 y) :
        x(x), y(y) { }
};

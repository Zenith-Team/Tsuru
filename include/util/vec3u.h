#pragma once

#include "types.h"

struct Vec3u
{
    u32 x;
    u32 y;
    u32 z;

    Vec3u(u32 x, u32 y, u32 z) :
        x(x), y(y), z(z) { }
};

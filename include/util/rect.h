#pragma once

#include "vec2.h"

struct Rect {  // size: 0x10
    inline static bool RectsOverlap(Rect& thisRect, Rect& otherRect) {
        // https://stackoverflow.com/a/31035335
        if (thisRect.left < otherRect.right && thisRect.right > otherRect.left &&
            thisRect.bottom < otherRect.top && thisRect.top > otherRect.bottom)
                return true;

        return false;
    }

    inline static bool PointInside(Rect& thisRect, Vec2& point) {
        if (point.x >= thisRect.left && point.x <= thisRect.right &&
            point.y >= thisRect.bottom && point.y <= thisRect.top)
            return true;

        return false;
    }

    static Rect zero;

    f32 left;       // 0
    f32 bottom;     // 4
    f32 right;      // 8
    f32 top;        // C
};

#pragma once

#include "types.h"

struct Rect { // size: 0x10
    inline static bool RectsOverlap(Rect& thisRect, Rect& otherRect) {
        if (thisRect.left < otherRect.right && thisRect.right > otherRect.left && thisRect.bottom < otherRect.top && thisRect.top > otherRect.bottom)
            return true;
        else
            return false;
    }

    inline static bool PointInside(Rect& thisRect, Vec2f& point) {
        if (point.x >= thisRect.left && point.x <= thisRect.right && point.y >= thisRect.bottom && point.y <= thisRect.top)
            return true;
        else
            return false;
    }

    static Rect sZero;

    f32 left;       // _0
    f32 bottom;     // _4
    f32 right;      // _8
    f32 top;        // _C
};

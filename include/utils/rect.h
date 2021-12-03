#pragma once

#include <types.h>

struct Rect { // Size: 0x10
    static inline bool intersects(Rect& thisRect, Rect& otherRect) {
        if (thisRect.left < otherRect.right && thisRect.right > otherRect.left && thisRect.bottom < otherRect.top && thisRect.top > otherRect.bottom)
            return true;
        else
            return false;
    }

    static inline bool pointInside(Rect& thisRect, sead::Vec2f& point) {
        if (point.x >= thisRect.left && point.x <= thisRect.right && point.y >= thisRect.bottom && point.y <= thisRect.top)
            return true;
        else
            return false;
    }

    static Rect sZero;

    f32 left;       // 0
    f32 bottom;     // 4
    f32 right;      // 8
    f32 top;        // C
};

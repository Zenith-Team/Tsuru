#pragma once

#include <types.h>

class Direction {
public:
    enum DirectionType {
        DirectionType_Right = 0,
        DirectionType_Left  = 1,
        DirectionType_Up    = 2,
        DirectionType_Down  = 3
    };

    static u32 directionToRotationList[];
};

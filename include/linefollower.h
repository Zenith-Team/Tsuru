#pragma once

#include "states.h"
#include "util/vec2.h"

class LineFollower {  // size: 0x90
public:
    LineFollower();

    void init(const Vec2& position, u8 layer, bool noReverseOnStop, bool reversedDirection, f32 lineSpeed);
    void start(bool unk);

    void reverseDirection() {
        reversedDirection = reversedDirection ^ 1;
        lineSpeed = -lineSpeed;
    }
    void setLineSpeed(f32 speed) {
        if (reversedDirection)
            speed = -speed;

        lineSpeed = speed;
    }

    inline void execute() {
        states.execute();
    }

    StateWrapper<LineFollower> states;  // 0
    Vec2 _24[7];                        // 24 Inited to 0.0
    Vec2 speed;                         // 5C Inited to 0.0
    Vec2 position;                      // 64 Inited to 0.0
    Vec2 lastPosition;                  // 6C Inited to 0.0
    Vec2 blockPosition;                 // 74 Inited to 0.0
    Vec2 _7C;                           // 7C Inited to 0.0
    u32 rotation;                       // 84 Inited to 0
    f32 lineSpeed;                      // 88 Inited to 0.0
    bool noReverseOnStop;               // 8C Inited to false
    u8 layer;                           // 8D Inited to 0
    bool reversedDirection;             // 8E Inited to false
    u8 _8F;                             // 8F Inited to 0
};

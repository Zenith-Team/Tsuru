#pragma once

#include "states.h"

class LineFollower { // Size: 0x90 
public:
    LineFollower();

    void init(const Vec2f& position, u8 layer, bool noReverseOnStop, bool reversedDirection, f32 lineSpeed);
    void start(bool unk);

    void reverseDirection();
    void setLineSpeed(f32 speed);

    inline void execute() {
        states.execute();
    }

    StateWrapper<LineFollower> states;  // 0
    Vec2f _24[7];                       // 24 Inited to 0.0
    Vec2f speed;                        // 5C Inited to 0.0
    Vec2f position;                     // 64 Inited to 0.0
    Vec2f lastPosition;                 // 6C Inited to 0.0
    Vec2f blockPosition;                // 74 Inited to 0.0
    Vec2f _7C;                          // 7C Inited to 0.0
    u32 rotation;                       // 84 Inited to 0
    f32 lineSpeed;                      // 88 Inited to 0.0
    bool noReverseOnStop;               // 8C Inited to false
    u8 layer;                           // 8D Inited to 0
    bool reversedDirection;             // 8E Inited to false
    u8 _8F;                             // 8F Inited to 0
};

static_assert(sizeof(LineFollower) == 0x90, "LineFollower size mismatch");

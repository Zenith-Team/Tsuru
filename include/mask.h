#pragma once

#include "sead.h"
#include "util/vec3.h"

class LightMask {  // size: 0x24
public:
    LightMask();

    virtual bool init(sead::Heap* heap, u32 type);
    virtual bool update();
    virtual bool draw();

    //? This starts at 0 but the member names seem to start at offset 8 for some reason...
    f32 radius;     // 0
    f32 _8;         // 4
    Vec3 position;  // 8
    u32* _18;       // 14
    u32 _1C;        // 18
    u32 type;       // 1C
    u32 _24;        // 20
};

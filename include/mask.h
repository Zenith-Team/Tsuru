#pragma once

#include "sead.h"
#include "util/vec3.h"

class LightMask
{
public:
    LightMask();

    virtual bool init(sead::Heap* heap, u32 type);
    virtual bool update();
    virtual bool draw();

    f32 radius;
    f32 _8;
    Vec3 position;
    u32* _18;
    u32 _1C;
    u32 type;
    u32 _24;
};
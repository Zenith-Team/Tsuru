#pragma once

#include "sead.h"

class LightSource : sead::IDisposer
{
public:
    LightSource();
    ~LightSource();

    bool update(u32 type, Vec3* position, f32* _24, f32* attenuationRadius, f32* _2C, sead::Color4f* color, f32* _40, f32* _44);
    bool update(Vec3* position, f32* _24, f32* attenuationRadius, f32* _2C, sead::Color4f* color, f32* _40, f32* _44);

    bool _10;                       // 10   Inited?
    u32* _14;                       // 14   Pointer to a class
    Vec3 position;                  // 18
    f32 _24;                        // 24
    f32 attenuationRadius;          // 28   Inited to 1.0
    f32 _2C;                        // 2C
    sead::Color4f color;            // 30
    f32 _40;                        // 40
    f32 _44;                        // 44
};
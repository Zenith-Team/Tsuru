#pragma once

#include "sead.h"
#include "util/vec3.h"

class LightSource : public sead::IDisposer {  // size: 0x48
public:
    LightSource();
    virtual ~LightSource();

    bool update(u32 type, Vec3* position, u32* _24, f32* attenuationRadius, f32* _2C, sead::Color4f* color, u32* _40, f32* _44);
    bool update(Vec3* position, u32* _24, f32* attenuationRadius, f32* _2C, sead::Color4f* color, u32* _40, f32* _44);

    bool _10;                       // 10   Inited?
    void* _14;                      // 14   Pointer to a class
    Vec3 position;                  // 18
    u32 _24;                        // 24   Inited to 0
    f32 attenuationRadius;          // 28   Inited to 1.0
    f32 _2C;                        // 2C   Inited to 1.0
    sead::Color4f color;            // 30
    u32 _40;                        // 40   Inited to 0
    f32 _44;                        // 44   Inited to 0.0
};

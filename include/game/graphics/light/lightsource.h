#pragma once

#include <sead/idisposer.h>
#include <sead/color.h>

class LightSource : public sead::IDisposer { // Size: 0x48
    LightSource();
    virtual ~LightSource();

    bool update(Vec3f* position, f32*, f32* radius, f32*, sead::Color4f* color, f32*, f32*);
    bool update(u32 type, Vec3f* position, u32*, f32* radius, f32*, sead::Color4f* color, f32*, f32*);

    bool _10;
    void* _14;  // Pointer to a class
    Vec3f position;
    u32 _24;
    f32 radius;
    f32 _2C;
    sead::Color4f color;
    u32 _40;
    f32 _44;
};

static_assert(sizeof(LightSource) == 0x48, "LightSource size mismatch");

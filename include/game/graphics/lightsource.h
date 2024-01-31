#pragma once

#include "heap/seadDisposer.h"
#include "gfx/seadColor.h"

class LightSource : public sead::IDisposer { // Size: 0x48
public:
    ENUM_CLASS(Type); // TODO: Fill this in

public:
    LightSource();
    virtual ~LightSource();

    // Updates the light source
    // @param type Light source type
    // @param u32* Unknown
    // @param f32* Pointer to radius variable for the light source
    // @param f32* Unknown
    // @param color Pointer to sead::Color4f variable to determine the color of the light source
    bool update(u32 type, sead::Vector3f* position, u32*, f32* radius, f32*, sead::Color4f* color, f32* = nullptr, f32* = nullptr);

private:
    // Updates the light source
    bool update(sead::Vector3f* position, f32*, f32* radius, f32*, sead::Color4f* color, f32* = nullptr, f32* = nullptr);

public:
    bool _10;
    void* _14;  // Pointer to a class
    sead::Vector3f position;
    u32 _24;
    f32 radius;
    f32 _2C;
    sead::Color4f color;
    u32 _40;
    f32 _44;
};

static_assert(sizeof(LightSource) == 0x48, "LightSource size mismatch");

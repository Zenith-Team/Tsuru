#pragma once

#include <sead.h>
#include <types.h>

#include "drawmethod.h"

namespace agl { namespace lyr {

class Layer : public sead::IDisposer { // Size: 0x41C
private:
    struct DebugInfo {
        u8 _0[0x390]; // TODO: I'll do this later
    };

public:
    Layer();
    virtual ~Layer();

    // TODO: Return types, parameters, names for these:
    SEAD_RTTI_BASE(Layer)
    virtual void vf24() = 0;
    virtual void vf2C() = 0;
    virtual void vf34();
    virtual void vf3C();
    virtual void vf44();
    virtual void vf4C();
    virtual void vf54();
    virtual void vf5C();

    void initialize_(sead::Heap* heap);

    DrawMethod* pushBackDrawMethod(u32, DrawMethod* drawMethod);

    u8 _10[0x4];
    sead::Viewport _14;
    sead::Viewport _2C;
    sead::Camera* camera;
    sead::Projection* projection;
    u32 _4C;
    u32 _50;
    u32 _54;
    u8 _58[0x4];
    s32 _5C;
    u32 _60;
    u32 _64;
    u32 _68;
    f32 _6C;
    f32 _70;
    f32 _74;
    f32 _78;
    f32 _7C;
    Vec2i _80;
    u32 _88;
    DebugInfo debugInfo;
};

static_assert(sizeof(Layer) == 0x41C, "agl::lyr::Layer size mismatch");

} }

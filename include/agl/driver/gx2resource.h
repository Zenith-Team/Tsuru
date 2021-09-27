#pragma once

#include <sead/idisposer.h>
#include <sead/criticalsection.h>

namespace agl { namespace driver {

class GX2Resource { // Size: 0x80
    SEAD_SINGLETON_DISPOSER(GX2Resource)

public:
    GX2Resource();
    virtual ~GX2Resource();

    u32 initialize(sead::Heap* heap, u32, u32, bool);

    void restoreContextState();

    void setGeometryShaderRingBuffer() const;

    void setShaderMode(u32 shaderMode, const void* shaderOptimizeInfo) const;   // Second parameter is actually const agl::ShaderOptimizeInfo&
    void setShaderMode(u32 shaderMode) const;

    u32 _10;
    u8 _14[0x10];   // Unknown values
    u32 _24;
    u32 _28;
    u32 _2C;
    u32 _30;
    u32 _34;
    u32 _38;
    sead::CriticalSection _3C;
    u8 _78;
    u8 _79;
};

static_assert(sizeof(GX2Resource) == 0x80, "agl::driver::GX2Resource size mismatch");

} }

#pragma once

#include "sead/idisposer.h"
#include "sead/listimpl.h"
#include "agl/texturesampler.h"

class PtclMgr {
    SEAD_SINGLETON_DISPOSER(PtclMgr);

public:
    PtclMgr();

    void setFrameBufferTexture(const agl::TextureSampler& texture, f32 xOffset = 0.0f, f32 yOffset = 0.0f, f32 xScale = 1.0f, f32 yScale = 1.0f);

    void* ptclSystem; // sead::ptcl::PtclSystem*
    void* ptclParallelTbl;
    void* colors;
    void* userShaderParamTbl;
    sead::ListImpl effects; // sead::TList
    u32 emitter1[0x40C / sizeof(u32)]; // sead::FixedPtrArray<nw::eft::EmitterInstance, 256>
    u32 emitter2[0x40C / sizeof(u32)]; // sead::FixedPtrArray<nw::eft::EmitterInstance, 256>
    s32 playerID;
    bool isUseDisplayList;
    u8 _849;
    bool isUseParallel;
};

static_assert(sizeof(PtclMgr) == 0x84C, "PtclMgr size mismatch");

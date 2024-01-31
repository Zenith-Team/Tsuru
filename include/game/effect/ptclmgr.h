#pragma once

#include "heap/seadDisposer.h"
#include "container/seadTList.h"
#include "container/seadPtrArray.h"
#include "common/aglTextureSampler.h"
#include "layer/aglRenderInfo.h"
#include "nw/eft/eft_Emitter.h"

class LevelEffect;
class PtclLightMgr;

class PtclMgr {
    SEAD_SINGLETON_DISPOSER(PtclMgr);

public:
    PtclMgr();

    void draw(const agl::lyr::RenderInfo& renderInfo, u32 type, const sead::PtrArray<nw::eft::EmitterInstance>* emitters = nullptr);

    void setFrameBufferTexture(const agl::TextureSampler& texture, f32 xOffset = 0.0f, f32 yOffset = 0.0f, f32 xScale = 1.0f, f32 yScale = 1.0f);

    void* ptclSystem; // sead::ptcl::PtclSystem*
    void* ptclParallelTbl;
    PtclLightMgr* lightMgr;
    void* userShaderParamTbl;
    sead::TList<LevelEffect> effects;
    sead::FixedPtrArray<nw::eft::EmitterInstance, 256> emitter1;
    sead::FixedPtrArray<nw::eft::EmitterInstance, 256> emitter2;
    s32 playerID;
    bool isUseDisplayList;
    bool isDrawDisable;
    bool isUseParallel;
};

static_assert(sizeof(PtclMgr) == 0x84C, "PtclMgr size mismatch");

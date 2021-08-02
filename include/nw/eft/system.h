#pragma once

#include "nw/math/mtx44.h"
#include "nw/eft/enum.h"

namespace nw { namespace eft {

struct EmitterInstance;
struct PtclInstance;
class Renderer;

struct EmitterPreCalcArg {
    EmitterInstance* mEmitter;
};

static_assert(sizeof(EmitterPreCalcArg) == 4, "EmitterPreCalcArg size mismatch");

struct EmitterPostCalcArg {
    EmitterInstance* mEmitter;
};

static_assert(sizeof(EmitterPostCalcArg) == 4, "EmitterPostCalcArg size mismatch");

struct ParticleEmitArg {
    PtclInstance* mPtcl;
};

static_assert(sizeof(ParticleEmitArg) == 4, "ParticleEmitArg size mismatch");

struct ParticleRemoveArg {
    PtclInstance* mPtcl;
};

static_assert(sizeof(ParticleRemoveArg) == 4, "ParticleRemoveArg size mismatch");

struct ParticleCalcArg {
    EmitterInstance* mEmitter;
    PtclInstance* mPtcl;
    CpuCore mCore;
    bool mNoCalcBehavior;
};

static_assert(sizeof(ParticleCalcArg) == 0x10, "ParticleCalcArg size mismatch");

struct ParticleMakeAttrArg {
    EmitterInstance* mEmitter;
    PtclInstance* mPtcl;
    CpuCore mCore;
    bool mNoCalcBehavior;
};

static_assert(sizeof(ParticleMakeAttrArg) == 0x10, "ParticleMakeAttrArg size mismatch");

struct EmitterDrawOverrideArg {
    const EmitterInstance* mEmitter;
    Renderer* mRenderer;
    bool mFlushCache;
    void* mArgData;
};

static_assert(sizeof(EmitterDrawOverrideArg) == 0x10, "EmitterDrawOverrideArg size mismatch");

struct ShaderEmitterPostCalcArg {
    EmitterInstance* mEmitter;
    bool mNoCalcBehavior;
    bool mChildParticle;
};

static_assert(sizeof(ShaderEmitterPostCalcArg) == 8, "ShaderEmitterPostCalcArg size mismatch");

struct ShaderDrawOverrideArg {
    const EmitterInstance* mEmitter;
    Renderer* mRenderer;
    bool mFlushCache;
    void* mArgData;
};

static_assert(sizeof(ShaderDrawOverrideArg) == 0x10, "ShaderDrawOverrideArg size mismatch");

struct RenderStateSetArg {
    const EmitterInstance* mEmitter;
    Renderer* mRenderer;
    bool mFlushCache;
    void* mArgData;
};

static_assert(sizeof(RenderStateSetArg) == 0x10, "RenderStateSetArg size mismatch");

typedef void (*CustomActionEmitterPreCalcCallback)(EmitterPreCalcArg& arg);
typedef void (*CustomActionEmitterPostCalcCallback)(EmitterPostCalcArg& arg);
typedef bool (*CustomActionParticleEmitCallback)(ParticleEmitArg& arg);
typedef bool (*CustomActionParticleRemoveCallback)(ParticleRemoveArg& arg);
typedef void (*CustomActionParticleCalcCallback)(ParticleCalcArg& arg);
typedef void (*CustomActionParticleMakeAttributeCallback)(const ParticleMakeAttrArg& arg); //? const?
typedef void (*CustomActionEmitterDrawOverrideCallback)(EmitterDrawOverrideArg& arg);
typedef void (*CustomShaderEmitterPostCalcCallback)(ShaderEmitterPostCalcArg& arg);
typedef void (*CustomShaderDrawOverrideCallback)(ShaderDrawOverrideArg& arg);
typedef void (*CustomShaderRenderStateSetCallback)(RenderStateSetArg& arg);

struct AlphaAnim;
class Config;
class EmitterCalc;
class EmitterSet;
struct EmitterStaticUniformBlock;
class Handle;
class Heap;
class PtclStripe;
class Resource;
struct ScaleAnim; // ?
struct SimpleEmitterData;

class System { // Size: 0xA28
public:
    struct PtclViewZ { // Size: 0x8
        EmitterSet* mEmitterSet;
        u32 mZ;
    };

    static_assert(sizeof(PtclViewZ) == 8, "PtclViewZ size mismatch");

public:
    System(const Config& config);
    virtual ~System(); // deleted

    virtual void Initialize(Heap* heap, const Config& config);

    void RemoveStripe(PtclStripe* stripe);
    void RemovePtcl_();
    EmitterSet* RemoveEmitterSetFromDrawList(EmitterSet* emitterSet);
    void RemovePtcl();
    void AddPtclRemoveList(PtclInstance* ptcl, CpuCore core);
    void EmitChildParticle();
    void AddPtclAdditionList(PtclInstance* ptcl, CpuCore core);
    PtclStripe* AllocAndConnectStripe(EmitterInstance* emitter, PtclInstance* ptcl);
    PtclInstance* AllocPtcl(PtclType type);
    EmitterSet* AllocEmitterSet(Handle* handle);
    EmitterInstance* AllocEmitter(u8 groupID);
    void AddEmitterSetToDrawList(EmitterSet* emitterSet, u8 groupID);

    void InitializeEmitter(EmitterInstance* emitter, const SimpleEmitterData* data, u32 resourceID, s32 emitterSetID, u32 seed, bool keepCreateID);
    bool CreateEmitterSetID(Handle* handle, const math::MTX34& matrixSRT, s32 emitterSetID, u32 resourceID, u8 groupID, u32 emitterEnableMask = 0xFFFFFFFF);

    void BeginFrame();
    void SwapDoubleBuffer();
    void CalcEmitter(u8 groupID, f32 emissionSpeed = 1.0f);
    void CalcParticle(EmitterInstance* emitter, CpuCore core);
    void CalcChildParticle(EmitterInstance* emitter, CpuCore core);
    void FlushCache();
    void FlushGpuCache();
    inline void CalcEmitter(EmitterInstance* emitter, f32 emissionSpeed);
    void CalcParticle(bool flushCache);
    void Calc(bool flushCache);
    void BeginRender(const math::MTX44& proj, const math::MTX34& view, const math::VEC3& cameraWorldPos, f32 zNear, f32 zFar);
    void RenderEmitter(EmitterInstance* emitter, bool flushCache, void* argData);
    void EndRender();

    void ClearResource(Heap* heap, u32 resourceID);
    void EntryResource(Heap* heap, void* resource, u32 resourceID);
    void KillEmitter(EmitterInstance* emitter);
    void KillEmitterGroup(u8 groupID);
    void KillEmitterSet(EmitterSet* emitterSet);

    CustomActionEmitterPreCalcCallback GetCurrentCustomActionEmitterPreCalcCallback(const EmitterInstance* emitter);
    CustomActionEmitterPostCalcCallback GetCurrentCustomActionEmitterPostCalcCallback(const EmitterInstance* emitter);
    CustomActionParticleEmitCallback GetCurrentCustomActionParticleEmitCallback(const EmitterInstance* emitter);
    CustomActionParticleRemoveCallback GetCurrentCustomActionParticleRemoveCallback(const EmitterInstance* emitter);
    CustomActionParticleCalcCallback GetCurrentCustomActionParticleCalcCallback(const EmitterInstance* emitter);
    CustomActionParticleMakeAttributeCallback GetCurrentCustomActionParticleMakeAttributeCallback(const EmitterInstance* emitter);
    CustomActionEmitterDrawOverrideCallback GetCurrentCustomActionEmitterDrawOverrideCallback(const EmitterInstance* emitter);
    CustomShaderEmitterPostCalcCallback GetCustomShaderEmitterPostCalcCallback(CustomShaderCallBackID callbackID);
    CustomShaderDrawOverrideCallback GetCustomShaderDrawOverrideCallback(CustomShaderCallBackID callbackID);
    CustomShaderRenderStateSetCallback GetCustomShaderRenderStateSetCallback(CustomShaderCallBackID callbackID);

    // For qsort
    static int ComparePtclViewZ(const void* a, const void* b);

    bool mInitialized;
    Heap* mHeap;
    Resource** mResources;
    u32 mNumResourceMax;
    EmitterSet* mEmitterSets;
    s32 mNumEmitterSetMax;
    s32 mNumEmitterSetMaxMask;
    math::MTX44 mView[CpuCoreMax];
    EmitterInstance* mEmitterGroups[64];  // Maximum of 64 groups
    EmitterSet* mEmitterSetGroupHead[64]; // Maximum of 64 groups
    EmitterSet* mEmitterSetGroupTail[64]; // Maximum of 64 groups
    EmitterInstance* mEmitters;
    EmitterStaticUniformBlock* mEmitterStaticUniformBlocks;
    s32 mCurrentEmitterIdx;
    s32 mNumUnusedEmitters;
    PtclInstance* mParticles;
    s32 mCurrentParticleIdx;
    AlphaAnim* mAlphaAnim;
    ScaleAnim* mScaleAnim;
    PtclInstance** mChildParticles[CpuCoreMax];
    s32 mNumChildParticle[CpuCoreMax];
    PtclInstance** mParticlesToRemove[CpuCoreMax];
    s32 mNumParticleToRemove[CpuCoreMax];
    PtclStripe* mStripes;
    PtclStripe* mStripeGroups[64]; // Maximum of 64 groups
    u32 mUnused0;
    s32 mCurrentEmitterSetIdx;
    s32 mCurrentStripeIdx;
    s32 mNumEmitterMax;
    s32 mNumParticleMax;
    s32 mNumStripeMax;
    s32 mNumEmitterMaxMask;
    s32 mNumParticleMaxMask;
    s32 mNumStripeMaxMask;
    u32 mNumCalcEmitter;
    u32 mNumCalcParticle;
    u32 mNumCalcEmitterSet;
    u32 mNumEmittedParticle;
    u32 mNumCalcStripe;
    u64 mActiveGroupsFlg;
    u32 mUnusedFlags[CpuCoreMax][64]; // Maximum of 64 groups
    Renderer* mRenderers[CpuCoreMax];
    u32 mCurrentEmitterSetCreateID;
    EmitterCalc* mEmitterCalc[EmitterTypeMax];
    void* mResourceWork;
    void* mEmitterSetWork;
    void* mRendererWork[CpuCoreMax];
    void* mEmitterSimpleCalcWork;
    void* mEmitterComplexCalcWork;
    u8 mUnusedPad[4];
    s32 mUnkCallbackVal; // When not equal to -1, currentCallbackID must be valid
    CustomActionCallBackID currentCallbackID;
    CustomActionEmitterPreCalcCallback customActionEmitterPreCalcCallback[CustomActionCallBackIDMax];
    CustomActionParticleEmitCallback customActionParticleEmitCallback[CustomActionCallBackIDMax];
    CustomActionParticleRemoveCallback customActionParticleRemoveCallback[CustomActionCallBackIDMax];
    CustomActionParticleCalcCallback customActionParticleCalcCallback[CustomActionCallBackIDMax];
    CustomActionParticleMakeAttributeCallback customActionParticleMakeAttributeCallback[CustomActionCallBackIDMax];
    CustomActionEmitterPostCalcCallback customActionEmitterPostCalcCallback[CustomActionCallBackIDMax];
    CustomActionEmitterDrawOverrideCallback customActionEmitterDrawOverrideCallback[CustomActionCallBackIDMax];
    CustomShaderEmitterPostCalcCallback customShaderEmitterPostCalcCallback[CustomShaderCallBackIDMax];
    CustomShaderDrawOverrideCallback customShaderDrawOverrideCallback[CustomShaderCallBackIDMax];
    CustomShaderRenderStateSetCallback customShaderRenderStateSetCallback[CustomShaderCallBackIDMax];
    PtclViewZ* sortedEmitterSets[CpuCoreMax];
    u32 numSortedEmitterSets[CpuCoreMax];
    u32 _unused1[CpuCoreMax];
    u32 doubleBufferSwapped;
};

static_assert(sizeof(System) == 0xA28, "System size mismatch");

} }

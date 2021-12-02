#pragma once

#include <nw/math/mtx44.h>
#include <nw/eft/enum.h>

namespace nw { namespace eft {

struct EmitterInstance;
struct PtclInstance;
class Renderer;

struct EmitterPreCalcArg {
    EmitterInstance* emitter;
};

static_assert(sizeof(EmitterPreCalcArg) == 4, "nw::eft::EmitterPreCalcArg size mismatch");

struct EmitterPostCalcArg {
    EmitterInstance* emitter;
};

static_assert(sizeof(EmitterPostCalcArg) == 4, "nw::eft::EmitterPostCalcArg size mismatch");

struct ParticleEmitArg {
    PtclInstance* ptcl;
};

static_assert(sizeof(ParticleEmitArg) == 4, "nw::eft::ParticleEmitArg size mismatch");

struct ParticleRemoveArg {
    PtclInstance* ptcl;
};

static_assert(sizeof(ParticleRemoveArg) == 4, "nw::eft::ParticleRemoveArg size mismatch");

struct ParticleCalcArg {
    EmitterInstance* emitter;
    PtclInstance* ptcl;
    CpuCore core;
    bool noCalcBehavior;
};

static_assert(sizeof(ParticleCalcArg) == 0x10, "nw::eft::ParticleCalcArg size mismatch");

struct ParticleMakeAttrArg {
    EmitterInstance* emitter;
    PtclInstance* ptcl;
    CpuCore core;
    bool noCalcBehavior;
};

static_assert(sizeof(ParticleMakeAttrArg) == 0x10, "nw::eft::ParticleMakeAttrArg size mismatch");

struct EmitterDrawOverrideArg {
    const EmitterInstance* emitter;
    Renderer* renderer;
    bool flushCache;
    void* argData;
};

static_assert(sizeof(EmitterDrawOverrideArg) == 0x10, "nw::eft::EmitterDrawOverrideArg size mismatch");

struct ShaderEmitterPostCalcArg {
    EmitterInstance* emitter;
    bool noCalcBehavior;
    bool childParticle;
};

static_assert(sizeof(ShaderEmitterPostCalcArg) == 8, "nw::eft::ShaderEmitterPostCalcArg size mismatch");

struct ShaderDrawOverrideArg {
    const EmitterInstance* emitter;
    Renderer* renderer;
    bool flushCache;
    void* argData;
};

static_assert(sizeof(ShaderDrawOverrideArg) == 0x10, "nw::eft::ShaderDrawOverrideArg size mismatch");

struct RenderStateSetArg {
    const EmitterInstance* emitter;
    Renderer* renderer;
    bool flushCache;
    void* argData;
};

static_assert(sizeof(RenderStateSetArg) == 0x10, "nw::eft::RenderStateSetArg size mismatch");

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
        EmitterSet* emitterSet;
        u32 z;
    };

    static_assert(sizeof(PtclViewZ) == 8, "nw::eft::System::PtclViewZ size mismatch");

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
    static s32 ComparePtclViewZ(const void* a, const void* b);

    bool initialized;
    Heap* heap;
    Resource** resources;
    u32 numResourceMax;
    EmitterSet* emitterSets;
    s32 numEmitterSetMax;
    s32 numEmitterSetMaxMask;
    math::MTX44 view[CpuCore_Max];
    EmitterInstance* emitterGroups[64];  // Maximum of 64 groups
    EmitterSet* emitterSetGroupHead[64]; // Maximum of 64 groups
    EmitterSet* emitterSetGroupTail[64]; // Maximum of 64 groups
    EmitterInstance* emitters;
    EmitterStaticUniformBlock* emitterStaticUniformBlocks;
    s32 currentEmitterIdx;
    s32 numUnusedEmitters;
    PtclInstance* particles;
    s32 currentParticleIdx;
    AlphaAnim* alphaAnim;
    ScaleAnim* scaleAnim;
    PtclInstance** childParticles[CpuCore_Max];
    s32 numChildParticle[CpuCore_Max];
    PtclInstance** particlesToRemove[CpuCore_Max];
    s32 numParticleToRemove[CpuCore_Max];
    PtclStripe* stripes;
    PtclStripe* stripeGroups[64]; // Maximum of 64 groups
    u32 unused0;
    s32 currentEmitterSetIdx;
    s32 currentStripeIdx;
    s32 numEmitterMax;
    s32 numParticleMax;
    s32 numStripeMax;
    s32 numEmitterMaxMask;
    s32 numParticleMaxMask;
    s32 numStripeMaxMask;
    u32 numCalcEmitter;
    u32 numCalcParticle;
    u32 numCalcEmitterSet;
    u32 numEmittedParticle;
    u32 numCalcStripe;
    u64 activeGroupsFlg;
    u32 unusedFlags[CpuCore_Max][64]; // Maximum of 64 groups
    Renderer* renderers[CpuCore_Max];
    u32 currentEmitterSetCreateID;
    EmitterCalc* emitterCalc[EmitterType_Max];
    void* resourceWork;
    void* emitterSetWork;
    void* rendererWork[CpuCore_Max];
    void* emitterSimpleCalcWork;
    void* emitterComplexCalcWork;
    u8 unusedPad[4];
    s32 unkCallbackVal; // When not equal to -1, currentCallbackID must be valid
    CustomActionCallBackID currentCallbackID;
    CustomActionEmitterPreCalcCallback customActionEmitterPreCalcCallback[CustomActionCallBackID_Max];
    CustomActionParticleEmitCallback customActionParticleEmitCallback[CustomActionCallBackID_Max];
    CustomActionParticleRemoveCallback customActionParticleRemoveCallback[CustomActionCallBackID_Max];
    CustomActionParticleCalcCallback customActionParticleCalcCallback[CustomActionCallBackID_Max];
    CustomActionParticleMakeAttributeCallback customActionParticleMakeAttributeCallback[CustomActionCallBackID_Max];
    CustomActionEmitterPostCalcCallback customActionEmitterPostCalcCallback[CustomActionCallBackID_Max];
    CustomActionEmitterDrawOverrideCallback customActionEmitterDrawOverrideCallback[CustomActionCallBackID_Max];
    CustomShaderEmitterPostCalcCallback customShaderEmitterPostCalcCallback[CustomShaderCallBackID_Max];
    CustomShaderDrawOverrideCallback customShaderDrawOverrideCallback[CustomShaderCallBackID_Max];
    CustomShaderRenderStateSetCallback customShaderRenderStateSetCallback[CustomShaderCallBackID_Max];
    PtclViewZ* sortedEmitterSets[CpuCore_Max];
    u32 numSortedEmitterSets[CpuCore_Max];
    u32 _unused1[CpuCore_Max];
    u32 doubleBufferSwapped;
};

static_assert(sizeof(System) == 0xA28, "nw::eft::System size mismatch");

} }

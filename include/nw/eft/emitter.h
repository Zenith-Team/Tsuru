#pragma once

#include <nw/eft/particle.h>
#include <nw/eft/random.h>
#include <nw/eft/resdata.h>

namespace nw { namespace eft {

class Primitive;
class EmitterSet;
class EmitterCalc;
class ParticleShader;
class EmitterController;
class StripeVertexBuffer;
struct KeyFrameAnimArray;
struct PtclAttributeBuffer;
struct EmitterStaticUniformBlock;
struct EmitterDynamicUniformBlock;

struct EmitterInstance { // Size: 0x220
    void Init(const SimpleEmitterData* data);
    inline void UpdateEmitterStaticUniformBlock(EmitterStaticUniformBlock* uniformBlock, const SimpleEmitterData* data);
    inline void UpdateChildStaticUniformBlock(EmitterStaticUniformBlock* uniformBlock, const ChildData* data);
    void UpdateResInfo();

    const ComplexEmitterData* GetComplexEmitterData() const {
        if (this->mData->mType != EmitterTypeComplex)
            return NULL;
        
        return static_cast<const ComplexEmitterData*>(this->mData);
    }

    bool HasChild() const {
        return this->mData->mType != EmitterTypeSimple && (static_cast<const ComplexEmitterData*>(this->mData)->mChildFlags & 1);
    }

    const ChildData* GetChildData() const {
        if (!HasChild())
            return NULL;
        
        return reinterpret_cast<const ChildData*>(static_cast<const ComplexEmitterData*>(this->mData) + 1);
    }

    f32 mCounter;
    f32 mCounter2;
    f32 mEmitCounter;
    f32 mPreCalcCounter;
    f32 mEmitLostTime;
    u32 mNumParticles;
    u32 mNumChildParticles;
    u32 mGroupID;
    EmitterSet* mEmitterSet;
    EmitterController* mController;
    u32 mEmitterSetCreateID;
    math::MTX34 mMatrixRT;
    math::MTX34 mMatrixSRT;
    PtclRandom mRandom;
    s32 mEmissionInterval;
    f32 mFadeAlpha;
    f32 mEmissionSpeed;
    math::VEC3 mPrevPos;   // Used for equidistant emission
    bool mPrevPosSet;      // ^^
    f32 mEmitLostDistance; // ^^
    math::VEC3 mScaleRandom;
    math::VEC3 mRotateRandom;
    math::VEC3 mTranslateRandom;
    PtclFollowType mPtclFollowType;
    EmitterInstance* mPrev;
    EmitterInstance* mNext;
    EmitterCalc* mCalc;
    const SimpleEmitterData* mData;
    PtclInstance* mParticleHead;
    PtclInstance* mChildParticleHead;
    PtclInstance* mParticleTail;
    PtclInstance* mChildParticleTail;
    ParticleShader* mShader[ShaderTypeMax];
    ParticleShader* mChildShader[ShaderTypeMax];
    Primitive* mPrimitive;
    Primitive* mChildPrimitive;
    KeyFrameAnimArray* mAnimArray;
    f32 mAnim[25];
    math::MTX34 mAnimMatrixRT;
    math::MTX34 mAnimMatrixSRT;
    f32 mEmitLostRate;
    bool mIsEmitted;
    bool mIsCalculated;
    u8 mUnused;
    u32 mParticleBehaviorFlg;
    u32 mShaderAvailableAttribFlg;
    u32 mChildShaderAvailableAttribFlg;
    u32 mNumDrawParticle;
    u32 mNumDrawChildParticle;
    u32 mNumDrawStripe;
    PtclAttributeBuffer* mPtclAttributeBuffer;
    PtclAttributeBuffer* mChildPtclAttributeBuffer;
    StripeVertexBuffer* mStripeVertexBuffer;
    EmitterStaticUniformBlock* mEmitterStaticUniformBlock;
    EmitterStaticUniformBlock* mChildEmitterStaticUniformBlock;
    EmitterDynamicUniformBlock* mEmitterDynamicUniformBlock;
    EmitterDynamicUniformBlock* mChildEmitterDynamicUniformBlock;
};

static_assert(sizeof(EmitterInstance) == 0x220, "EmitterInstance size mismatch");

class System;

class EmitterCalc {
public:
    EmitterCalc(System* system) {
        sSys = system;
    }

    virtual ~EmitterCalc() { } // deleted
    virtual void CalcEmitter(EmitterInstance* emitter) = 0;
    virtual PtclType GetPtclType() const = 0;
    virtual u32 CalcParticle(EmitterInstance* emitter, CpuCore core, bool noCalcBehavior, bool noMakePtclAttributeBuffer) = 0;
    virtual u32 CalcChildParticle(EmitterInstance* emitter, CpuCore core, bool noCalcBehavior, bool noMakePtclAttributeBuffer) = 0;

    static void RemoveParticle(EmitterInstance* emitter, PtclInstance* ptcl, CpuCore core);
    static inline void AddChildPtclToList(EmitterInstance* emitter, PtclInstance* childPtcl) {
        if (emitter->mChildParticleHead == NULL) {
            emitter->mChildParticleHead = childPtcl;
            childPtcl->mNext = NULL;
            childPtcl->mPrev = NULL;
        }
        
        else {
            emitter->mChildParticleHead->mPrev = childPtcl;
            childPtcl->mNext = emitter->mChildParticleHead;
            emitter->mChildParticleHead = childPtcl;
            childPtcl->mPrev = NULL;
        }

        if (emitter->mChildParticleTail == NULL)
            emitter->mChildParticleTail = childPtcl;

        emitter->mNumChildParticles++;
    }

    static inline void AddPtclToList(EmitterInstance* emitter, PtclInstance* ptcl) {
        if (emitter->mParticleHead == NULL) {
            emitter->mParticleHead = ptcl;
            ptcl->mNext = NULL;
            ptcl->mPrev = NULL;
        }

        else {
            emitter->mParticleHead->mPrev = ptcl;
            ptcl->mNext = emitter->mParticleHead;
            emitter->mParticleHead = ptcl;
            ptcl->mPrev = NULL;
        }

        if (emitter->mParticleTail == NULL)
            emitter->mParticleTail = ptcl;

        emitter->mNumParticles++;
    }

    static void EmitCommon(EmitterInstance* emitter, PtclInstance* ptcl);

    static const void* _ptclField_Random(EmitterInstance* emitter, PtclInstance* ptcl, const void* fieldData);
    static const void* _ptclField_Magnet(EmitterInstance* emitter, PtclInstance* ptcl, const void* fieldData);
    static const void* _ptclField_Spin(EmitterInstance* emitter, PtclInstance* ptcl, const void* fieldData);
    static const void* _ptclField_Collision(EmitterInstance* emitter, PtclInstance* ptcl, const void* fieldData);
    static const void* _ptclField_Convergence(EmitterInstance* emitter, PtclInstance* ptcl, const void* fieldData);
    static const void* _ptclField_PosAdd(EmitterInstance* emitter, PtclInstance* ptcl, const void* fieldData);

    static void InitializeFluctuationTable(Heap* heap);
    static void CalcFluctuation(EmitterInstance* emitter, PtclInstance* ptcl);

    static u32 CalcSimpleParticleBehavior(EmitterInstance* emitter, PtclInstance* ptcl, CpuCore core);
    static u32 CalcComplexParticleBehavior(EmitterInstance* emitter, PtclInstance* ptcl, CpuCore core);
    static u32 CalcChildParticleBehavior(EmitterInstance* emitter, PtclInstance* ptcl);
    static void MakeParticleAttributeBuffer(PtclAttributeBuffer* ptclAttributeBuffer, PtclInstance* ptcl, u32 shaderAvailableAttribFlg, f32 cameraOffset);

    void ApplyAnim(EmitterInstance* emitter);
    void UpdateEmitterInfoByEmit(EmitterInstance* emitter);

    static PtclInstance* CalcEmitPoint(EmitterInstance* emitter);
    static PtclInstance* CalcEmitCircle(EmitterInstance* emitter);
    static PtclInstance* CalcEmitCircleSameDivide(EmitterInstance* emitter);
    static PtclInstance* CalcEmitFillCircle(EmitterInstance* emitter);
    static PtclInstance* CalcEmitSphere(EmitterInstance* emitter);
    static PtclInstance* CalcEmitSphereSameDivide(EmitterInstance* emitter);
    static PtclInstance* CalcEmitSphereSameDivide64(EmitterInstance* emitter);
    static PtclInstance* CalcEmitFillSphere(EmitterInstance* emitter);
    static PtclInstance* CalcEmitCylinder(EmitterInstance* emitter);
    static PtclInstance* CalcEmitFillCylinder(EmitterInstance* emitter);
    static PtclInstance* CalcEmitBox(EmitterInstance* emitter);
    static PtclInstance* CalcEmitFillBox(EmitterInstance* emitter);
    static PtclInstance* CalcEmitLine(EmitterInstance* emitter);
    static PtclInstance* CalcEmitLineSameDivide(EmitterInstance* emitter);
    static PtclInstance* CalcEmitRectangle(EmitterInstance* emitter);

    static f32* sFluctuationTbl;
    static System* sSys;

    typedef PtclInstance* (*EmitFunction)(EmitterInstance* emitter);
    static EmitFunction mEmitFunctions[];
};

static_assert(sizeof(EmitterCalc) == 4, "EmitterCalc size mismatch");



} }

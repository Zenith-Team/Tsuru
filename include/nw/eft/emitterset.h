#pragma once

#include <nw/math/mtx34.h>
#include <nw/math/vec3.h>
#include <nw/ut/color4f.h>
#include <nw/eft/enum.h>

namespace nw { namespace eft {

struct EmitterInstance;

class EmitterController { // Size: 0x14
public:
    void SetFollowType(PtclFollowType followType);

    f32 mEmissionRatio;
    f32 mEmissionInterval;
    f32 mLife;
    u32 mRenderVisibilityFlags;
    EmitterInstance* mEmitter;
};

static_assert(sizeof(EmitterController) == 0x14, "EmitterController size mismatch");

class System;

class EmitterSet { // Size: 0x294
public:
    EmitterSet()
        : mNumEmitter(0)
        , mNumEmitterAtCreate(0)
        , mCreateID(0)
        , mUserData(0)
        , mEmissionPoints(NULL)
    {
        mColor.v    = (math::VEC4){ 1.0f, 1.0f, 1.0f, 1.0f };
        mPtclRotate = (math::VEC3){ 1.0f, 1.0f, 1.0f };

        for (u32 i = 0; i < 16u; i++)
            mEmitters[i] = NULL;
    }

    void SetMtx(const math::MTX34& matrixSRT);
    void Kill();

    System* mSystem;
    s32 mNumEmitter;
    s32 mNumEmitterAtCreate;
    u32 mCreateID;
    EmitterInstance* mEmitters[16];
    EmitterController mControllers[16];
    u32 mResourceID;
    u32 mEmitterSetID;
    u32 mUserData;
    u32 mGroupID;
    u32 mUnusedFlags;
    math::MTX34 mMatrixSRT;
    math::MTX34 mMatrixRT;
    math::VEC3 mScaleForMatrix;
    math::VEC2 mPtclScale;
    math::VEC2 mPtclEmitScale;
    math::VEC2 mPtclEffectiveScale;
    math::VEC3 mEmitterVolumeScale;
    ut::Color4f mColor;
    f32 mAllDirVel;
    f32 mDirVel;
    f32 mDirVelRandom;
    math::VEC3 mAddVelocity;
    math::VEC3 mDir;
    s32 mStartFrame;
    math::VEC3 mPtclRotate;
    s32 mNumEmissionPoints;
    math::VEC3* mEmissionPoints;
    EmitterSet* mNext;
    EmitterSet* mPrev;
    u8 mDoFade;
    u8 mDirSet;
    u8 mNoCalc;
    u8 mNoDraw;
    u8 mInfiniteLifespan;
    u8 mUnused;
    u8 mUnusedPad[6];
};

static_assert(sizeof(EmitterSet) == 0x294, "EmitterSet size mismatch");

} }

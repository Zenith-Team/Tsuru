#pragma once

#include "nw/math/vec3.h"
#include "nw/math/mtx34.h"
#include "nw/ut/color4f.h"
#include "nw/eft/enum.h"

namespace nw { namespace eft {

struct AlphaAnim { // Size: 0x10
    f32 mStartDiff;
    f32 mEndDiff;
    s32 mTime2;
    s32 mTime3;
};

static_assert(sizeof(AlphaAnim) == 0x10, "AlphaAnim size mismatch");

struct ScaleAnim { // Size: 0x18
    math::VEC2 mStartDiff;
    math::VEC2 mEndDiff;
    s32 mTime2;
    s32 mTime3;
};

static_assert(sizeof(ScaleAnim) == 0x18, "ScaleAnim size mismatch");

struct TexUVParam { // Size: 0x1C
    f32 mRotate;
    math::VEC2 mOffset;
    math::VEC2 mScroll;
    math::VEC2 mScale;
};

static_assert(sizeof(TexUVParam) == 0x1C, "TexUVParam size mismatch");

struct EmitterInstance;
struct PtclAttributeBuffer;
struct PtclStripe;
struct SimpleEmitterData;

struct PtclInstance { // Size: 0x180
    f32 mCounter;
    s32 mLifespan;
    math::VEC3 mPos;
    math::VEC3 mPosDiff;
    math::VEC3 mVelocity;
    math::VEC3 mWorldPos;
    math::VEC3 mWorldPosDiff;
    math::VEC3 mRotation;
    math::VEC3 mAngularVelocity;
    f32 mRandomF32;
    f32 mAlpha;
    AlphaAnim* mAlphaAnim;
    math::VEC2 mScale;
    ScaleAnim* mScaleAnim;
    TexUVParam mTexAnimParam[2]; // For each texture
    f32 mFluctuationAlpha;
    f32 mFluctuationScale;
    union {
        ut::Color4f mColor[2];
        struct {
            ut::Color4f mColor0;
            ut::Color4f mColor1;
        };
    };
    PtclAttributeBuffer* mPtclAttributeBuffer;
    math::MTX34 mMatrixRT;
    math::MTX34 mMatrixSRT;
    math::MTX34* mpMatrixRT;
    math::MTX34* mpMatrixSRT;
    u32 mUnused;
    const SimpleEmitterData* mData;
    PtclInstance* mPrev;
    PtclInstance* mNext;
    EmitterInstance* mEmitter;
    PtclStripe* mStripe;
    PtclType mType;
    u32 mRandomU32;
    f32 mChildEmitCounter;
    f32 mChildPreCalcCounter;
    f32 mChildEmitLostTime;
    u8 mUnusedPad[0x180 - 0x16C];
};

static_assert(sizeof(PtclInstance) == 0x180, "PtclInstance size mismatch");

struct PtclStripeSliceHistory { // Size: 0x58
    math::VEC3 mPos;
    f32 mScale;
    math::MTX34 mEmitterMatrixSRT;
    math::VEC3 mOuter;
    math::VEC3 mDir;
};

static_assert(sizeof(PtclStripeSliceHistory) == 0x58, "PtclStripSliceHistory size mismatch");

struct ComplexEmitterData;

struct PtclStripe { // Size: 0x5880
    PtclInstance* mParticle;
    u32 mQueueFront;
    u32 mQueueRear;
    PtclStripeSliceHistory mQueue[256];
    u32 mQueueCount;
    u32 mGroupID;
    const ComplexEmitterData* mData;
    s32 mCounter;
    math::MTX34 mEmitterMatrixSRT;
    math::VEC3 mCurrentSliceDir;
    math::VEC3 mPos0;
    math::VEC3 mPos1;
    PtclStripe* mPrev;
    PtclStripe* mNext;
    u32 mDrawFirstVertex;
    u32 mNumDraw;
};

static_assert(sizeof(PtclStripe) == 0x5880, "PtclStripe size mismatch");

} }

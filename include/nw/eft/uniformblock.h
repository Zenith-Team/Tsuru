#pragma once

#include <nw/math/vec4.h>
#include <nw/math/mtx44.h>

namespace nw { namespace eft{

struct EmitterStaticUniformBlock { // Size: 0x100
    math::VEC4 mUVScaleInit;
    math::VEC4 mRotBasis;
    math::VEC4 mShaderParam;
    math::VEC4 mPad[0x10-3]; // Pad the block to 256 bytes for hardware needs
};

static_assert(sizeof(EmitterStaticUniformBlock) == 0x100, "EmitterStaticUniformBlock size mismatch");

struct EmitterDynamicUniformBlock { // Size: 0x20
    math::VEC4 mEmitterColor0;
    math::VEC4 mEmitterColor1;
};

static_assert(sizeof(EmitterDynamicUniformBlock) == 0x20, "EmitterDynamicUniformBlock size mismatch");

struct ViewUniformBlock { // Size: 0x110
    math::MTX44 mViewMat;
    math::MTX44 mVPMat;
    math::MTX44 mBldMat;
    math::VEC4 mEyeVec;
    math::VEC4 mEyePos;
    math::VEC4 mDepthBufferTexMat;
    math::VEC4 mFrameBufferTexMat;
    math::VEC4 mViewParam;
};

static_assert(sizeof(ViewUniformBlock) == 0x110, "ViewUniformBlock size mismatch");

struct PtclAttributeBuffer { // Size: 0xB0
    math::VEC4 mWldPos;
    math::VEC4 mScl;
    math::VEC4 mColor0;
    math::VEC4 mColor1;
    math::VEC4 mTexAnim;
    math::VEC4 mWldPosDf;
    math::VEC4 mRot;
    math::VEC4 mSubTexAnim;
    math::MTX34 mEmtMat;
};

static_assert(sizeof(PtclAttributeBuffer) == 0xB0, "PtclAttributeBuffer size mismatch");

struct StripeUniformBlock { // Size: 0xA0
    math::VEC4 mStParam;
    math::VEC4 mUVScrollAnim;
    math::VEC4 mUVScaleRotateAnim0;
    math::VEC4 mUVScaleRotateAnim1;
    math::VEC4 mVtxColor0;
    math::VEC4 mVtxColor1;
    math::MTX44 mEmitterMat;
};

static_assert(sizeof(StripeUniformBlock) == 0xA0, "StripeUniformBlock size mismatch");

struct StripeVertexBuffer { // Size: 0x40
    math::VEC4 mPos;
    math::VEC4 mOuter;
    math::VEC4 mTexCoord;
    math::VEC4 mDir;
};

static_assert(sizeof(StripeVertexBuffer) == 0x40, "StripeVertexBuffer size mismatch");

} }

#pragma once

#include "nw/math/vec4.h"
#include "nw/math/mtx44.h"

namespace nw { namespace eft{

struct EmitterStaticUniformBlock { // Size: 0x100
    math::VEC4 UVScaleInit;
    math::VEC4 rotBasis;
    math::VEC4 shaderParam;
    math::VEC4 pad[0xD]; // Pad the block to 256 bytes for hardware needs
};

static_assert(sizeof(EmitterStaticUniformBlock) == 0x100, "nw::eft::EmitterStaticUniformBlock size mismatch");

struct EmitterDynamicUniformBlock { // Size: 0x20
    math::VEC4 emitterColor0;
    math::VEC4 emitterColor1;
};

static_assert(sizeof(EmitterDynamicUniformBlock) == 0x20, "nw::eft::EmitterDynamicUniformBlock size mismatch");

struct ViewUniformBlock { // Size: 0x110
    math::MTX44 viewMat;
    math::MTX44 VPMat;
    math::MTX44 bldMat;
    math::VEC4 eyeVec;
    math::VEC4 eyePos;
    math::VEC4 depthBufferTexMat;
    math::VEC4 frameBufferTexMat;
    math::VEC4 viewParam;
};

static_assert(sizeof(ViewUniformBlock) == 0x110, "nw::eft::ViewUniformBlock size mismatch");

struct PtclAttributeBuffer { // Size: 0xB0
    math::VEC4 wldPos;
    math::VEC4 scl;
    math::VEC4 color0;
    math::VEC4 color1;
    math::VEC4 texAnim;
    math::VEC4 wldPosDf;
    math::VEC4 rot;
    math::VEC4 subTexAnim;
    math::MTX34 emtMat;
};

static_assert(sizeof(PtclAttributeBuffer) == 0xB0, "nw::eft::PtclAttributeBuffer size mismatch");

struct StripeUniformBlock { // Size: 0xA0
    math::VEC4 stParam;
    math::VEC4 UVScrollAnim;
    math::VEC4 UVScaleRotateAnim0;
    math::VEC4 UVScaleRotateAnim1;
    math::VEC4 vtxColor0;
    math::VEC4 vtxColor1;
    math::MTX44 emitterMat;
};

static_assert(sizeof(StripeUniformBlock) == 0xA0, "nw::eft::StripeUniformBlock size mismatch");

struct StripeVertexBuffer { // Size: 0x40
    math::VEC4 pos;
    math::VEC4 outer;
    math::VEC4 texCoord;
    math::VEC4 dir;
};

static_assert(sizeof(StripeVertexBuffer) == 0x40, "nw::eft::StripeVertexBuffer size mismatch");

} }

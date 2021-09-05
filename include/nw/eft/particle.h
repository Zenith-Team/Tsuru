#pragma once

#include <nw/math/vec3.h>
#include <nw/math/mtx34.h>
#include <nw/ut/color4f.h>
#include <nw/eft/enum.h>

namespace nw { namespace eft {

struct AlphaAnim { // Size: 0x10
    f32 startDiff;
    f32 endDiff;
    s32 time;
    s32 time2;
};

static_assert(sizeof(AlphaAnim) == 0x10, "AlphaAnim size mismatch");

struct ScaleAnim { // Size: 0x18
    math::VEC2 startDiff;
    math::VEC2 endDiff;
    s32 time;
    s32 time2;
};

static_assert(sizeof(ScaleAnim) == 0x18, "ScaleAnim size mismatch");

struct TexUVParam { // Size: 0x1C
    f32 rotate;
    math::VEC2 offset;
    math::VEC2 scroll;
    math::VEC2 scale;
};

static_assert(sizeof(TexUVParam) == 0x1C, "TexUVParam size mismatch");

struct EmitterInstance;
struct PtclAttributeBuffer;
struct PtclStripe;
struct SimpleEmitterData;

struct PtclInstance { // Size: 0x180
    f32 counter;
    s32 lifespan;
    math::VEC3 pos;
    math::VEC3 posDiff;
    math::VEC3 velocity;
    math::VEC3 worldPos;
    math::VEC3 worldPosDiff;
    math::VEC3 rotation;
    math::VEC3 angularVelocity;
    f32 randomF32;
    f32 alpha;
    AlphaAnim* alphaAnim;
    math::VEC2 scale;
    ScaleAnim* scaleAnim;
    TexUVParam texAnimParam[2]; // For each texture
    f32 fluctuationAlpha;
    f32 fluctuationScale;
    union {
        ut::Color4f color[2];
        struct {
            ut::Color4f color0;
            ut::Color4f color1;
        };
    };
    PtclAttributeBuffer* ptclAttributeBuffer;
    math::MTX34 matrixRT;
    math::MTX34 matrixSRT;
    math::MTX34* matrixRTPtr;
    math::MTX34* matrixSRTPtr;
    u32 unused;
    const SimpleEmitterData* data;
    PtclInstance* prev;
    PtclInstance* next;
    EmitterInstance* emitter;
    PtclStripe* stripe;
    PtclType type;
    u32 randomU32;
    f32 childEmitCounter;
    f32 childPreCalcCounter;
    f32 childEmitLostTime;
    u8 unusedPad[0x180 - 0x16C];
};

static_assert(sizeof(PtclInstance) == 0x180, "PtclInstance size mismatch");

struct PtclStripeSliceHistory { // Size: 0x58
    math::VEC3 pos;
    f32 scale;
    math::MTX34 emitterMatrixSRT;
    math::VEC3 outer;
    math::VEC3 dir;
};

static_assert(sizeof(PtclStripeSliceHistory) == 0x58, "PtclStripSliceHistory size mismatch");

struct ComplexEmitterData;

struct PtclStripe { // Size: 0x5880
    PtclInstance* particle;
    u32 queueFront;
    u32 queueRear;
    PtclStripeSliceHistory queue[256];
    u32 queueCount;
    u32 groupID;
    const ComplexEmitterData* data;
    s32 counter;
    math::MTX34 emitterMatrixSRT;
    math::VEC3 currentSliceDir;
    math::VEC3 pos0;
    math::VEC3 pos1;
    PtclStripe* prev;
    PtclStripe* next;
    u32 drawFirstVertex;
    u32 numDraw;
};

static_assert(sizeof(PtclStripe) == 0x5880, "PtclStripe size mismatch");

} }

#pragma once

#include <nw/math/vec3.h>
#include <nw/math/mtx44.h>
#include <nw/eft/rendercontext.h>
#include <nw/eft/temporarybuffer.h>

namespace nw { namespace eft {

class Config;
struct EmitterInstance;
class Heap;
class ParticleShader;
class Primitive;
struct PtclAttributeBuffer;
struct PtclInstance;
struct PtclStripe;
struct StripeVertexBuffer;
class System;
struct ViewUniformBlock;

class Renderer {
public:
    struct PtclViewZ { // Size: 0xC
        PtclInstance* ptcl;
        u32 z;
        u32 idx;
    };

    static_assert(sizeof(PtclViewZ) == 0xC, "PtclViewZ size mismatch");

    static s32 ComparePtclViewZ(const void* a, const void* b);

public:
    Renderer(Heap* heap, System* system, const Config& config);
    ~Renderer();

    void BeginRender(const math::MTX44& proj, const math::MTX34& view, const math::VEC3& cameraWorldPos, f32 zNear, f32 zFar);
    bool SetupParticleShaderAndVertex(ParticleShader* shader, MeshType meshType, Primitive* primitive);
    void RequestParticle(const EmitterInstance* emitter, ParticleShader* shader, bool isChild, bool flushCache, void* argData);
    void EntryChildParticleSub(const EmitterInstance* emitter, bool flushCache, void* argData);
    void EntryParticleSub(const EmitterInstance* emitter, bool flushCache, void* argData);
    void EntryParticle(EmitterInstance* emitter, bool flushCache, void* argData);
    void EndRender();

    void SwapDoubleBuffer();
    void* AllocFromDoubleBuffer(u32 size);
    void FlushCache();

    u32 MakeStripeAttributeBlockCore(PtclStripe* stripe, StripeVertexBuffer* stripeVertexBuffer, s32 firstVertex);
    static void GetPositionOnCubic(math::VEC3* result, const math::VEC3& startPos, const math::VEC3& startVel, const math::VEC3& endPos, const math::VEC3& endVel, f32 time);
    u32 MakeStripeAttributeBlockCoreDivide(PtclStripe* stripe, StripeVertexBuffer* stripeVertexBuffer, s32 firstVertex, s32 numDivisions);
    bool MakeStripeAttributeBlock(EmitterInstance* emitter);
    bool ConnectionStripeUvScaleCalc(f32& invTexRatio, f32& texRatioSub, const EmitterInstance* emitter, s32 numParticles, f32 invRatio, s32 connectionType);
    u32 MakeConnectionStripeAttributeBlockCore(EmitterInstance* emitter, s32 numParticles, PtclInstance* ptclLast, PtclInstance* ptclBeforeLast, s32 connectionType, StripeVertexBuffer* stripeVertexBuffer, s32 firstVertex = 0);
    u32 MakeConnectionStripeAttributeBlockCoreDivide(EmitterInstance* emitter, s32 numParticles, PtclInstance* ptclLast, PtclInstance* ptclBeforeLast, s32 connectionType, StripeVertexBuffer* stripeVertexBuffer, s32 firstVertex = 0);
    StripeVertexBuffer* MakeConnectionStripeAttributeBlock(EmitterInstance* emitter, bool flushCache);
    bool SetupStripeDrawSetting(const EmitterInstance* emitter, bool flushCache, void* argData);
    void EntryConnectionStripe(EmitterInstance* emitter, bool flushCache, void* argData);
    void EntryStripe(EmitterInstance* emitter, bool flushCache, void* argData);

    void BindParticleAttributeBlock(PtclAttributeBuffer* ptclAttributeBuffer, ParticleShader* shader, u32 numInstances);

    System* system;
    Heap* heap;
    RenderContext renderContext;
    u32 primitiveMode;
    math::MTX44 view;
    math::MTX44 viewProj;
    math::MTX44 billboard;
    math::VEC3 eyeVec;
    math::VEC3 eyePos;
    VertexBuffer VBPos;
    VertexBuffer VBIndex;
    Primitive* primitive;
    ViewUniformBlock* viewUniformBlock;
    union {
        const GX2Texture* textures[2];
        struct {
            const GX2Texture* depthBufferTexture;
            const GX2Texture* frameBufferTexture;
        };
    };
    math::VEC2 depthBufferTextureOffset;
    math::VEC2 depthBufferTextureScale;
    math::VEC2 frameBufferTextureOffset;
    math::VEC2 frameBufferTextureScale;
    TemporaryBuffer doubleBuffer;
    u32 stripeNumDrawVertex;
    PtclType currentParticleType;
    ShaderType shaderType;
    u32 renderVisibilityFlags;
};

} }

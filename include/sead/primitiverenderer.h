#pragma once

#include <sead.h>
#include <types.h>
#include <math.h>
#include <util/mtx.h>
#include <dynlibs/gx2/types.h>

namespace sead {

class Heap;
class Camera;
class Projection;
class Texture;

class PrimitiveRendererBase {
public:
    virtual void prepareFromBinaryImpl(Heap* heap, const void* bin_data, u32 bin_size) = 0;
    virtual void prepareImpl(Heap* heap, const SafeString& path) = 0;
    virtual void setCameraImpl(const Camera& camera) = 0;
    virtual void setProjectionImpl(const Projection& projection) = 0;
    virtual void beginImpl() = 0;
    virtual void endImpl() = 0;
    virtual void drawQuadImpl(const Mtx34& modelMtx, const Color4f& colorL, const Color4f& colorR) = 0;
    virtual void drawQuadImpl(const Mtx34& modelMtx, const Texture& texture, const Color4f& colorL, const Color4f& colorR, const Vec2f& uv_src, const Vec2f& uv_size) = 0;
    virtual void drawBoxImpl(const Mtx34& modelMtx, const Color4f& colorL, const Color4f& colorR) = 0;
    virtual void drawCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) = 0;
    virtual void drawWireCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) = 0;
    virtual void drawLineImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) = 0;
    virtual void drawSphere4x8Impl(const Mtx34& modelMtx, const Color4f& north, const Color4f& south) = 0;
    virtual void drawSphere8x16Impl(const Mtx34& modelMtx, const Color4f& north, const Color4f& south) = 0;
    virtual void drawDisk16Impl(const Mtx34& modelMtx, const Color4f& center, const Color4f& edge) = 0;
    virtual void drawDisk32Impl(const Mtx34& modelMtx, const Color4f& center, const Color4f& edge) = 0;
    virtual void drawCircle16Impl(const Mtx34& modelMtx, const Color4f& edge) = 0;
    virtual void drawCircle32Impl(const Mtx34& modelMtx, const Color4f& edge) = 0;
    virtual void drawCylinder16Impl(const Mtx34& modelMtx, const Color4f& top, const Color4f& btm) = 0;
    virtual void drawCylinder32Impl(const Mtx34& modelMtx, const Color4f& top, const Color4f& btm) = 0;
};

class PrimitiveRenderer : public IDisposer {
    SEAD_SINGLETON_DISPOSER(PrimitiveRenderer)

public:
    class QuadArg {
    public:
        QuadArg();

        Vec3f mCenter;
        Vec2f mSize;
        Color4f mColor0;
        Color4f mColor1;
        bool mHorizontal;
    };

public:
    void setCamera(const Camera& camera);
    void setProjection(const Projection& projection);

    void begin();
    void end();

    void drawQuad(const QuadArg& arg);
    void drawCube(const Vec3f& position, f32 size, const Color4f& color);
    void drawWireCube(const Vec3f& position, f32 size, const Color4f& color);
    void drawCircle16(const Vec3f& position, f32 radius, const Color4f& color);
    void drawCircle32(const Vec3f& position, f32 radius, const Color4f& color);

    PrimitiveRendererBase* mRendererImpl;
    Mtx34 mModelMtx;
};

namespace PrimitiveRendererUtil {

class Vertex {
public:
    Vertex(const Vec3f& pos, const Vec2f& uv, const Color4f& color)
        : mPos(pos)
        , mUV(uv)
        , mColor(color)
    { }

    Vec3f mPos;
    Vec3f mUV;
    Color4f mColor;
};

}

class PrimitiveRendererCafe : public PrimitiveRendererBase {
public:
    PrimitiveRendererCafe(Heap* heap);

    void prepareFromBinaryImpl(Heap* heap, const void* binData, u32) override;
    void prepareImpl(Heap* heap, const SafeString& path) override;
    void setCameraImpl(const Camera& camera) override;
    void setProjectionImpl(const Projection& projection) override;
    void beginImpl() override;
    void endImpl() override;
    void drawQuadImpl(const Mtx34& modelMtx, const Color4f& colorL, const Color4f& colorR) override;
    void drawQuadImpl(const Mtx34& modelMtx, const Texture& texture, const Color4f& colorL, const Color4f& colorR, const Vec2f& uv_src, const Vec2f& uv_size) override;
    void drawBoxImpl(const Mtx34& modelMtx, const Color4f& colorL, const Color4f& colorR) override;
    void drawCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) override;
    void drawWireCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) override;    // restored
    void drawLineImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) override;
    void drawSphere4x8Impl(const Mtx34& modelMtx, const Color4f& north, const Color4f& south) override;
    void drawSphere8x16Impl(const Mtx34& modelMtx, const Color4f& north, const Color4f& south) override;
    void drawDisk16Impl(const Mtx34& modelMtx, const Color4f& center, const Color4f& edge) override;
    void drawDisk32Impl(const Mtx34& modelMtx, const Color4f& center, const Color4f& edge) override;
    void drawCircle16Impl(const Mtx34& modelMtx, const Color4f& edge) override;  // restored
    void drawCircle32Impl(const Mtx34& modelMtx, const Color4f& edge) override;  // restored
    void drawCylinder16Impl(const Mtx34& modelMtx, const Color4f& top, const Color4f& bottom) override;
    void drawCylinder32Impl(const Mtx34& modelMtx, const Color4f& top, const Color4f& bottom) override;
    virtual ~PrimitiveRendererCafe();

    void drawLines_(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx, u32 vtxNum, u16* idx, u32 idxNum);
    void drawTriangles_(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx, u32 vtxNum, u16* idx, u32 idxNum, const GX2Texture* tex);

    Mtx34 mCameraMtx;
    Mtx44 mProjectionMtx;
    GX2VertexShader* mVertexShader;
    GX2PixelShader* mPixelShader;
    u32 mParamWVPOffset;
    u32 mParamUserOffset;
    u32 mParamRateOffset;
    u32 mParamColor0Offset;
    u32 mParamColor1Offset;
    u32 mParamTexLocation;
    u32 mAttrVertexLocation;
    u32 mAttrTexCoord0Location;
    u32 mAttrColorRateLocation;
    GX2AttribStream mAttributes[3];
    void* mFetchShaderBufPtr;
    GX2FetchShader mFetchShader;
    GX2Sampler mDrawQuadSampler;

    // Quad, Box
    PrimitiveRendererUtil::Vertex* mQuadVertexBuf;
    u16*                           mQuadIndexBuf;
    u16*                           mBoxIndexBuf;

    // Line
    PrimitiveRendererUtil::Vertex* mLineVertexBuf;
    u16*                           mLineIndexBuf;

    // Cube
    PrimitiveRendererUtil::Vertex* mCubeVertexBuf;
    u16*                           mCubeIndexBuf;

    // WireCube
    PrimitiveRendererUtil::Vertex* mWireCubeVertexBuf;
    u16*                           mWireCubeIndexBuf;

    // SphereS
    PrimitiveRendererUtil::Vertex* mSphereSVertexBuf;
    u16*                           mSphereSIndexBuf;

    // SphereL
    PrimitiveRendererUtil::Vertex* mSphereLVertexBuf;
    u16*                           mSphereLIndexBuf;

    // DiskS, DiskL, CircleS, CircleL
    PrimitiveRendererUtil::Vertex* mDiskSVertexBuf;
    u16*                           mDiskSIndexBuf;
    PrimitiveRendererUtil::Vertex* mDiskLVertexBuf;
    u16*                           mDiskLIndexBuf;
    u16*                           mCircleSIndexBuf;
    u16*                           mCircleLIndexBuf;

    // CylinderS
    PrimitiveRendererUtil::Vertex* mCylinderSVertexBuf;
    u16*                           mCylinderSIndexBuf;

    // CylinderL
    PrimitiveRendererUtil::Vertex* mCylinderLVertexBuf;
    u16*                           mCylinderLIndexBuf;
};

}

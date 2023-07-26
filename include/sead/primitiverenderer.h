#pragma once

#include "utils/rect.h"
#include "sead/matrix.h"
#include "dynlibs/gx2/types.h"
#include "sead/color.h"
#include "sead/safestring.h"
#include "sead/idisposer.h"
#include "sead/boundbox.h"

namespace sead {

class Heap;
class Camera;
class Projection;
class Texture;

class PrimitiveRendererBase {
public:
    virtual void prepareFromBinaryImpl(Heap* heap, const void* binData, u32 binSize) = 0;
    virtual void prepareImpl(Heap* heap, const SafeString& path) = 0;
    virtual void setCameraImpl(const Camera& camera) = 0;
    virtual void setProjectionImpl(const Projection& projection) = 0;
    virtual void beginImpl() = 0;
    virtual void endImpl() = 0;
    virtual void drawQuadImpl(const Mtx34& modelMtx, const Color4f& colorL, const Color4f& colorR) = 0;
    virtual void drawQuadImpl(const Mtx34& modelMtx, const Texture& texture, const Color4f& colorL, const Color4f& colorR, const Vec2f& uvSrc, const Vec2f& uvSize) = 0;
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
static_assert(sizeof(PrimitiveRendererBase) == 0x4, "sead::PrimitiveRendererBase size mismatch");

class PrimitiveRenderer : public IDisposer {
    SEAD_SINGLETON_DISPOSER(PrimitiveRenderer);

public:
    class QuadArg {
    public:
        QuadArg()
            : center(0.0f)
            , size(1.0f, 1.0f)
            , color0(sead::colorWhite)
            , color1(sead::colorWhite)
            , horizontal(false)
        {
        }
        
        QuadArg& setCornerAndSize(const Vec3f& p, const Vec2f& size);
        QuadArg& setBoundBox(const BoundBox2f& box, f32 z)
        {
            Vec2f p;
            box.getCenter(&p);

            center.set(p.x, p.y, z);
            size.set(box.getSizeX(), box.getSizeY());
            return *this;
        }
        QuadArg& setColor(const Color4f& colorT, const Color4f& colorB);
        QuadArg& setColor(const Color4f& color) { return setColor(color, color); }

        Vec3f center;
        Vec2f size;
        Color4f color0;
        Color4f color1;
        bool horizontal;
    };
    static_assert(sizeof(QuadArg) == 0x38, "sead::PrimitiveRenderer::QuadArg size mismatch");
    
    class CubeArg
    {
    public:
        CubeArg();

        CubeArg& setCornerAndSize(const Vec3f& p, const Vec3f& size);
        CubeArg& setBoundBox(const BoundBox3f& box);

        Vec3f center;
        Vec3f size;
        Color4f color0;
        Color4f color1;
    };
    static_assert(sizeof(CubeArg) == 0x38, "sead::PrimitiveRenderer::CubeArg size mismatch");

public:
    void setCamera(const Camera& camera);
    void setProjection(const Projection& projection);
    void setModelMatrix(const Mtx34& modelToWorldMtx);

    void begin();
    void end();

    void drawQuad(const QuadArg& arg);
    void drawBox(const QuadArg& arg);
    void drawCube(const CubeArg& arg);
    void drawWireCube(const CubeArg& arg);
    void drawLine(const Vec3f& from, const Vec3f& to, const Color4f& c0, const Color4f& c1);
    void drawLine(const Vec3f& from, const Vec3f& to, const Color4f& color) { drawLine(from, to, color, color); }

    void drawCube(const Vec3f& position, f32 size, const Color4f& color);
    void drawWireCube(const Vec3f& position, f32 size, const Color4f& color);

    void drawCircle16(const Vec3f& position, f32 radius, const Color4f& color);
    void drawCircle32(const Vec3f& position, f32 radius, const Color4f& color);

    PrimitiveRendererBase* rendererImpl;
    Mtx34 modelMtx;
};
static_assert(sizeof(PrimitiveRenderer) == 0x54, "sead::PrimitiveRenderer size mismatch");

namespace PrimitiveRendererUtil {

class Vertex {
public:
    Vertex(const Vec3f& pos, const Vec2f& uv, const Color4f& color)
        : pos(pos)
        , UV(uv)
        , color(color)
    { }

    Vec3f pos;
    Vec2f UV;
    Color4f color;
};
static_assert(sizeof(Vertex) == 0x24, "sead::PrimitiveRendererUtil::Vertex size mismatch");

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
    void drawQuadImpl(const Mtx34& modelMtx, const Texture& texture, const Color4f& colorL, const Color4f& colorR, const Vec2f& uvSrc, const Vec2f& uvSize) override;
    void drawBoxImpl(const Mtx34& modelMtx, const Color4f& colorL, const Color4f& colorR) override;
    void drawCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) override;
    void drawWireCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) override; // restored
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

    Mtx34 cameraMtx;
    Mtx44 projectionMtx;
    GX2VertexShader* vertexShader;
    GX2PixelShader* pixelShader;
    u32 paramWVPOffset;
    u32 paramUserOffset;
    u32 paramRateOffset;
    u32 paramColor0Offset;
    u32 paramColor1Offset;
    u32 paramTexLocation;
    u32 attrVertexLocation;
    u32 attrTexCoord0Location;
    u32 attrColorRateLocation;
    GX2AttribStream attributes[3];
    void* fetchShaderBufPtr;
    GX2FetchShader fetchShader;
    GX2Sampler drawQuadSampler;

    // Quad, Box
    PrimitiveRendererUtil::Vertex* quadVertexBuf;
    u16*                           quadIndexBuf;
    u16*                           boxIndexBuf;

    // Line
    PrimitiveRendererUtil::Vertex* lineVertexBuf;
    u16*                           lineIndexBuf;

    // Cube
    PrimitiveRendererUtil::Vertex* cubeVertexBuf;
    u16*                           cubeIndexBuf;

    // WireCube
    PrimitiveRendererUtil::Vertex* wireCubeVertexBuf;
    u16*                           wireCubeIndexBuf;

    // SphereS
    PrimitiveRendererUtil::Vertex* sphereSVertexBuf;
    u16*                           sphereSIndexBuf;

    // SphereL
    PrimitiveRendererUtil::Vertex* sphereLVertexBuf;
    u16*                           sphereLIndexBuf;

    // DiskS, DiskL, CircleS, CircleL
    PrimitiveRendererUtil::Vertex* diskSVertexBuf;
    u16*                           diskSIndexBuf;
    PrimitiveRendererUtil::Vertex* diskLVertexBuf;
    u16*                           diskLIndexBuf;
    u16*                           circleSIndexBuf;
    u16*                           circleLIndexBuf;

    // CylinderS
    PrimitiveRendererUtil::Vertex* cylinderSVertexBuf;
    u16*                           cylinderSIndexBuf;

    // CylinderL
    PrimitiveRendererUtil::Vertex* cylinderLVertexBuf;
    u16*                           cylinderLIndexBuf;
};
static_assert(sizeof(PrimitiveRendererCafe) == 0x18C, "sead::PrimitiveRendererCafe size mismatch");

}

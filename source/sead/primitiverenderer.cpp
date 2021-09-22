#include <sead.h>
#include <utils/mtx.h>
#include <dynlibs/gx2/functions.h>

namespace sead {

void PrimitiveRenderer::drawCube(const Vec3f& position, f32 size, const Color4f& color) {
    Vec3f scale(size);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34MULT(&outMtx, &modelMtx, &mtx);

    this->rendererImpl->drawCubeImpl(outMtx, color, color);
}

void PrimitiveRenderer::drawWireCube(const Vec3f& position, f32 size, const Color4f& color) {
    Vec3f scale(size);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34MULT(&outMtx, &modelMtx, &mtx);

    this->rendererImpl->drawWireCubeImpl(outMtx, color, color);
}

void PrimitiveRenderer::drawCircle16(const Vec3f& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    Vec3f scale(diameter);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34MULT(&outMtx, &modelMtx, &mtx);

    this->rendererImpl->drawCircle16Impl(outMtx, color);
}

void PrimitiveRenderer::drawCircle32(const Vec3f& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    Vec3f scale(diameter);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34MULT(&outMtx, &modelMtx, &mtx);

    this->rendererImpl->drawCircle32Impl(outMtx, color);
}

void PrimitiveRendererCafe::drawCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) {
    drawTriangles_(modelMtx, c0, c1, cubeVertexBuf, 8, cubeIndexBuf, 36, NULL);
}

void PrimitiveRendererCafe::drawWireCubeImpl(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1) {
    drawLines_(modelMtx, c0, c1, this->wireCubeVertexBuf, 8, this->wireCubeIndexBuf, 17);
}

void PrimitiveRendererCafe::drawCircle16Impl(const Mtx34& modelMtx, const Color4f& edge) {
    drawLines_(modelMtx, edge, edge, this->diskSVertexBuf, 17, this->circleSIndexBuf, 16);
}

void PrimitiveRendererCafe::drawCircle32Impl(const Mtx34& modelMtx, const Color4f& edge) {
    drawLines_(modelMtx, edge, edge, this->diskLVertexBuf, 33, this->circleLIndexBuf, 32);
}

void PrimitiveRendererCafe::drawLines_(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx, u32 vtxNum, u16* idx, u32 idxNum) {
    GX2SetVertexUniformReg(this->paramUserOffset, 12, &modelMtx);
    GX2SetVertexUniformReg(this->paramColor0Offset, 4, &c0);
    GX2SetVertexUniformReg(this->paramColor1Offset, 4, &c1);
    GX2SetPixelUniformReg(this->paramRateOffset, 4, &Rect::sZero);
    GX2SetAttribBuffer(0, vtxNum * 0x24, 0x24, vtx);
    GX2DrawIndexedEx(GX2_PRIMITIVE_LINE_LOOP, idxNum, GX2_INDEX_FORMAT_U16, idx, 0, 1);
}

}

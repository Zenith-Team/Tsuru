#include <sead.h>
#include <util/mtx.h>
#include <dynlibs/gx2/functions.h>

namespace sead {

void PrimitiveRenderer::drawCircle16(const Vec3f& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    Vec3f scale(diameter);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34MULT(&outMtx, &mModelMtx, &mtx);

    mRendererImpl->drawCircle16Impl(outMtx, color);
}

void PrimitiveRenderer::drawCircle32(const Vec3f& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    Vec3f scale(diameter);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34MULT(&outMtx, &mModelMtx, &mtx);

    mRendererImpl->drawCircle32Impl(outMtx, color);
}

void PrimitiveRendererCafe::drawLines_(const Mtx34& modelMtx, const Color4f& c0, const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx, u32 vtxNum, u16* idx, u32 idxNum) {
    GX2SetVertexUniformReg(mParamUserOffset, 12, &modelMtx);
    GX2SetVertexUniformReg(mParamColor0Offset, 4, &c0);
    GX2SetVertexUniformReg(mParamColor1Offset, 4, &c1);
    GX2SetPixelUniformReg(mParamRateOffset, 4, &Rect::sZero);
    GX2SetAttribBuffer(0, vtxNum * 0x24, 0x24, vtx);
    GX2DrawIndexedEx(GX2_PRIMITIVE_LINE_LOOP, idxNum, GX2_INDEX_FORMAT_U16, idx, 0, 1);
}

void PrimitiveRendererCafe::drawCircle16Impl(const Mtx34& modelMtx, const Color4f& edge) {
    drawLines_(modelMtx, edge, edge, mDiskSVertexBuf, 17, mCircleSIndexBuf, 16);
}

void PrimitiveRendererCafe::drawCircle32Impl(const Mtx34& modelMtx, const Color4f& edge) {
    drawLines_(modelMtx, edge, edge, mDiskLVertexBuf, 33, mCircleLIndexBuf, 32);
}

}

#include "dynamic_libs/gx2_functions.h"
#include "util/mtx34.h"
#include "util/rect.h"
#include "util/vec3.h"
#include "sead.h"

namespace sead {

void PrimitiveRenderer::drawCircle16(const Vec3& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    Vec3 scale(diameter, diameter, diameter);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34Mult(&outMtx, &mModelMtx, &mtx);

    mRendererImpl->drawCircle16Impl(outMtx, color);
}

void PrimitiveRenderer::drawCircle32(const Vec3& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    Vec3 scale(diameter, diameter, diameter);

    Mtx34 mtx;
    Mtx34::makeST(mtx, scale, position);

    Mtx34 outMtx;
    (void)MTX34Mult(&outMtx, &mModelMtx, &mtx);

    mRendererImpl->drawCircle32Impl(outMtx, color);
}

void PrimitiveRendererCafe::drawLines_(const Mtx34& model_mtx, const Color4f& c0, const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx, u32 vtx_num, u16* idx, u32 idx_num) {
    GX2SetVertexUniformReg(mParamUserOffset, 12, &model_mtx);
    GX2SetVertexUniformReg(mParamColor0Offset, 4, &c0);
    GX2SetVertexUniformReg(mParamColor1Offset, 4, &c1);
    GX2SetPixelUniformReg(mParamRateOffset, 4, &Rect::zero);
    GX2SetAttribBuffer(0, vtx_num * 0x24, 0x24, vtx);
    GX2DrawIndexedEx(GX2_PRIMITIVE_LINE_LOOP, idx_num, GX2_INDEX_FORMAT_U16, idx, 0, 1);
}

void PrimitiveRendererCafe::drawCircle16Impl(const Mtx34& model_mtx, const Color4f& edge) {
    drawLines_(model_mtx, edge, edge, mDiskSVertexBuf, 17, mCircleSIndexBuf, 16);
}

void PrimitiveRendererCafe::drawCircle32Impl(const Mtx34& model_mtx, const Color4f& edge) {
    drawLines_(model_mtx, edge, edge, mDiskLVertexBuf, 33, mCircleLIndexBuf, 32);
}

}

#include "gfx/seadPrimitiveRenderer.h"
#include "gfx/cafe/seadPrimitiveRendererCafe.h"
#include "sdk/mtxvec/functions.h"
#include "sdk/gx2/functions.h"
#include "math/seadQuat.h"

static sead::Matrix34f* ASM_MTXMultiply(sead::Matrix34f* out, sead::Matrix34f* p1, sead::Matrix34f* p2) {
    ASM_MTXConcat(p1->m, p2->m, out->m);
    return out;
}

namespace sead {

void PrimitiveRenderer::drawQuad(const Color4f& colorL, const Color4f& colorR) {
    mRendererImpl->drawQuadImpl(mModelMtx, colorL, colorR);
}

void PrimitiveRenderer::drawCube(const Color4f& c0, const Color4f& c1) {
    mRendererImpl->drawCubeImpl(mModelMtx, c0, c1);
}

PrimitiveRenderer::QuadArg& PrimitiveRenderer::QuadArg::setBoundBox(const BoundBox2f& box, f32 z) {
    Vector2f p;
    box.getCenter(&p);

    mCenter.set(p.x, p.y, z);
    mSize.set(box.getSizeX(), box.getSizeY());
    return *this;
}

void PrimitiveRenderer::drawBox(const QuadArg& arg) {
    sead::Matrix34f mtx;

    if (arg.isHorizontal()) {
        const sead::Vector2f& size = arg.getSize();
        sead::Vector3f scale(size.x, size.y, 1.0f); // No flipping of x and y. Bug?
        sead::Vector3f rotation(0.0f, 0.0f, sead::Mathf::deg2rad(90));

        mtx.makeSRT(scale, rotation, arg.getCenter());
    } else {
        const sead::Vector2f& size = arg.getSize();
        sead::Vector3f scale(size.x, size.y, 1.0f);

        mtx.makeST(scale, arg.getCenter());
    }

    sead::Matrix34f outMtx;
    ASM_MTXMultiply(&outMtx, &mModelMtx, &mtx);

    mRendererImpl->drawBoxImpl(outMtx, arg.getColor0(), arg.getColor1());
}

void PrimitiveRenderer::drawCube(const CubeArg& arg) {
    sead::Matrix34f mtx;
    mtx.makeST(arg.getSize(), arg.getCenter());

    sead::Matrix34f outMtx;
    ASM_MTXMultiply(&outMtx, &mModelMtx, &mtx);

    mRendererImpl->drawCubeImpl(outMtx, arg.getColor0(), arg.getColor1());
}

void PrimitiveRenderer::drawWireCube(const CubeArg& arg) {
    sead::Matrix34f mtx;
    mtx.makeST(arg.getSize(), arg.getCenter());

    sead::Matrix34f outMtx;
    ASM_MTXMultiply(&outMtx, &mModelMtx, &mtx);
    mRendererImpl->drawWireCubeImpl(outMtx, arg.getColor0(), arg.getColor1());
}

void PrimitiveRenderer::drawLine(const sead::Vector3f& from, const sead::Vector3f& to, const Color4f& c0, const Color4f& c1) {
    sead::Vector3f dir = to - from;

    sead::Matrix34f mtxS;
    mtxS.makeS(dir.length(), 1.0f, 1.0f);

    dir.normalize();

    Quatf q;
    q.makeVectorRotation(sead::Vector3f(1.0f, 0.0f, 0.0f), dir);

    sead::Matrix34f mtxR;
    mtxR.fromQuat(q);

    sead::Matrix34f mtx;
    ASM_MTXMultiply(&mtx, &mtxR, &mtxS);

    dir = to - from;
    dir.multScalar(0.5f);
    dir += from;
    mtx.setTranslation(dir);

    sead::Matrix34f outMtx;
    ASM_MTXMultiply(&outMtx, &mModelMtx, &mtx);

    mRendererImpl->drawLineImpl(outMtx, c0, c1);
}

void PrimitiveRenderer::drawCircle16(const sead::Vector3f& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    sead::Vector3f scale(diameter, diameter, diameter);

    sead::Matrix34f mtx;
    mtx.makeST(scale, position);

    sead::Matrix34f outMtx;
    ASM_MTXMultiply(&outMtx, &mModelMtx, &mtx);

    this->mRendererImpl->drawCircle16Impl(outMtx, color);
}

void PrimitiveRenderer::drawCircle32(const sead::Vector3f& position, f32 radius, const Color4f& color) {
    f32 diameter = radius + radius;
    sead::Vector3f scale(diameter, diameter, diameter);

    sead::Matrix34f mtx;
    mtx.makeST(scale, position);

    sead::Matrix34f outMtx;
    ASM_MTXMultiply(&outMtx, &mModelMtx, &mtx);

    this->mRendererImpl->drawCircle32Impl(outMtx, color);
}

void PrimitiveRendererCafe::drawBoxImpl(const sead::Matrix34f& modelMtx, const Color4f& colorL, const Color4f& colorR) {
    this->drawLines_(modelMtx, colorL, colorR, mQuadVertexBuf, 4, mBoxIndexBuf, 4);
}

void PrimitiveRendererCafe::drawCubeImpl(const sead::Matrix34f& modelMtx, const Color4f& c0, const Color4f& c1) {
    this->drawTriangles_(modelMtx, c0, c1, mCubeVertexBuf, 8, mCubeIndexBuf, 36, nullptr);
}

void PrimitiveRendererCafe::drawWireCubeImpl(const sead::Matrix34f& modelMtx, const Color4f& c0, const Color4f& c1) {
    this->drawLines_(modelMtx, c0, c1, mWireCubeVertexBuf, 8, mWireCubeIndexBuf, 17);
}

void PrimitiveRendererCafe::drawLineImpl(const sead::Matrix34f& modelMtx, const Color4f& c0, const Color4f& c1) {
    this->drawLines_(modelMtx, c0, c1, mLineVertexBuf, 2, mLineIndexBuf, 2);
}

void PrimitiveRendererCafe::drawCircle16Impl(const sead::Matrix34f& modelMtx, const Color4f& edge) {
    this->drawLines_(modelMtx, edge, edge, mDiskSVertexBuf, 17, mCircleSIndexBuf, 16);
}

void PrimitiveRendererCafe::drawCircle32Impl(const sead::Matrix34f& modelMtx, const Color4f& edge) {
    this->drawLines_(modelMtx, edge, edge, mDiskLVertexBuf, 33, mCircleLIndexBuf, 32);
}

void PrimitiveRendererCafe::drawLines_(const sead::Matrix34f& modelMtx, const Color4f& c0, const Color4f& c1, PrimitiveRendererUtil::Vertex* vtx, u32 vtxNum, u16* idx, u32 idxNum) {
    GX2SetVertexUniformReg(mParamUserOffset, 12, &modelMtx);
    GX2SetVertexUniformReg(mParamColor0Offset, 4, &c0);
    GX2SetVertexUniformReg(mParamColor1Offset, 4, &c1);
    GX2SetPixelUniformReg(mParamRateOffset, 4, &sead::Vector4f::zero);
    GX2SetAttribBuffer(0, vtxNum * sizeof(PrimitiveRendererUtil::Vertex), sizeof(PrimitiveRendererUtil::Vertex), vtx);
    GX2DrawIndexedEx(GX2_PRIMITIVE_LINE_LOOP, idxNum, GX2_INDEX_FORMAT_U16, idx, 0, 1);
}

}

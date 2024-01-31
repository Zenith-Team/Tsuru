#pragma once

#include "prim/seadRuntimeTypeInfo.h"
#include "math/seadMatrix.h"

class RenderObjBase {
    SEAD_RTTI_BASE_DECL(RenderObjBase);

public:
    RenderObjBase() { }

    virtual void calc() = 0;
};

class RenderMgr;

class RenderObj : public RenderObjBase {
    SEAD_RTTI_OVERRIDE_DECL(RenderObj, RenderObjBase);

public:
    RenderObj()
        : RenderObjBase()
    { }

    virtual void calcGPU(s32 viewIndex, const sead::Matrix34f& viewMtx, const sead::Matrix44f& projMtx, RenderMgr* renderMgr) = 0;
    virtual void updateView(s32 viewIndex, const sead::Matrix34f& viewMtx, const sead::Matrix44f& projMtx, RenderMgr* renderMgr) = 0;
    virtual void drawOpa(s32 viewIndex, const sead::Matrix34f& viewMtx, const sead::Matrix44f& projMtx, RenderMgr* renderMgr) = 0;
    virtual void drawXlu(s32 viewIndex, const sead::Matrix34f& viewMtx, const sead::Matrix44f& projMtx, RenderMgr* renderMgr) = 0;
    virtual void drawShadowOpa(s32 viewIndex, const sead::Matrix34f& viewMtx, const sead::Matrix44f& projMtx, RenderMgr* renderMgr) { }
    virtual void drawReflectionOpa(s32 viewIndex, const sead::Matrix34f& viewMtx, const sead::Matrix44f& projMtx, RenderMgr* renderMgr) { }
    virtual void drawReflectionXlu(s32 viewIndex, const sead::Matrix34f& viewMtx, const sead::Matrix44f& projMtx, RenderMgr* renderMgr) { }
    virtual bool hasShadow() const { return false; }

    sead::Vector3f orderPos;
};

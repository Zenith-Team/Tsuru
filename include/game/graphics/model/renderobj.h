#pragma once

#include "sead/runtimetypeinfo.h"
#include "sead/matrix.h"

class RenderObjBase {
    SEAD_RTTI_BASE(RenderObjBase);

public:
    RenderObjBase() { }

    virtual void calc() = 0;
};

class RenderMgr;

class RenderObj : public RenderObjBase {
    SEAD_RTTI_OVERRIDE(RenderObj, RenderObjBase);

public:
    RenderObj()
        : RenderObjBase()
    { }

    virtual void calcGPU(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) = 0;
    virtual void updateView(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) = 0;
    virtual void drawOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) = 0;
    virtual void drawXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) = 0;
    virtual void drawShadowOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) { }
    virtual void drawReflectionOpa(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) { }
    virtual void drawReflectionXlu(s32 viewIndex, const Mtx34& viewMtx, const Mtx44& projMtx, RenderMgr* renderMgr) { }
    virtual bool hasShadow() const { return false; }

    Vec3f orderPos;
};

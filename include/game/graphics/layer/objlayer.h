#pragma once

#include "math/seadMatrix.h"
#include "game/graphics/layer/layeragl.h"

class RenderMgr;

class ObjLayer : public LayerAgl {
    SEAD_RTTI_OVERRIDE_DECL(ObjLayer, LayerAgl);

public:
    ObjLayer();
    virtual ~ObjLayer();

    void doInitialize(sead::Heap* heap) override;
    void vf3C() override;

    u32 vf54() override;
    u32 vf5C() override;

    // Calls GX2SetPolygonOffset()
    virtual void vf64(s32);

    void setParentRenderer(RenderMgr* renderMgr);

    RenderMgr* renderMgr;
    s32 viewIndex;
    sead::Matrix44f* _428;
};

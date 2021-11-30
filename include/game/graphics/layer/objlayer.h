#pragma once

#include <utils/mtx.h>
#include <game/graphics/layer/layeragl.h>
#include "game/graphics/layer/objlayerrenderer.h"

class ObjLayerRenderer;

class ObjLayer : public LayerAgl {
    SEAD_RTTI_OVERRIDE(ObjLayer, LayerAgl)

public:
    class Node : public LayerAgl::Node {
        SEAD_RTTI_OVERRIDE(Node, LayerAgl::Node)

    public:
        virtual void CalcView(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void vf2C(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawAllShapes1(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawAllShapes2(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawShadowCastShapes(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionShapes1(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionShapes2(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) { }
        virtual bool hasShadowCastShapes() const { return false; }
    };

public:
    ObjLayer();
    virtual ~ObjLayer();

    void doInitialize(sead::Heap* heap) override;
    void vf3C() override;

    bool vf54(u32) override;
    u32 vf5C() override;

    // Calls GX2SetPolygonOffset()
    virtual void vf64(u32);

    void setParentRenderer(ObjLayerRenderer* renderer);

    u32 _420;
    s32 _424;
    Mtx44* _428;
};

#pragma once

#include "sead/matrix.h"
#include "game/graphics/layer/layeragl.h"
#include "game/graphics/layer/objlayerrenderer.h"

class ObjLayerRenderer;

class ObjLayer : public LayerAgl {
    SEAD_RTTI_OVERRIDE(ObjLayer, LayerAgl)

public:
    class Node : public LayerAgl::Node {
        SEAD_RTTI_OVERRIDE(Node, LayerAgl::Node)

    public:
        virtual void calcGPU(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void calcView(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawOpa(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawXlu(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawShadowOpa(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionOpa(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionXlu(s32 viewIndex, const Mtx34& cameraMtx, const Mtx44& deviceProjectionMtx, ObjLayerRenderer* renderer) { }
        virtual bool hasShadow() const { return false; }
    };

public:
    ObjLayer();
    virtual ~ObjLayer();

    void doInitialize(sead::Heap* heap) override;
    void vf3C() override;

    u32 vf54() override;
    u32 vf5C() override;

    // Calls GX2SetPolygonOffset()
    virtual void vf64(s32);

    void setParentRenderer(ObjLayerRenderer* renderer);

    u32 _420;
    s32 _424;
    Mtx44* _428;
};

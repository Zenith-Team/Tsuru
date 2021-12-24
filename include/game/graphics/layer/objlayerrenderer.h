#pragma once

#include "sead/idisposer.h"
#include "sead/safestring.h"
#include "sead/list.h"
#include "sead/ptrarray.h"
#include "sead/buffer.h"
#include "agl/texturesampler.h"
#include "game/graphics/layer/objlayer.h"
#include "game/graphics/layer/objlayerbuffer.h"

class ObjLayerRenderer : public sead::IDisposer { // Size: 0x4D4
public:
    ObjLayerRenderer(const sead::SafeString& name);
    virtual ~ObjLayerRenderer();

    void init(u32 layersCount, u32 nodePtrCount, u32 nodeOpaBufferSize, u32 nodeXluBufferSize, sead::Heap* heap);

    sead::SafeString name;
    u8 _18;
    sead::PtrArray<LayerAgl::Node> nodes;
    sead::Buffer<sead::PtrArray<LayerAgl::Node> > nodeOpaBuffer;
    sead::Buffer<sead::PtrArray<LayerAgl::Node> > nodeXluBuffer;
    sead::PtrArray<LayerAgl::Node> nodesWithShadowCastShapes;
    u8 envObjMgr[1124]; // Is class
    sead::PtrArray<LayerAgl::Node> _4A8;
    void* _4B4;
    u8 _4B8;
    agl::TextureSampler* shadowMapSampler;
    agl::TextureSampler* reflectionMapSampler;
    sead::Buffer<ObjLayerBuffer> layerBuffer;
    sead::ListNode layerMgrNode;
};

static_assert(sizeof(ObjLayerRenderer) == 0x4D4, "ObjLayerRenderer size mismatch");

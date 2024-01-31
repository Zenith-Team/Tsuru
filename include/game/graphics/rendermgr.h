#pragma once

#include "heap/seadDisposer.h"
#include "prim/seadSafeString.h"
#include "container/seadListImpl.h"
#include "container/seadPtrArray.h"
#include "container/seadBuffer.h"
#include "common/aglTextureSampler.h"
#include "game/graphics/model/modelenvview.h"

class RenderObjBaseLayer;
class RenderObj;
class CullViewFrustum;

class RenderMgr : public sead::IDisposer, sead::INamable { // Size: 0x4D4
public:
    struct ViewInfo {
        RenderObjBaseLayer* layer;
        sead::Matrix34f viewMtx;
        sead::Matrix44f projMtx;
        sead::Matrix44f* _74;
        CullViewFrustum* cull;
        void* _7C;
    };

    static_assert(sizeof(ViewInfo) == 0x80, "RenderMgr::ViewInfo size mismatch");

public:
    RenderMgr(const sead::SafeString& name);
    virtual ~RenderMgr();

    void init(u32 layersCount, u32 nodePtrCount, u32 nodeOpaBufferSize, u32 nodeXluBufferSize, sead::Heap* heap);

    u8 _18;
    sead::PtrArray<RenderObj> renderObjects;
    sead::Buffer<sead::PtrArray<RenderObj> > renderObjectsOpa;
    sead::Buffer<sead::PtrArray<RenderObj> > renderObjectsXlu;
    sead::PtrArray<RenderObj> renderObjectsShadow;
    u8 envObjMgr[1124]; // Is class
    ModelEnvView modelEnvView;
    void* _4B4;
    bool drawShadow;
    agl::TextureSampler* shadowMapSampler;
    agl::TextureSampler* reflectionMapSampler;
    sead::Buffer<ViewInfo> viewInfos;
    sead::ListNode layerMgrNode;
};

static_assert(sizeof(RenderMgr) == 0x4D4, "ObjLayerRenderer size mismatch");

#pragma once

#include <sead.h>
#include "agl/lyr/displaytype.h"
#include "agl/renderbuffer.h"
#include "sead/controller.h"

namespace agl { namespace lyr {

class Layer;

class Renderer { // Size: 0xF78
    SEAD_SINGLETON_DISPOSER(Renderer)

public:
    Renderer();
    virtual ~Renderer();

    // Creates and initializes a layer + binds it to the renderer
    // @param layerID Target ID of the created layer
    // @param layerName Name of the created layer
    // @param displayType Display type of the layer
    // @param heap Heap to allocate to
    // @return Pointer to the created layer
    template <class T>
    T* createLayer(u32 layerID, const sead::SafeString& layerName, DisplayType displayType, sead::Heap* heap) {
        T* layer = new T();

        this->initLayer_(layer, layerID, layerName, displayType, heap);

        return layer;
    }

    void initLayer_(Layer* layer, u32 layerID, const sead::SafeString& layerName, u32 displayType, sead::Heap* heap);

    bool draw(DisplayType displayType) const;
    
    // Custom functions
    bool drawCustomTV(DisplayType displayType) const;
    bool drawCustomDRC(DisplayType displayType) const;

    u32 isDisplayList;
    u32 multiSampleType; // agl::MultiSampleType
    u8 renderDisplays[DisplayType_Num][0x6C4]; // agl::lyr::RenderDisplay[DisplayType_Num]
    RenderBuffer* renderBuffers[DisplayType_Num];
    sead::Buffer<agl::lyr::Layer*> layers;
    mutable sead::BitFlag16 flags;
    f32 _DB4;
    u8 _DB8[16];
    sead::CriticalSection cs;
    u8 jobQueues[2][0x64]; // sead::FixedSizeJQ[2]
    sead::PtrArrayImpl renderDisplayJobs[DisplayType_Num]; // sead::PtrArray<agl::lyr::RenderDisplay::Job>[DisplayType_Num]
    u32 _EE4;
    u32 _EE8;
    s32 _EEC;
    sead::Controller* debugController; // sead::Controller*
    f32 _EF4;
    sead::Vec2f _EF8;
    u32 _F00;
    u8 renderDLBuffer[0x58]; // agl::lyr::RenderDLBuffer
    u32 gpuCounter;
    u32 gpuCounterPeriod;
    u32 _F64;
    s32 colorBufferSwizzle;
    s32 depthBufferSwizzle;
    f32 _F70;
};

static_assert(sizeof(Renderer) == 0xF78, "agl::lyr::Renderer size mismatch");

} }

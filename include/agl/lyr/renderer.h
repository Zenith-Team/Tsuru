#pragma once

#include <sead.h>

namespace agl { namespace lyr {

class Layer;

class Renderer { // Size: 0xF78
    SEAD_SINGLETON_DISPOSER(Renderer)

public:
    Renderer();
    virtual ~Renderer();

    template <class T>
    T* createLayer(u32 layerID, const sead::SafeString& layerName, u32 displayType, sead::Heap* heap) {
        T* layer = new T();

        this->initLayer_(layer, layerID, layerName, displayType, heap);
        
        return layer;
    }

    void initLayer_(Layer* layer, u32 layerID, const sead::SafeString& layerName, u32 displayType, sead::Heap* heap);

    u32 _10;
    u32 _14;
    u8 _18[0x6C4][2];           // Array of two CLASS_2a618c0
    u8 _DA0[0x8];               // Unknown values
    sead::Buffer<Layer*> layers;
    u16 _DB0;
    u8 _DB2[0x2];               // Unknown values
    f32 _DB4;
    u8 _DB8[0x10];              // Unknown values
    sead::CriticalSection _DC8;
    u8 _E04[0x64][2];           // Array of two CLASS_2affb68
    u8 _ECC[0xC][2];            // Array of two CLASS_2a3b27c
    u32 _EE4;
    u32 _EE8;
    u32 _EEC;
    u32 _EF0;
    f32 _EF4;
    Vec2f _EF8;
    u32 _F00;
    u8 _F04[0x58];              // CLASS_2a638c0
    u32 _F5C;
    u32 _F60;
    u32 _F64;
    u32 _F68;
    u32 _F6C;
    f32 _F70;
};

static_assert(sizeof(Renderer) == 0xF78, "agl::lyr::Renderer size mismatch");

} }

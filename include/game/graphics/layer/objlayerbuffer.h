#pragma once

#include "types.h"

class ObjLayer;

class ObjLayerBuffer { // Size: 0x80
public:
    ObjLayer* layer;
    Mtx34 cameraMtx;
    Mtx44 deviceProjectionMtx;
    Mtx44* _74;
    u32 _78;
    u32 _7C;    
};

static_assert(sizeof(ObjLayerBuffer) == 0x80, "ObjLayerBuffer size mismatch");

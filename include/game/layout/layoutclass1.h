#pragma once

#include "sead/idisposer.h"
#include "sead/buffer.h"
#include "sead/safestring.h"
#include "utils/mtx.h"
#include "game/layout/gamelayout.h"

// TODO: RE this more
class CoLayout { public: CoLayout(); u32 _0; sead::SafeString _4; u32 _C; u8 _10; };

class LayoutClass1 : public sead::IDisposer { // Size: 0xE88
public:
    LayoutClass1(CoLayout*, s32);
    virtual ~LayoutClass1();

    void init(sead::Heap* heap = nullptr);
    void draw(const Mtx44& projectionMtx);
    void update(u32 layerID, u32 = 0);

    GameLayout* layout;
    void* heap; // some sead/nw bridge class probably
    u32 _18;
    nw::lyt::DrawInfo drawInfo;
    u8 _E4[3476]; // inlined class
    sead::Buffer<CoLayout> _E78;
    class { virtual void spawnVtable() { } } _E80; // wesley says its font related
    f32 _E84;
};

static_assert(sizeof(LayoutClass1) == 0xE88, "LayoutClass1 size mismatch");

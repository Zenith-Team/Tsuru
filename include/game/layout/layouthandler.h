#pragma once

#include "sead/idisposer.h"
#include "sead/buffer.h"
#include "sead/safestring.h"
#include "sead/matrix.h"
#include "game/layout/gamelayout.h"

class LayoutAnimator {
public:
    LayoutAnimator();

    u32 _0;
    sead::SafeString _4;
    u32 _C;
    u8 _10;
};

class LayoutHandler : public sead::IDisposer { // Size: 0xE88
public:
    LayoutHandler(LayoutAnimator*, s32);
    virtual ~LayoutHandler();

    void init(sead::Heap* heap = nullptr);
    void draw(const Mtx44& projectionMtx);
    void update(u32 layerID, Mtx34* mtx = nullptr);
    void initAnims(const sead::SafeString* names, u32& count);
    void playAnim(u32, const sead::SafeString& name, bool loop = false);

    GameLayout* layout;
    struct { void* _0; u32 _4; } allocator; // Likely a NW/Sead bridge class
    nw::lyt::DrawInfo drawInfo;
    u8 _E4[3476]; // inlined class
    sead::Buffer<LayoutAnimator> LayoutAnimators;
    class { virtual void spawnVtable() { } } _E80; // wesley says its font related
    f32 _E84;
};

static_assert(sizeof(LayoutHandler) == 0xE88, "LayoutHandler size mismatch");

#pragma once

#include "heap/seadDisposer.h"
#include "container/seadBuffer.h"
#include "prim/seadSafeString.h"
#include "math/seadMatrix.h"
#include "game/layout/gamelayout.h"
#include "game/layout/textboxwrapper.h"

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
    void draw(const sead::Matrix44f& projectionMtx);
    void update(u32 layerID, sead::Matrix34f* mtx = nullptr);
    void initAnims(const sead::SafeString* names, u32& count);
    void playAnim(u32, const sead::SafeString& name, bool loop = false);

    nw::lyt::Pane* getPane(const sead::SafeString& name) const;
    void getPanes(nw::lyt::Pane** output, sead::SafeString* names, const u32& count) const;

    nw::lyt::Pane* getRootPane() const;

    TextBoxWrapper* getTextBoxPane(const sead::SafeString& name) const;
    void getTextBoxPanes(TextBoxWrapper** output, sead::SafeString* names, const u32& count) const;

    GameLayout* layout;
    struct { void* _0; u32 _4; } allocator; // Likely a NW/Sead bridge class
    nw::lyt::DrawInfo drawInfo;
    u8 _E4[3476]; // inlined class
    sead::Buffer<LayoutAnimator> LayoutAnimators;
    class { virtual void spawnVtable() { } } _E80; // wesley says its font related
    f32 _E84;
};

static_assert(sizeof(LayoutHandler) == 0xE88, "LayoutHandler size mismatch");

#pragma once

#include "heap/seadDisposer.h"
#include "common/aglTextureData.h"
#include "common/aglRenderBuffer.h"
#include "gfx/seadCamera.h"
#include "gfx/seadProjection.h"
#include "prim/seadBitFlag.h"
#include "utility/aglDebugTexturePage.h"

class TileTexMgr {
    SEAD_SINGLETON_DISPOSER(TileTexMgr);

public:
    struct TileAnimation {
        bool playing;
        bool reverse;
        u32* frameDelays;
        u32 frameCount;
        u32 currentFrame;
        u32 delayTimer;
    };

public:
    TileTexMgr();

    void updateAnimations();
    void renderAnimation(u32, u32 tileAnimIndex, u32 textureAnimIndex, u32);

    void* _10; // Some type of vtable
    agl::TextureData tilesetImages[4];
    sead::BitFlag32 usedSlots;
    u8 _288[4]; // Unknown values
    agl::TextureData normalMaps[4];
    agl::RenderTargetColor textureRenderTarget;
    agl::RenderBuffer textureRenderBuffer;
    agl::RenderTargetColor normalMapRenderTarget;
    agl::RenderBuffer normalMapRenderBuffer;
    sead::OrthoProjection projection;
    sead::OrthoCamera camera;
    agl::TextureData textureAnimations[6];
    TileAnimation tileAnimations[9];
    u32 hasPa0Tileset;
    agl::utl::DebugTexturePage debugTexturePage;
    u8 _F84;
};

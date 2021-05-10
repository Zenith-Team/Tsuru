#pragma once

#include "dynamic_libs/gx2_types.h"
#include "agl/texture/texturedata.h"

namespace agl { class RenderTargetDepth {
public:
    RenderTargetDepth();

    void invalidateGPUCache();
    void applyTextureData(agl::TextureData*);

    TextureData textureData;
	u8 _9C;
	u32 _A0;
	u32 _A4;
	u32 _A8;
	u32 _AC;
	u32 _B0;
	GX2DepthBuffer depthBuffer;
};

}

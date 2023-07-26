#pragma once

#include "dynlibs/gx2/types.h"

namespace agl {

enum TextureType { };
enum TextureFormat { };
enum TextureCompSel { };
enum MultiSampleType { };

class TextureData { // Size: 0x9C
public:
    TextureData();
    virtual ~TextureData(); // deleted

    u32 getWidth(s32 mipLevel = 0) const { return sead::Mathi::max(surface.width >> mipLevel, minWidth); }
    u32 getHeight(s32 mipLevel = 0) const { return sead::Mathi::max(surface.height >> mipLevel, minHeight); }

    void* getImagePtr() const { return surface.imageData; }
    void setImagePtr(void* ptr) { surface.imageData = ptr; }

    u32 getImageByteSize() const { return surface.imageSize; }

    void* getMipPtr() const { return surface.mipData; }
    void setMipPtr(void* ptr) { surface.mipData = ptr; }

    u32 getMipByteSize() const { return surface.mipSize; }

    u32 getAlignment() const { return surface.align; }

    void initializeFromSurface(const GX2Surface& surface);
    void invalidateGPUCache();

    u32 getMipLevelNum() const { return surface.numMips; }
    void setMipLevelNum(u32 mipLevelNum);

private:
    void initialize_(TextureType textureType, TextureFormat textureFormat, u32 width, u32 height, u32 sliceNum, bool mipLevelNum, MultiSampleType multiSampleType);
    void initializeSize_(u32 width, u32 height, u32 sliceNum);

public:
    TextureFormat format;
    GX2Surface surface;
    u32 minWidth;
    u32 minHeight;
    u32 minSlice;
    u32 maxMipLevel;
    TextureCompSel compR;
    TextureCompSel compG;
    TextureCompSel compB;
    TextureCompSel compA;
};

static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}

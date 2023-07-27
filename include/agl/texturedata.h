#pragma once

#include "dynlibs/gx2/types.h"
#include "sead/mathcalccommon.h"

namespace agl {

enum TextureType { };
enum TextureFormat { };
enum TextureCompSel { };
enum MultiSampleType { };

class TextureData { // Size: 0x9C
public:
    TextureData();
    virtual ~TextureData(); // deleted

    u32 getWidth(s32 mipLevel = 0) const { return sead::Mathi::max(this->surface.width >> mipLevel, this->minWidth); }
    u32 getHeight(s32 mipLevel = 0) const { return sead::Mathi::max(this->surface.height >> mipLevel, this->minHeight); }

    void* getImagePtr() const { return this->surface.imageData; }
    void setImagePtr(void* ptr) { this->surface.imageData = ptr; }

    u32 getImageByteSize() const { return this->surface.imageSize; }

    void* getMipPtr() const { return this->surface.mipData; }
    void setMipPtr(void* ptr) { this->surface.mipData = ptr; }

    u32 getMipByteSize() const { return this->surface.mipSize; }

    u32 getAlignment() const { return this->surface.align; }

    void initializeFromSurface(const GX2Surface& surface);
    void invalidateGPUCache();

    u32 getMipLevelNum() const { return this->surface.numMips; }
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

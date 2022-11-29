#pragma once

#include "sead/runtimetypeinfo.h"
#include "dynlibs/gx2/types.h"

namespace sead {

class Texture {
    SEAD_RTTI_BASE(Texture);

public:
    Texture() { }
    virtual ~Texture() { }

    virtual u32 getWidth() const = 0;
    virtual u32 getHeight() const = 0;
};

class TextureCafeGX2 : public Texture {
    SEAD_RTTI_OVERRIDE(TextureCafeGX2, Texture);

public:
    TextureCafeGX2()
        : Texture()
        , gx2Texture(nullptr)
    { }

    virtual ~TextureCafeGX2() { }

    virtual u32 getWidth() const override;
    virtual u32 getHeight() const override;

    GX2Texture* gx2Texture;
};

}

static_assert(sizeof(sead::Texture) == 0x4, "sead::Texture size mismatch");
static_assert(sizeof(sead::TextureCafeGX2) == 0x8, "sead::TextureCafeGX2 size mismatch");

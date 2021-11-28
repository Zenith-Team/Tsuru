#pragma once

#include "sead/idisposer.h"
#include "sead/ptrarray.h"
#include "agl/shaderprogramarchive.h"

namespace agl { namespace detail {

class ShaderHolder { // Size: 0x280
    SEAD_SINGLETON_DISPOSER(ShaderHolder)

public:
    ShaderHolder();
    virtual ~ShaderHolder();

    sead::PtrArrayImpl _10;
    u8 _1C[376];
    ShaderProgramArchive shaders[3];
    u8 _278;
};

static_assert(sizeof(ShaderHolder) == 0x280, "agl::detail::ShaderHolder");

} }

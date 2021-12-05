#pragma once

#include "types.h"

namespace agl {

class ResBinaryShaderArchiveData { // Size: 0x18
public:
    u32 signature;
    u32 version;
    u32 size;
    u32 endianness;
    u32 pointersResolved;
    u32 nameLength;
};

static_assert(sizeof(ResBinaryShaderArchiveData) == 0x18, "agl::ResBinaryShaderArchiveData size mismatch");

class ResBinaryShaderArchive { // Size: 0x4
public:
    u32 setUp(bool);

    ResBinaryShaderArchiveData* data;
};

static_assert(sizeof(ResBinaryShaderArchive) == 0x4, "agl::ResBinaryShaderArchive size mismatch");

}

#pragma once

#include <types.h>

namespace agl {

class ResShaderArchiveData; // TODO

class ResShaderArchive { // Size: 0x4
    u32 setUp(bool);

    ResShaderArchiveData* data;
};

static_assert(sizeof(ResShaderArchive) == 0x4, "agl::ResShaderArchive size mismatch");

}

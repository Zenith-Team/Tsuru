#pragma once

#include "nw/g3d/fnd/gx2struct.h"

namespace nw { namespace g3d { namespace fnd {

struct GfxFetchShader_t {
    internal::GX2FetchShaderData gx2FetchShader;
    u32 ofsVFInst;
    u32 handle;
};

class GfxFetchShader : public GfxFetchShader_t {
    // TODO
};

} } }

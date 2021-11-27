#pragma once

#include "dynlibs/gx2/types.h"

namespace agl { namespace detail {

class TextureDataUtil {
public:
    static void calcSizeAndAlignment(const GX2Surface& surface);

    static u32 convFormatGX2ToAGL(u32 surfaceFormat);
    static u32 convFormatAGLToGX2(u32 aglFormat);
};

} }

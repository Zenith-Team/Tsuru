#pragma once

#include <nw/math/vec4.h>

namespace nw { namespace ut {

struct Color4f {
    math::VEC3& rgb() { return v.xyz(); }
    const math::VEC3& rgb() const { return v.xyz(); }

    union {
        math::VEC4 v;
        struct {
            f32 r;
            f32 g;
            f32 b;
            f32 a;
        };
    };
};

} }

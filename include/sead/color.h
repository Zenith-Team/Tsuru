#pragma once

namespace sead {

class Color4f {  // size: 0x10
public:
    Color4f()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(0.0f)
    { }

    Color4f(f32 r, f32 g, f32 b, f32 a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    { }

    f32 r;  // 0
    f32 g;  // 4
    f32 b;  // 8
    f32 a;  // C

    static const Color4f cWhite;
};

}
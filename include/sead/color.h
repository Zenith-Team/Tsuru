#pragma once

namespace sead {

class Color4f
{
public:
    Color4f()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(0.0f)
    {
    }

    Color4f(f32 r, f32 g, f32 b, f32 a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }

    f32 r;
    f32 g;
    f32 b;
    f32 a;

    static const Color4f cWhite;
};

}
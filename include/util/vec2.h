#pragma once

#include "math.h"

class Vec3;

class Vec2
{
public:
    union
    {
        f32 array[2];

        struct
        {
            f32 x;
            f32 y;
        };
    };

    Vec2(f32 v = 0.0f) :
        x(v), y(v) { }
    Vec2(f32 x, f32 y) :
        x(x), y(y) { }
    Vec2(Vec3& v) :
        x(reinterpret_cast<Vec2&>(v).x), y(reinterpret_cast<Vec2&>(v).y) { }

    void set(f32 val) { x = val; y = val; };
    void set(f32 x, f32 y) { this->x = x; this->y = y; };

    f32& operator[](int idx) { return array[idx]; }

    Vec2& operator+=(const Vec2& rhs) { add(*this, *this, rhs); return *this; }
    Vec2& operator-=(const Vec2& rhs) { sub(*this, *this, rhs); return *this; }
    Vec2 operator+(const Vec2& rhs) const { Vec2 tmp; add(tmp, *this, rhs); return tmp; }
    Vec2 operator-(const Vec2& rhs) const { Vec2 tmp; sub(tmp, *this, rhs); return tmp; }

    Vec2& operator*=(const f32 rhs) { scale(*this, *this, rhs); return *this; }
    Vec2& operator/=(const f32 rhs) { return operator*=(1.0f / rhs); }
    Vec2 operator*(const f32 rhs) const { Vec2 tmp; scale(tmp, *this, rhs); return tmp; }
    Vec2 operator/(const f32 rhs) const { return operator*(1.0f/rhs); }

    Vec2& scale(f32 scale) { Vec2::scale(*this, *this, scale); return *this; }
    Vec2 scaled(f32 scale) { Vec2 tmp; Vec2::scale(tmp, *this, scale); return tmp; }
    Vec2& scale(const Vec2& scales) { Vec2::scale(*this, *this, scales); return *this; }
    Vec2 scaled(const Vec2& scales) { Vec2 tmp; Vec2::scale(tmp, *this, scales); return tmp; }

    f32 dot(const Vec2& v) const { return dot(*this, v); }

    f32 mag() const { return sqrt(magSq()); }
    f32 magSq() const { return x*x + y*y; }
    f32 dist(const Vec2& v) const { return dist(*this, v); }
    f32 distSq(const Vec2& v) const { return distSq(*this, v); }
    f32 angle(const Vec2& v) const { return angle(*this, v); }
    f32 angleCos(const Vec2& v) const { return angleCos(*this, v); }

    Vec2& normalize() { return operator/=(mag()); }

    static Vec2 add(const Vec2& a, const Vec2& b) { Vec2 tmp; add(tmp, a, b); return tmp; }
    static Vec2 sub(const Vec2& a, const Vec2& b) { Vec2 tmp; sub(tmp, a, b); return tmp; }
    static Vec2 scaled(const Vec2& v, const f32 scale) { Vec2 tmp; Vec2::scale(tmp, v, scale); return tmp; }
    static Vec2& scale(Vec2& v, const f32 scale) { return Vec2::scale(v, v, scale); }
    static Vec2 scaled(const Vec2& v, const Vec2& scales) { Vec2 tmp; Vec2::scale(tmp, v, scales); return tmp; }
    static Vec2& scale(Vec2& v, const Vec2& scales) { return Vec2::scale(v, v, scales); }

    static f32 dot(const Vec2& a, const Vec2& b);
    static f32 dist(const Vec2& a, const Vec2& b);
    static f32 distSq(const Vec2& a, const Vec2& b);
    static f32 angle(const Vec2& a, const Vec2& b);
    static f32 angleCos(const Vec2& a, const Vec2& b);

private:
    static Vec2& add(Vec2& out, const Vec2& a, const Vec2& b);
    static Vec2& sub(Vec2& out, const Vec2& a, const Vec2& b);
    static Vec2& scale(Vec2& out, const Vec2& v, const f32 scale);
    static Vec2& scale(Vec2& out, const Vec2& v, const Vec2& scales);
};

inline Vec2& Vec2::add(Vec2& out, const Vec2& a, const Vec2& b)
{
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    return out;
}

inline Vec2& Vec2::sub(Vec2& out, const Vec2& a, const Vec2& b)
{
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    return out;
}

inline Vec2& Vec2::scale(Vec2& out, const Vec2& v, const f32 scale)
{
    out.x = v.x * scale;
    out.y = v.y * scale;
    return out;
}

inline Vec2& Vec2::scale(Vec2& out, const Vec2& v, const Vec2& scales)
{
    out.x = v.x * scales.x;
    out.y = v.y * scales.y;
    return out;
}

inline f32 Vec2::dot(const Vec2& a, const Vec2& b)
{
    return a.x*b.x + a.y*b.y;
}

inline f32 Vec2::dist(const Vec2& a, const Vec2& b)
{
    Vec2 d = a - b;
    return d.mag();
}

inline f32 Vec2::distSq(const Vec2& a, const Vec2& b)
{
    Vec2 d = a - b;
    return d.magSq();
}

inline f32 Vec2::angle(const Vec2& a, const Vec2& b)
{
    return acos(angleCos(a, b));
}

inline f32 Vec2::angleCos(const Vec2& a, const Vec2& b)
{
    return dot(a, b) / (a.mag() * b.mag());
}

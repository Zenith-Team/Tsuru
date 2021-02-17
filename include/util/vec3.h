#pragma once

#include "vec2.h"

class Vec3
{
public:
    union
    {
        f32 array[3];

        struct
        {
            f32 x;
            f32 y;
            f32 z;
        };
    };

    Vec3(f32 v = 0.0f) :
        x(v), y(v), z(v) { }
    Vec3(f32 x, f32 y, f32 z) :
        x(x), y(y), z(z) { }
    Vec3(const Vec2& v) :
        x(v.x), y(v.y), z(0.0f) { }

    f32& operator[](int idx) { return array[idx]; }

    void set(f32 val) { x = val; y = val; z = val; };
    void set(f32 x, f32 y, f32 z) { this->x = x; this->y = y; this->z = z; };

    Vec3& operator+=(const Vec3& rhs) { add(*this, *this, rhs); return *this; }
    Vec3& operator-=(const Vec3& rhs) { sub(*this, *this, rhs); return *this; }
    Vec3 operator+(const Vec3& rhs) const { Vec3 tmp; add(tmp, *this, rhs); return tmp; }
    Vec3 operator-(const Vec3& rhs) const { Vec3 tmp; sub(tmp, *this, rhs); return tmp; }

    Vec3& operator+=(const Vec2& rhs) { add(*this, *this, rhs); return *this; }
    Vec3& operator-=(const Vec2& rhs) { sub(*this, *this, rhs); return *this; }
    Vec3 operator+(const Vec2& rhs) const { Vec3 tmp; add(tmp, *this, rhs); return tmp; }
    Vec3 operator-(const Vec2& rhs) const { Vec3 tmp; sub(tmp, *this, rhs); return tmp; }

    Vec3& operator*=(const f32 rhs) { scale(*this, *this, rhs); return *this; }
    Vec3& operator/=(const f32 rhs) { return operator*=(1.0f / rhs); }
    Vec3 operator*(const f32 rhs) const { Vec3 tmp; scale(tmp, *this, rhs); return tmp; }
    Vec3 operator/(const f32 rhs) const { return operator*(1.0f/rhs); }

    Vec3& scale(f32 scale) { Vec3::scale(*this, *this, scale); return *this; }
    Vec3 scaled(f32 scale) { Vec3 tmp; Vec3::scale(tmp, *this, scale); return tmp; }
    Vec3& scale(const Vec3& scales) { Vec3::scale(*this, *this, scales); return *this; }
    Vec3 scaled(const Vec3& scales) { Vec3 tmp; Vec3::scale(tmp, *this, scales); return tmp; }

    f32 dot(const Vec3& v) const { return dot(*this, v); }

    f32 mag() const { return sqrt(magSq()); }
    f32 magSq() const { return x*x + y*y + z*z; }
    f32 dist(const Vec3& v) const { return dist(*this, v); }
    f32 distSq(const Vec3& v) const { return distSq(*this, v); }
    f32 angle(const Vec3& v) const { return angle(*this, v); }
    f32 angleCos(const Vec3& v) const { return angleCos(*this, v); }

    Vec3& normalize() { return operator/=(mag()); }

    static Vec3 add(const Vec3& a, const Vec3& b) { Vec3 tmp; add(tmp, a, b); return tmp; }
    static Vec3 sub(const Vec3& a, const Vec3& b) { Vec3 tmp; sub(tmp, a, b); return tmp; }
    static Vec3 add(const Vec3& a, const Vec2& b) { Vec3 tmp; add(tmp, a, b); return tmp; }
    static Vec3 sub(const Vec3& a, const Vec2& b) { Vec3 tmp; sub(tmp, a, b); return tmp; }
    static Vec3 scaled(const Vec3& v, const f32 scale) { Vec3 tmp; Vec3::scale(tmp, v, scale); return tmp; }
    static Vec3& scale(Vec3& v, const f32 scale) { return Vec3::scale(v, v, scale); }
    static Vec3 scaled(const Vec3& v, const Vec3& scales) { Vec3 tmp; Vec3::scale(tmp, v, scales); return tmp; }
    static Vec3& scale(Vec3& v, const Vec3& scales) { return Vec3::scale(v, v, scales); }
    static Vec3 cross(const Vec3& a, const Vec3& b) { Vec3 tmp; cross(tmp, a, b); return tmp; }

    static f32 dot(const Vec3& a, const Vec3& b);
    static f32 dist(const Vec3& a, const Vec3& b);
    static f32 distSq(const Vec3& a, const Vec3& b);
    static f32 angle(const Vec3& a, const Vec3& b);
    static f32 angleCos(const Vec3& a, const Vec3& b);

private:
    static Vec3& add(Vec3& out, const Vec3& a, const Vec3& b);
    static Vec3& sub(Vec3& out, const Vec3& a, const Vec3& b);
    static Vec3& add(Vec3& out, const Vec3& a, const Vec2& b);
    static Vec3& sub(Vec3& out, const Vec3& a, const Vec2& b);
    static Vec3& scale(Vec3& out, const Vec3& v, const f32 scale);
    static Vec3& scale(Vec3& out, const Vec3& v, const Vec3& scales);
    static Vec3& cross(Vec3& out, const Vec3& a, const Vec3& b);
};

inline Vec3& Vec3::add(Vec3& out, const Vec3& a, const Vec3& b)
{
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;
    return out;
}

inline Vec3& Vec3::sub(Vec3& out, const Vec3& a, const Vec3& b)
{
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.y - b.z;
    return out;
}

inline Vec3& Vec3::add(Vec3& out, const Vec3& a, const Vec2& b)
{
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    return out;
}

inline Vec3& Vec3::sub(Vec3& out, const Vec3& a, const Vec2& b)
{
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    return out;
}

inline Vec3& Vec3::scale(Vec3& out, const Vec3& v, const f32 scale)
{
    out.x = v.x * scale;
    out.y = v.y * scale;
    out.z = v.z * scale;
    return out;
}

inline Vec3& Vec3::scale(Vec3& out, const Vec3& v, const Vec3& scales)
{
    out.x = v.x * scales.x;
    out.y = v.y * scales.y;
    out.z = v.z * scales.z;
    return out;
}

inline f32 Vec3::dot(const Vec3& a, const Vec3& b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vec3& Vec3::cross(Vec3& out, const Vec3& a, const Vec3& b)
{
    Vec3 tmp;
    tmp.x = a.y*b.z - a.z*b.y;
    tmp.y = a.z*b.x - a.x*b.z;
    tmp.z = a.x*b.y - a.y*b.x;

    out = tmp;
    return out;
}

inline f32 Vec3::dist(const Vec3& a, const Vec3& b)
{
    Vec3 d = a - b;
    return d.mag();
}

inline f32 Vec3::distSq(const Vec3& a, const Vec3& b)
{
    Vec3 d = a - b;
    return d.magSq();
}

inline f32 Vec3::angle(const Vec3& a, const Vec3& b)
{
    return acos(angleCos(a, b));
}

inline f32 Vec3::angleCos(const Vec3& a, const Vec3& b)
{
    return dot(a, b) / (a.mag() * b.mag());
}

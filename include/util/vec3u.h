#pragma once

#include "types.h"
#include "vec3.h"

class Vec3u {  // size: 0xC
public:
    union {
        u32 array[3];

        struct {
            u32 x;  // 0
            u32 y;  // 4
            u32 z;  // 8
        };
    };

    Vec3u(u32 v = 0.0f) :
        x(v), y(v), z(v) { }
    Vec3u(u32 x, u32 y, u32 z) :
        x(x), y(y), z(z) { }
    Vec3u(const Vec2& v) :
        x(v.x), y(v.y), z(0.0f) { }

    u32& operator[](int idx) { return array[idx]; }

    void set(u32 val) { x = val; y = val; z = val; };
    void set(u32 x, u32 y, u32 z) { this->x = x; this->y = y; this->z = z; };

    Vec3u& operator+=(const Vec3u& rhs) { add(*this, *this, rhs); return *this; }
    Vec3u& operator-=(const Vec3u& rhs) { sub(*this, *this, rhs); return *this; }
    Vec3u operator+(const Vec3u& rhs) const { Vec3u tmp; add(tmp, *this, rhs); return tmp; }
    Vec3u operator-(const Vec3u& rhs) const { Vec3u tmp; sub(tmp, *this, rhs); return tmp; }

    Vec3u& operator+=(const Vec2& rhs) { add(*this, *this, rhs); return *this; }
    Vec3u& operator-=(const Vec2& rhs) { sub(*this, *this, rhs); return *this; }
    Vec3u operator+(const Vec2& rhs) const { Vec3u tmp; add(tmp, *this, rhs); return tmp; }
    Vec3u operator-(const Vec2& rhs) const { Vec3u tmp; sub(tmp, *this, rhs); return tmp; }

    Vec3u& operator*=(const u32 rhs) { scale(*this, *this, rhs); return *this; }
    Vec3u& operator/=(const u32 rhs) { return operator*=(1.0f / rhs); }
    Vec3u operator*(const u32 rhs) const { Vec3u tmp; scale(tmp, *this, rhs); return tmp; }
    Vec3u operator/(const u32 rhs) const { return operator*(1.0f/rhs); }

    Vec3u& scale(u32 scale) { Vec3u::scale(*this, *this, scale); return *this; }
    Vec3u scaled(u32 scale) { Vec3u tmp; Vec3u::scale(tmp, *this, scale); return tmp; }
    Vec3u& scale(const Vec3u& scales) { Vec3u::scale(*this, *this, scales); return *this; }
    Vec3u scaled(const Vec3u& scales) { Vec3u tmp; Vec3u::scale(tmp, *this, scales); return tmp; }

    u32 dot(const Vec3u& v) const { return dot(*this, v); }

    u32 mag() const { return sqrt(magSq()); }
    u32 magSq() const { return x*x + y*y + z*z; }
    u32 dist(const Vec3u& v) const { return dist(*this, v); }
    u32 distSq(const Vec3u& v) const { return distSq(*this, v); }
    u32 angle(const Vec3u& v) const { return angle(*this, v); }
    u32 angleCos(const Vec3u& v) const { return angleCos(*this, v); }

    Vec3u& normalize() { return operator/=(mag()); }

    static Vec3u add(const Vec3u& a, const Vec3u& b) { Vec3u tmp; add(tmp, a, b); return tmp; }
    static Vec3u sub(const Vec3u& a, const Vec3u& b) { Vec3u tmp; sub(tmp, a, b); return tmp; }
    static Vec3u add(const Vec3u& a, const Vec2& b) { Vec3u tmp; add(tmp, a, b); return tmp; }
    static Vec3u sub(const Vec3u& a, const Vec2& b) { Vec3u tmp; sub(tmp, a, b); return tmp; }
    static Vec3u scaled(const Vec3u& v, const u32 scale) { Vec3u tmp; Vec3u::scale(tmp, v, scale); return tmp; }
    static Vec3u& scale(Vec3u& v, const u32 scale) { return Vec3u::scale(v, v, scale); }
    static Vec3u scaled(const Vec3u& v, const Vec3u& scales) { Vec3u tmp; Vec3u::scale(tmp, v, scales); return tmp; }
    static Vec3u& scale(Vec3u& v, const Vec3u& scales) { return Vec3u::scale(v, v, scales); }
    static Vec3u cross(const Vec3u& a, const Vec3u& b) { Vec3u tmp; cross(tmp, a, b); return tmp; }

    static u32 dot(const Vec3u& a, const Vec3u& b);
    static u32 dist(const Vec3u& a, const Vec3u& b);
    static u32 distSq(const Vec3u& a, const Vec3u& b);
    static u32 angle(const Vec3u& a, const Vec3u& b);
    static u32 angleCos(const Vec3u& a, const Vec3u& b);

private:
    static Vec3u& add(Vec3u& out, const Vec3u& a, const Vec3u& b);
    static Vec3u& sub(Vec3u& out, const Vec3u& a, const Vec3u& b);
    static Vec3u& add(Vec3u& out, const Vec3u& a, const Vec2& b);
    static Vec3u& sub(Vec3u& out, const Vec3u& a, const Vec2& b);
    static Vec3u& scale(Vec3u& out, const Vec3u& v, const u32 scale);
    static Vec3u& scale(Vec3u& out, const Vec3u& v, const Vec3u& scales);
    static Vec3u& cross(Vec3u& out, const Vec3u& a, const Vec3u& b);
};

inline Vec3u& Vec3u::add(Vec3u& out, const Vec3u& a, const Vec3u& b) {
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;
    return out;
}

inline Vec3u& Vec3u::sub(Vec3u& out, const Vec3u& a, const Vec3u& b) {
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.y - b.z;
    return out;
}

inline Vec3u& Vec3u::add(Vec3u& out, const Vec3u& a, const Vec2& b) {
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    return out;
}

inline Vec3u& Vec3u::sub(Vec3u& out, const Vec3u& a, const Vec2& b) {
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    return out;
}

inline Vec3u& Vec3u::scale(Vec3u& out, const Vec3u& v, const u32 scale) {
    out.x = v.x * scale;
    out.y = v.y * scale;
    out.z = v.z * scale;
    return out;
}

inline Vec3u& Vec3u::scale(Vec3u& out, const Vec3u& v, const Vec3u& scales) {
    out.x = v.x * scales.x;
    out.y = v.y * scales.y;
    out.z = v.z * scales.z;
    return out;
}

inline u32 Vec3u::dot(const Vec3u& a, const Vec3u& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vec3u& Vec3u::cross(Vec3u& out, const Vec3u& a, const Vec3u& b) {
    Vec3u tmp;
    tmp.x = a.y*b.z - a.z*b.y;
    tmp.y = a.z*b.x - a.x*b.z;
    tmp.z = a.x*b.y - a.y*b.x;

    out = tmp;
    return out;
}

inline u32 Vec3u::dist(const Vec3u& a, const Vec3u& b) {
    Vec3u d = a - b;
    return d.mag();
}

inline u32 Vec3u::distSq(const Vec3u& a, const Vec3u& b) {
    Vec3u d = a - b;
    return d.magSq();
}

inline u32 Vec3u::angle(const Vec3u& a, const Vec3u& b) {
    return acos(angleCos(a, b));
}

inline u32 Vec3u::angleCos(const Vec3u& a, const Vec3u& b) {
    return dot(a, b) / (a.mag() * b.mag());
}

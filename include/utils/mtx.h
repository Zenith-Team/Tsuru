#pragma once

#include <types.h>
#include <nw/math/triangular.h>
#include <cafe/math/mtx.h>

inline void sinCosIdx(f32* pSin, f32* pCos, u32 idx) {
    u32 index = (idx >> 24) & 0xFF;
    f32 rest = static_cast<f32>(idx & 0xFFFFFF) / 0x1000000;
    const nw::math::internal::SinCosSample& sample = nw::math::internal::globalSinCosTbl[index];

    *pSin = sample.sinVal + sample.sinDelta * rest;
    *pCos = sample.cosVal + sample.cosDelta * rest;
}

class Mtx34 {
public:
    static Mtx34* sIdentity;

    union {
        f32 rows[3][4];
        f32 cells[12];
    };

    void rotateAndTranslate(const Vec3u& rotation, const Vec3f& translation);
    static void makeST(Mtx34& mtx, const Vec3f& scale, const Vec3f& translation);
    static void makeSRT(Mtx34& mtx, const Vec3f& scale, const Vec3f& rotation, const Vec3f& translation);
    void makeSRzxyTIdx(const Vec3f& s, const Vec3u& r, const Vec3f& t) {
        f32 sinV[3];
        f32 cosV[3];
        sinCosIdx(&sinV[0], &cosV[0], r.x);
        sinCosIdx(&sinV[1], &cosV[1], r.y);
        sinCosIdx(&sinV[2], &cosV[2], r.z);

        this->rows[2][2] = s.z * (cosV[0] * cosV[1]);
        this->rows[0][2] = s.z * (cosV[0] * sinV[1]);
        this->rows[1][2] = s.z * -sinV[0];
        this->rows[2][0] = s.x * (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
        this->rows[0][0] = s.x * (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
        this->rows[1][0] = s.x * (cosV[0] * sinV[2]);
        this->rows[2][1] = s.y * (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
        this->rows[0][1] = s.y * (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
        this->rows[1][1] = s.y * (cosV[0] * cosV[2]);
        this->rows[0][3] = t.x;
        this->rows[1][3] = t.y;
        this->rows[2][3] = t.z;
    }
};

class Mtx44 {
public:
    union {
        f32 rows[4][4];
        f32 cells[16];
    };
};

inline Mtx34* MTX34MULT(Mtx34* out, Mtx34* p1, Mtx34* p2) {
    ASM_MTXConcat(p1, p2, out);
    return out;
}

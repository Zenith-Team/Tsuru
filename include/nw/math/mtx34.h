#pragma once

#include "nw/math/vec4.h"
#include "nw/math/triangular.h"

namespace nw { namespace math {

struct MTX34 {
    MTX34() { }
    MTX34(const MTX34& other) { Copy(this, &other); }

    MTX34(
        f32 _00, f32 _01, f32 _02, f32 _03,
        f32 _10, f32 _11, f32 _12, f32 _13,
        f32 _20, f32 _21, f32 _22, f32 _23
    ) {
        m[0][0] = _00;
        m[0][1] = _01;
        m[0][2] = _02;
        m[0][3] = _03;

        m[1][0] = _10;
        m[1][1] = _11;
        m[1][2] = _12;
        m[1][3] = _13;

        m[2][0] = _20;
        m[2][1] = _21;
        m[2][2] = _22;
        m[2][3] = _23;
    }

    static const MTX34& Identity() {
        static const MTX34 identity(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f
        );

        return identity;
    }

    static MTX34* Copy(MTX34* dst, const MTX34* src) {
        if (src != dst)
            *dst = *src;
        
        return dst;
    }

    static MTX34* Transpose(MTX34* dst, const MTX34* src) {
        if (src == dst) {
            MTX34 temp;
            temp.m[0][0] = src->m[0][0];
            temp.m[0][1] = src->m[1][0];
            temp.m[0][2] = src->m[2][0];
            temp.m[0][3] = 0.0f;
            temp.m[1][0] = src->m[0][1];
            temp.m[1][1] = src->m[1][1];
            temp.m[1][2] = src->m[2][1];
            temp.m[1][3] = 0.0f;
            temp.m[2][0] = src->m[0][2];
            temp.m[2][1] = src->m[1][2];
            temp.m[2][2] = src->m[2][2];
            temp.m[2][3] = 0.0f;
            Copy(dst, &temp);
        }

        else {
            dst->m[0][0] = src->m[0][0];
            dst->m[0][1] = src->m[1][0];
            dst->m[0][2] = src->m[2][0];
            dst->m[0][3] = 0.0f;
            dst->m[1][0] = src->m[0][1];
            dst->m[1][1] = src->m[1][1];
            dst->m[1][2] = src->m[2][1];
            dst->m[1][3] = 0.0f;
            dst->m[2][0] = src->m[0][2];
            dst->m[2][1] = src->m[1][2];
            dst->m[2][2] = src->m[2][2];
            dst->m[2][3] = 0.0f;
        }

        return dst;
    }

    static inline VEC3* MultVec(VEC3* dst, const MTX34* a, const VEC3* b);
    static inline VEC3* MultVecSR(VEC3* dst, const MTX34* a, const VEC3* b);

    static inline MTX34* MakeSRT(MTX34* dst, const VEC3* scale, const VEC3* rotate, const VEC3* translate);
    static inline MTX34* MakeRT(MTX34* dst, const VEC3* rotate, const VEC3* translate);

    static inline MTX34* MakeVectorRotation(MTX34* dst, const VEC3* a, const VEC3* b);
    static inline MTX34* MakeQ(MTX34* dst, const VEC4* q);

    union {
        f32  m[3][4];
        VEC4 v[3];
        f32  a[3*4];
    };
};

VEC3* MTX34::MultVec(VEC3* dst, const MTX34* a, const VEC3* b) {
    const VEC3 tmp = *b;
    dst->x = a->m[0][0] * tmp.x + a->m[0][1] * tmp.y + a->m[0][2] * tmp.z + a->m[0][3];
    dst->y = a->m[1][0] * tmp.x + a->m[1][1] * tmp.y + a->m[1][2] * tmp.z + a->m[1][3];
    dst->z = a->m[2][0] * tmp.x + a->m[2][1] * tmp.y + a->m[2][2] * tmp.z + a->m[2][3];
    return dst;
}

VEC3* MTX34::MultVecSR(VEC3* dst, const MTX34* a, const VEC3* b) {
    const VEC3 tmp = *b;
    dst->x = a->m[0][0] * tmp.x + a->m[0][1] * tmp.y + a->m[0][2] * tmp.z;
    dst->y = a->m[1][0] * tmp.x + a->m[1][1] * tmp.y + a->m[1][2] * tmp.z;
    dst->z = a->m[2][0] * tmp.x + a->m[2][1] * tmp.y + a->m[2][2] * tmp.z;
    return dst;
}

VEC3* VEC3::MultMTX(VEC3* dst, const VEC3* a, const MTX34* b) {
    const VEC3 tmp = *a;
    dst->x = tmp.x * b->m[0][0] + tmp.y * b->m[1][0] + tmp.z * b->m[2][0];
    dst->y = tmp.x * b->m[0][1] + tmp.y * b->m[1][1] + tmp.z * b->m[2][1];
    dst->z = tmp.x * b->m[0][2] + tmp.y * b->m[1][2] + tmp.z * b->m[2][2];
    return dst;
}

MTX34* MTX34::MakeSRT(MTX34* dst, const VEC3* scale, const VEC3* rotate, const VEC3* translate) {
    f32 sinRX = SinRad(rotate->x);
    f32 sinRY = SinRad(rotate->y);
    f32 sinRZ = SinRad(rotate->z);

    f32 cosRX = CosRad(rotate->x);
    f32 cosRY = CosRad(rotate->y);
    f32 cosRZ = CosRad(rotate->z);

    dst->m[0][0] = scale->x * (cosRY * cosRZ);
    dst->m[1][0] = scale->x * (cosRY * sinRZ);
    dst->m[2][0] = scale->x * -sinRY;

    dst->m[0][1] = scale->y * (sinRX * sinRY * cosRZ - cosRX * sinRZ);
    dst->m[1][1] = scale->y * (sinRX * sinRY * sinRZ + cosRX * cosRZ);
    dst->m[2][1] = scale->y * (sinRX * cosRY);

    dst->m[0][2] = scale->z * (cosRX * cosRZ * sinRY + sinRX * sinRZ);
    dst->m[1][2] = scale->z * (cosRX * sinRZ * sinRY - sinRX * cosRZ);
    dst->m[2][2] = scale->z * (cosRX * cosRY);

    dst->m[0][3] = translate->x;
    dst->m[1][3] = translate->y;
    dst->m[2][3] = translate->z;

    return dst;
}

MTX34* MTX34::MakeRT(MTX34* dst, const VEC3* rotate, const VEC3* translate) {
    const VEC3 scale = (VEC3){ 1.0f, 1.0f, 1.0f };
    return MakeSRT(dst, &scale, rotate, translate);
}

MTX34* MTX34::MakeVectorRotation(MTX34* dst, const VEC3* a, const VEC3* b) {
    // Based on sead::Matrix34CalcCommon<f32>::makeVectorRotation()

    math::VEC3 cross;
    math::VEC3::CrossProduct(&cross, a, b);
    f32 dot = math::VEC3::DotProduct(a, b) + 1.0f;

    math::VEC4 q;

    if (dot <= F_ULP)
        q = (math::VEC4){ 1.0f, 0.0f, 0.0f, 0.0f };

    else {
        f32 v1 = sqrtf(2.0f * dot);
        f32 v2 = 1.0f / v1;
        q.xyz() = cross * v2;
        q.w = v1 * 0.5f;
    }

    return MakeQ(dst, &q);
}

MTX34* MTX34::MakeQ(MTX34* dst, const VEC4* q) {
    f32 v = 2.0f / (q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);

    f32 v1  = q->x * v;
    f32 v2  = q->y * v;
    f32 v3  = q->z * v;
    f32 v4  = q->w * v1;
    f32 v5  = q->w * v2;
    f32 v6  = q->w * v3;
    f32 v7  = q->x * v1;
    f32 v8  = q->x * v2;
    f32 v9  = q->x * v3;
    f32 v10 = q->y * v2;
    f32 v11 = q->y * v3;
    f32 v12 = q->z * v3;

    dst->m[0][0] = 1.0f - (v10 + v12);
    dst->m[0][1] = v8 - v6;
    dst->m[0][2] = v9 + v5;
    dst->m[0][3] = 0.0f;

    dst->m[1][0] = v8 + v6;
    dst->m[1][1] = 1.0f - (v7 + v12);
    dst->m[1][2] = v11 - v4;
    dst->m[1][3] = 0.0f;

    dst->m[2][0] = v9 - v5;
    dst->m[2][1] = v11 + v4;
    dst->m[2][2] = 1.0f - (v7 + v10);
    dst->m[2][3] = 0.0f;

    return dst;
}

} }

#pragma once

#include "sead/matrix.h"
#include "sead/mathcalccommon.h"

namespace sead {

template <typename T>
class Matrix34CalcCommon {
public:
    static void makeRTIdx(Matrix34<T>& o, const Vector3<u32>& r, const Vector3<T>& t) {
        T sinV[3];
        T cosV[3];

        MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
        MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
        MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

        o.m[0][0] = (cosV[1] * cosV[2]);
        o.m[1][0] = (cosV[1] * sinV[2]);
        o.m[2][0] = -sinV[1];

        o.m[0][1] = (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
        o.m[1][1] = (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
        o.m[2][1] = (sinV[0] * cosV[1]);

        o.m[0][2] = (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
        o.m[1][2] = (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
        o.m[2][2] = (cosV[0] * cosV[1]);

        o.m[0][3] = t.x;
        o.m[1][3] = t.y;
        o.m[2][3] = t.z;
    }

    static void makeSRzxyTIdx(Matrix34<T>& o, const Vector3<T>& s, const Vector3<u32>& r, const Vector3<T>& t) {
        T sinV[3];
        T cosV[3];

        MathCalcCommon<T>::sinCosIdx(&sinV[0], &cosV[0], r.x);
        MathCalcCommon<T>::sinCosIdx(&sinV[1], &cosV[1], r.y);
        MathCalcCommon<T>::sinCosIdx(&sinV[2], &cosV[2], r.z);

        o.m[2][2] = s.z * (cosV[0] * cosV[1]);
        o.m[0][2] = s.z * (cosV[0] * sinV[1]);
        o.m[1][2] = s.z * -sinV[0];

        o.m[2][0] = s.x * (sinV[1] * cosV[2] - sinV[0] * cosV[1] * sinV[2]);
        o.m[0][0] = s.x * (cosV[1] * cosV[2] + sinV[0] * sinV[1] * sinV[2]);
        o.m[1][0] = s.x * (cosV[0] * sinV[2]);

        o.m[2][1] = s.y * (sinV[1] * sinV[2] + sinV[0] * cosV[1] * cosV[2]);
        o.m[0][1] = s.y * (cosV[1] * sinV[2] - sinV[0] * sinV[1] * cosV[2]);
        o.m[1][1] = s.y * (cosV[0] * cosV[2]);

        o.m[0][3] = t.x;
        o.m[1][3] = t.y;
        o.m[2][3] = t.z;
    }

    static void makeST(Matrix34<T>& o, const Vector3<T>& s, const Vector3<T>& t) {
        o.m[0][0] = s.x;
        o.m[1][0] = 0;
        o.m[2][0] = 0;

        o.m[0][1] = 0;
        o.m[1][1] = s.y;
        o.m[2][1] = 0;

        o.m[0][2] = 0;
        o.m[1][2] = 0;
        o.m[2][2] = s.z;

        o.m[0][3] = t.x;
        o.m[1][3] = t.y;
        o.m[2][3] = t.z;
    }

    static void makeSRT(Matrix34<T>& o, const Vector3<T>& s, const Vector3<T>& r, const Vector3<T>& t) {
        const T sinV[3] = { sinf(r.x),
                            sinf(r.y),
                            sinf(r.z) };

        const T cosV[3] = { cosf(r.x),
                            cosf(r.y),
                            cosf(r.z) };

        o.m[0][0] = s.x * (cosV[1] * cosV[2]);
        o.m[1][0] = s.x * (cosV[1] * sinV[2]);
        o.m[2][0] = s.x * -sinV[1];

        o.m[0][1] = s.y * (sinV[0] * sinV[1] * cosV[2] - cosV[0] * sinV[2]);
        o.m[1][1] = s.y * (sinV[0] * sinV[1] * sinV[2] + cosV[0] * cosV[2]);
        o.m[2][1] = s.y * (sinV[0] * cosV[1]);

        o.m[0][2] = s.z * (cosV[0] * cosV[2] * sinV[1] + sinV[0] * sinV[2]);
        o.m[1][2] = s.z * (cosV[0] * sinV[2] * sinV[1] - sinV[0] * cosV[2]);
        o.m[2][2] = s.z * (cosV[0] * cosV[1]);

        o.m[0][3] = t.x;
        o.m[1][3] = t.y;
        o.m[2][3] = t.z;
    }
};

template <typename T>
class Matrix44CalcCommon {
public:
    static void multiply(sead::Matrix44<T>& out, const sead::Matrix44<T>& a, const sead::Matrix34<T>& b) {
        const T a11 = a.rows[0][0];
        const T a12 = a.rows[0][1];
        const T a13 = a.rows[0][2];
        const T a14 = a.rows[0][3];

        const T a21 = a.rows[1][0];
        const T a22 = a.rows[1][1];
        const T a23 = a.rows[1][2];
        const T a24 = a.rows[1][3];

        const T a31 = a.rows[2][0];
        const T a32 = a.rows[2][1];
        const T a33 = a.rows[2][2];
        const T a34 = a.rows[2][3];

        const T a41 = a.rows[3][0];
        const T a42 = a.rows[3][1];
        const T a43 = a.rows[3][2];
        const T a44 = a.rows[3][3];

        const T b11 = b.rows[0][0];
        const T b12 = b.rows[0][1];
        const T b13 = b.rows[0][2];
        const T b14 = b.rows[0][3];

        const T b21 = b.rows[1][0];
        const T b22 = b.rows[1][1];
        const T b23 = b.rows[1][2];
        const T b24 = b.rows[1][3];

        const T b31 = b.rows[2][0];
        const T b32 = b.rows[2][1];
        const T b33 = b.rows[2][2];
        const T b34 = b.rows[2][3];

        out.rows[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
        out.rows[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
        out.rows[0][2] = a11 * b13 + a12 * b23 + a13 * b33;
        out.rows[0][3] = a11 * b14 + a12 * b24 + a13 * b34 + a14;

        out.rows[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
        out.rows[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
        out.rows[1][2] = a21 * b13 + a22 * b23 + a23 * b33;
        out.rows[1][3] = a21 * b14 + a22 * b24 + a23 * b34 + a24;

        out.rows[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
        out.rows[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
        out.rows[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
        out.rows[2][3] = a31 * b14 + a32 * b24 + a33 * b34 + a34;

        out.rows[3][0] = a41 * b11 + a42 * b21 + a43 * b31;
        out.rows[3][1] = a41 * b12 + a42 * b22 + a43 * b32;
        out.rows[3][2] = a41 * b13 + a42 * b23 + a43 * b33;
        out.rows[3][3] = a41 * b14 + a42 * b24 + a43 * b34 + a44;
    }
};

}

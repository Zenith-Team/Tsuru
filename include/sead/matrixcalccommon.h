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

    static void makeS(Matrix34<T>& o, const Vector3<T>& s) {
        o.m[0][0] = s.x;
        o.m[1][0] = 0;
        o.m[2][0] = 0;

        o.m[0][1] = 0;
        o.m[1][1] = s.y;
        o.m[2][1] = 0;

        o.m[0][2] = 0;
        o.m[1][2] = 0;
        o.m[2][2] = s.z;

        o.m[0][3] = 0;
        o.m[1][3] = 0;
        o.m[2][3] = 0;
    }

    static void makeS(Matrix34<T>& o, T x, T y, T z) {
        o.m[0][0] = x;
        o.m[1][0] = 0;
        o.m[2][0] = 0;

        o.m[0][1] = 0;
        o.m[1][1] = y;
        o.m[2][1] = 0;

        o.m[0][2] = 0;
        o.m[1][2] = 0;
        o.m[2][2] = z;

        o.m[0][3] = 0;
        o.m[1][3] = 0;
        o.m[2][3] = 0;
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

    static void makeSRTIdx(Matrix34<T>& o, const Vector3<T>& s, const Vector3<u32>& r, const Vector3<T>& t);

    static void makeQ(Matrix34<T>& o, const Quat<T>& q) {
        // Assuming the quaternion "q" is normalized

        const T yy = 2 * q.y * q.y;
        const T zz = 2 * q.z * q.z;
        const T xx = 2 * q.x * q.x;
        const T xy = 2 * q.x * q.y;
        const T xz = 2 * q.x * q.z;
        const T yz = 2 * q.y * q.z;
        const T wz = 2 * q.w * q.z;
        const T wx = 2 * q.w * q.x;
        const T wy = 2 * q.w * q.y;

        o.m[0][0] = 1 - yy - zz;
        o.m[0][1] =     xy - wz;
        o.m[0][2] =     xz + wy;

        o.m[1][0] =     xy + wz;
        o.m[1][1] = 1 - xx - zz;
        o.m[1][2] =     yz - wx;

        o.m[2][0] =     xz - wy;
        o.m[2][1] =     yz + wx;
        o.m[2][2] = 1 - xx - yy;

        o.m[0][3] = 0;
        o.m[1][3] = 0;
        o.m[2][3] = 0;
    }

    static void setBase(Matrix34<T>& n, s32 axis, const Vector3<T>& v) {
        n.m[0][axis] = v.x;
        n.m[1][axis] = v.y;
        n.m[2][axis] = v.z;
    }

    static void setRow(Matrix34<T>& n, const Vector4<T>& v, s32 row) {
        n.m[row][0] = v.x;
        n.m[row][1] = v.y;
        n.m[row][2] = v.z;
        n.m[row][3] = v.w;
    }

    static void setTranslation(Matrix34<T>& n, const Vector3<T>& v) {
        setBase(n, 3, v);
    }
};

template <typename T>
class Matrix44CalcCommon {
public:
    static void multiply(sead::Matrix44<T>& out, const sead::Matrix44<T>& a, const sead::Matrix34<T>& b) {
        const T a11 = a.m[0][0];
        const T a12 = a.m[0][1];
        const T a13 = a.m[0][2];
        const T a14 = a.m[0][3];

        const T a21 = a.m[1][0];
        const T a22 = a.m[1][1];
        const T a23 = a.m[1][2];
        const T a24 = a.m[1][3];

        const T a31 = a.m[2][0];
        const T a32 = a.m[2][1];
        const T a33 = a.m[2][2];
        const T a34 = a.m[2][3];

        const T a41 = a.m[3][0];
        const T a42 = a.m[3][1];
        const T a43 = a.m[3][2];
        const T a44 = a.m[3][3];

        const T b11 = b.m[0][0];
        const T b12 = b.m[0][1];
        const T b13 = b.m[0][2];
        const T b14 = b.m[0][3];

        const T b21 = b.m[1][0];
        const T b22 = b.m[1][1];
        const T b23 = b.m[1][2];
        const T b24 = b.m[1][3];

        const T b31 = b.m[2][0];
        const T b32 = b.m[2][1];
        const T b33 = b.m[2][2];
        const T b34 = b.m[2][3];

        out.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31;
        out.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32;
        out.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33;
        out.m[0][3] = a11 * b14 + a12 * b24 + a13 * b34 + a14;

        out.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31;
        out.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32;
        out.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33;
        out.m[1][3] = a21 * b14 + a22 * b24 + a23 * b34 + a24;

        out.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31;
        out.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32;
        out.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33;
        out.m[2][3] = a31 * b14 + a32 * b24 + a33 * b34 + a34;

        out.m[3][0] = a41 * b11 + a42 * b21 + a43 * b31;
        out.m[3][1] = a41 * b12 + a42 * b22 + a43 * b32;
        out.m[3][2] = a41 * b13 + a42 * b23 + a43 * b33;
        out.m[3][3] = a41 * b14 + a42 * b24 + a43 * b34 + a44;
    }
};

}

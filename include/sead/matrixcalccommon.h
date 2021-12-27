#pragma once

#include "types.h"

namespace sead {

template <typename T>
class Matrix44CalcCommon {
public:
    static void multiply(Mtx44& out, const Mtx44& a, const Mtx34& b) {
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

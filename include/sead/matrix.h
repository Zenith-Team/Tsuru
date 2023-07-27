#pragma once

#include "sead/vector.h"
#include "sead/quat.h"

namespace sead {

template <typename T>
class Matrix34 : public Policies<T>::Mtx34Base {
public:
    Matrix34() { }

    Matrix34(
        T a00, T a01, T a02, T a03,
        T a10, T a11, T a12, T a13,
        T a20, T a21, T a22, T a23
    );

    T operator()(s32 i, s32 j) const;
    T& operator()(s32 i, s32 j);
    Matrix34<T>& operator=(const Matrix34<T>& n);

    void makeIdentity();
    void makeZero();

    void setInverse(const Matrix34<T>& n);
    void setInverse33(const Matrix34<T>& n);
    void setInverseTranspose(const Matrix34<T>& n);
    void setMul(const Matrix34<T>& a, const Matrix34<T>& b);
    void setTranspose(const Matrix34<T>& n);
    void transpose();

    void makeR(const Vector3<T>& r);
    void makeRIdx(u32 xr, u32 yr, u32 zr);
    void makeRT(const Vector3<T>& r, const Vector3<T>& t);
    void makeRTIdx(const Vector3<u32>& r, const Vector3<T>& t);
    void makeRzxyIdx(u32 xr, u32 yr, u32 zr);
    void makeRzxyTIdx(const Vector3<u32>& r, const Vector3<T>& t);
    void makeS(const Vector3<T>& s);
    void makeS(T x, T y, T z);
    void makeSR(const Vector3<T>& s, const Vector3<T>& r);
    void makeSRIdx(const Vector3<T>& s, const Vector3<u32>& r);
    void makeSRT(const Vector3<T>& s, const Vector3<T>& r, const Vector3<T>& t);
    void makeSRTIdx(const Vector3<T>& s, const Vector3<u32>& r, const Vector3<T>& t);
    void makeSRzxyIdx(const Vector3<T>& s, const Vector3<u32>& r);
    void makeSRzxyTIdx(const Vector3<T>& s, const Vector3<u32>& r, const Vector3<T>& t);
    void makeST(const Vector3<T>& s, const Vector3<T>& t);
    void makeT(const Vector3<T>& t);
    void makeT(T x, T y, T z);
    void fromQuat(const Quat<T>& quat);

    void getBase(Vector3<T>& o, s32 axis) const;
    void getTranslation(Vector3<T>& o) const;

    void scaleAllElements(T s);
    void scaleBases(T sx, T sy, T sz);
    void setBase(s32 axis, const Vector3<T>& v);
    void setTranslation(const Vector3<T>& t);
    void setTranslation(T x, T y, T z);

    static const Matrix34 zero;
    static const Matrix34 ident;
};

template <typename T>
class Matrix44 : public Policies<T>::Mtx44Base {
public:
    Matrix44() { }

    Matrix44(
        T a00, T a01, T a02, T a03,
        T a10, T a11, T a12, T a13,
        T a20, T a21, T a22, T a23,
        T a30, T a31, T a32, T a33
    );

    T operator()(s32 i, s32 j) const;
    T& operator()(s32 i, s32 j);
    Matrix44<T>& operator=(const Matrix44<T>& n);

    void makeIdentity();
    void makeZero();

    void setInverse(const Matrix44<T>& n);
    void setInverseTranspose(const Matrix44<T>& n);
    void setMul(const Matrix44<T>& a, const Matrix44<T>& b);
    void setMul(const Matrix34<T>& a, const Matrix44<T>& b);
    void setMul(const Matrix44<T>& a, const Matrix34<T>& b);
    void setTranspose(const Matrix44<T>& n);
    void transpose();

    void makeR(const Vector3<T>& r);
    void makeRIdx(u32 xr, u32 yr, u32 zr);
    void makeRzxyIdx(u32 xr, u32 yr, u32 zr);

    void scaleAllElements(T s);
    void scaleBases(T sx, T sy, T sz, T sw);

    static const Matrix44 zero;
    static const Matrix44 ident;
};

}

#include "sead/matrixcalccommon.h"

namespace sead {

template <typename T> inline void Matrix34<T>::makeRTIdx(const Vector3<u32>& r, const Vector3<T>& t) { Matrix34CalcCommon<T>::makeRTIdx(*this, r, t); }
template <typename T> inline void Matrix34<T>::makeSRzxyTIdx(const Vector3<T>& s, const Vector3<u32>& r, const Vector3<T>& t) { Matrix34CalcCommon<T>::makeSRzxyTIdx(*this, s, r, t); }
template <typename T> inline void Matrix34<T>::makeS(const Vector3<T>& s) { Matrix34CalcCommon<T>::makeS(*this, s); }
template <typename T> inline void Matrix34<T>::makeS(T x, T y, T z) { Matrix34CalcCommon<T>::makeS(*this, x, y, z); }
template <typename T> inline void Matrix34<T>::makeST(const Vector3<T>& s, const Vector3<T>& t) { Matrix34CalcCommon<T>::makeST(*this, s, t); }
template <typename T> inline void Matrix34<T>::makeSRT(const Vector3<T>& s, const Vector3<T>& r, const Vector3<T>& t) { Matrix34CalcCommon<T>::makeSRT(*this, s, r, t); }
template <typename T> inline void Matrix34<T>::makeSRTIdx(const Vector3<T>& s, const Vector3<u32>& r, const Vector3<T>& t) { Matrix34CalcCommon<T>::makeSRTIdx(*this, s, r, t); }
template <typename T> inline void Matrix34<T>::fromQuat(const Quat<T>& quat) { Matrix34CalcCommon<T>::makeQ(*this, quat); }
template <typename T> inline void Matrix34<T>::setTranslation(const Vector3<T>& t) { Matrix34CalcCommon<T>::setTranslation(*this, t); }
template <typename T> inline void Matrix34<T>::makeIdentity() {
    m[0][0] = (T)1.0; m[0][1] = (T)0.0; m[0][2] = (T)0.0; m[0][3] = (T)0.0;
    m[1][0] = (T)0.0; m[1][1] = (T)1.0; m[1][2] = (T)0.0; m[1][3] = (T)0.0;
    m[2][0] = (T)0.0; m[2][1] = (T)0.0; m[2][2] = (T)1.0; m[2][3] = (T)0.0;
}

}

typedef sead::Matrix34<f32> Mtx34;
typedef sead::Matrix44<f32> Mtx44;

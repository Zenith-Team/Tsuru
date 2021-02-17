#pragma once

#include "vec3.h"
#include "vec3u.h"


class Mtx34
{
public:
    static Mtx34* Identity;

    union
    {
        f32 rows[3][4];
        f32 cells[12];
    };

    void rotateAndTranslate(const Vec3u& rotation, const Vec3& translation);
    static void makeST(Mtx34& mtx, const Vec3& scale, const Vec3& translation);
    static void makeSRT(Mtx34& mtx, const Vec3& scale, const Vec3& rotation, const Vec3& translation);
};

// TODO: do this properly
extern "C" void ASM_MTXConcat(const Mtx34* p1, const Mtx34* p2, Mtx34* pOut);

inline Mtx34*
MTX34Mult(Mtx34* pOut, const Mtx34* p1, const Mtx34* p2)
{
    ASM_MTXConcat(p1, p2, pOut);
    return pOut;
}

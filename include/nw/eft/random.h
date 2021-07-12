#ifndef EFT_RANDOM_H_
#define EFT_RANDOM_H_

#include "nw/math/vec3.h"

namespace nw { namespace eft {

class Random {
// https://github.com/open-ead/sead/blob/master/include/random/seadRandom.h
// https://github.com/open-ead/sead/blob/master/modules/src/random/seadRandom.cpp

public:
    Random() {
        Init();
    }

    Random(u32 seed) {
        Init(seed);
    }

    Random(u32 seed_x, u32 seed_y, u32 seed_z, u32 seed_w) {
        Init(seed_x, seed_y, seed_z, seed_w);
    }

    void Init() {
        Init(0);
    }

    void Init(u32 seed) {
        static const u32 a = 0x6C078965;
        mX = a * (seed ^ (seed >> 30u)) + 1;
        mY = a * (mX ^ (mX >> 30u)) + 2;
        mZ = a * (mY ^ (mY >> 30u)) + 3;
        mW = a * (mZ ^ (mZ >> 30u)) + 4;
    }

    void Init(u32 seed_x, u32 seed_y, u32 seed_z, u32 seed_w) {
        if ((seed_x | seed_y | seed_z | seed_w) == 0) // seeds must not be all zero.
            return Init(0);

        mX = seed_x;
        mY = seed_y;
        mZ = seed_z;
        mW = seed_w;
    }

    u32 GetU32() {
        u32 x = mX ^ (mX << 11u);
        mX = mY;
        mY = mZ;
        mZ = mW;
        mW = mW ^ (mW >> 19u) ^ x ^ (x >> 8u);
        return mW;
    }

    u32 GetU32(u32 max) {
        return GetU32() * u64(max) >> 32u;
    }

    s32 GetS32Range(s32 a, s32 b) {
        return GetU32(b - a) + a;
    }

    f32 GetF32() {
        return GetU32() * (1.0f / 4294967296.0f);
    }

    f32 GetF32(f32 max) {
        return GetF32() * max;
    }

    f32 GetF32Range(f32 a, f32 b) {
        return GetF32(b - a) + a;
    }

private:
    u32 mX;
    u32 mY;
    u32 mZ;
    u32 mW;
};
static_assert(sizeof(Random) == 0x10, "Random size mismatch");

class Heap;

class PtclRandom {
public:
    PtclRandom();

    void Init(u32 seed) {
        randomVec3Idx = (u16)seed;
        randomNormVec3Idx = (u16)(seed >> 16);
        val = seed;
    }

    u32 GetU32() {
        u32 x = val;
        val = val * 0x41C64E6D + 12345;
        return x;
    }

    u32 GetU32(u32 max) {
        return GetU32() * u64(max) >> 32u;
    }

    s32 GetS32Range(s32 a, s32 b) {
        return GetU32(b - a) + a;
    }

    s32 GetS32(s32 max) {
        // Using (s32)GetU32(max) does not match
        return (s32)(GetU32() * u64(max) >> 32u);
    }

    f32 GetF32() {
        return GetU32() * (1.0f / 4294967296.0f);
    }

    f32 GetF32(f32 max) {
        return GetF32() * max;
    }

    f32 GetF32Range(f32 a, f32 b) {
        return GetF32(b - a) + a;
    }

    const math::VEC3& GetVec3() {
        return mVec3Tbl[randomVec3Idx++ & 0x1FF];
    }

    const math::VEC3& GetNormalizedVec3() {
        return mNormalizedVec3Tbl[randomNormVec3Idx++ & 0x1FF];
    }

    static void Initialize(Heap* heap);
    static Random* GetGlobalRandom();

    static Random gRandom;
    static math::VEC3* mVec3Tbl;
    static math::VEC3* mNormalizedVec3Tbl;

    u16 randomVec3Idx;
    u16 randomNormVec3Idx;
    u32 val;
};
static_assert(sizeof(PtclRandom) == 8, "PtclRandom size mismatch");

} } // namespace nw::eft

#endif // EFT_RANDOM_H_

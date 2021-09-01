#pragma once

#include <nw/math/vec3.h>

namespace nw { namespace eft {

class Random { // Size: 0x10
public:
    Random() {
        this->Init();
    }

    Random(u32 seed) {
        this->Init(seed);
    }

    Random(u32 seedX, u32 seedY, u32 seedZ, u32 seedW) {
        this->Init(seedX, seedY, seedZ, seedW);
    }

    void Init() {
        this->Init(0);
    }

    void Init(u32 seed) {
        static const u32 a = 0x6C078965;
        this->mX = a * (seed ^ (seed >> 30u)) + 1;
        this->mY = a * (mX ^ (mX >> 30u)) + 2;
        this->mZ = a * (mY ^ (mY >> 30u)) + 3;
        this->mW = a * (mZ ^ (mZ >> 30u)) + 4;
    }

    void Init(u32 seedX, u32 seedY, u32 seedZ, u32 seedW) {
        if ((seedX | seedY | seedZ | seedW) == 0)   // Seeds must not all be zero
            return Init(0);
        
        this->mX = seedX;
        this->mY = seedY;
        this->mZ = seedZ;
        this->mW = seedW;
    }

    u32 GetU32() {
        u32 x = this->mX ^ (this->mX << 11u);
        this->mX = this->mY;
        this->mY = this->mZ;
        this->mZ = this->mW;
        this->mW = this->mW ^ (this->mW >> 19u) ^ x ^ (x >> 8u);
        return this->mW;
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

class PtclRandom { // Size: 0x8
public:
    PtclRandom();

    void Init(u32 seed) {
        mRandomVec3Idx = (u16)seed;
        mRandomNormVec3Idx = (u16)(seed >> 16);
        mVal = seed;
    }

    u32 GetU32() {
        u32 x = mVal;
        mVal = mVal * 0x41C64E6D + 12345;
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
        return sVec3Tbl[mRandomVec3Idx++ & 0x1FF];
    }

    const math::VEC3& GetNormalizedVec3() {
        return sNormalizedVec3Tbl[mRandomNormVec3Idx++ & 0x1FF];
    }

    static void Initialize(Heap* heap);
    static Random* GetGlobalRandom();

    static Random gRandom;
    static math::VEC3* sVec3Tbl;
    static math::VEC3* sNormalizedVec3Tbl;

    u16 mRandomVec3Idx;
    u16 mRandomNormVec3Idx;
    u32 mVal;
};

static_assert(sizeof(PtclRandom) == 8, "PtclRandom size mismatch");

} }

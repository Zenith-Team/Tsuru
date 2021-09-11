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
        this->x = a * (seed ^ (seed >> 30u)) + 1;
        this->y = a * (x ^ (x >> 30u)) + 2;
        this->z = a * (y ^ (y >> 30u)) + 3;
        this->w = a * (z ^ (z >> 30u)) + 4;
    }

    void Init(u32 seedX, u32 seedY, u32 seedZ, u32 seedW) {
        if ((seedX | seedY | seedZ | seedW) == 0)   // Seeds must not all be zero
            return Init(0);

        this->x = seedX;
        this->y = seedY;
        this->z = seedZ;
        this->w = seedW;
    }

    u32 GetU32() {
        u32 x = this->x ^ (this->x << 11u);
        this->x = this->y;
        this->y = this->z;
        this->z = this->w;
        this->w = this->w ^ (this->w >> 19u) ^ x ^ (x >> 8u);
        return this->w;
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
    u32 x;
    u32 y;
    u32 z;
    u32 w;
};

static_assert(sizeof(Random) == 0x10, "Random size mismatch");

class Heap;

class PtclRandom { // Size: 0x8
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
        return sVec3Tbl[randomVec3Idx++ & 0x1FF];
    }

    const math::VEC3& GetNormalizedVec3() {
        return sNormalizedVec3Tbl[randomNormVec3Idx++ & 0x1FF];
    }

    static void Initialize(Heap* heap);
    static Random* GetGlobalRandom();

    static Random globalRandom;
    static math::VEC3* sVec3Tbl;
    static math::VEC3* sNormalizedVec3Tbl;

    u16 randomVec3Idx;
    u16 randomNormVec3Idx;
    u32 val;
};

static_assert(sizeof(PtclRandom) == 8, "PtclRandom size mismatch");

} }

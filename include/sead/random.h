#pragma once

#include "sead/idisposer.h"

namespace sead {

class Random {
public:
    u32 getU32();
};

class GlobalRandom : public Random {
    SEAD_SINGLETON_DISPOSER(GlobalRandom);
};

inline bool randBool() { return GlobalRandom::instance()->getU32() & 1; }

inline u32 randU32() { return GlobalRandom::instance()->getU32(); }
inline u32 randU32(u32 max) { u64 x = static_cast<u64>(GlobalRandom::instance()->getU32()) * max; return x >> 32; }

inline s32 randS32(s32 min, s32 max) { s32 range = max - min; u64 x = static_cast<u64>(GlobalRandom::instance()->getU32()) * range; return min + (x >> 32); }

inline f32 randF32() { return static_cast<f32>(GlobalRandom::instance()->getU32()) * 0.00000000023283064f; }
inline f32 randF32(f32 max) { return static_cast<f32>(GlobalRandom::instance()->getU32()) * 0.00000000023283064f * max; }
inline f32 randF32(f32 min, f32 max) { f32 rand = static_cast<f32>(GlobalRandom::instance()->getU32()) * 0.00000000023283064f; return min + rand; }

}

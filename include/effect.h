#pragma once

#include "sead.h"
#include "util/vec3.h"
#include "util/vec3u.h"
#include "util/mtx34.h"


class Effect
{
public:
    Effect();
    bool update(Vec3* position, Vec3u* rotation, Vec3* scale);
    bool setEffectId(s32 effectId);
    static bool spawn(s32 effectId, Vec3* position, Vec3u* rotation, Vec3* scale);

    Mtx34 mtx;      // 0
    u8 _30;         // 30
    u32* _34;       // 34
    s32 _38;        // 38
    u32* _3C;       // 3C
};


class EffectWrapper : public sead::IDisposer
{
public:
    EffectWrapper();
    bool update(s32 effectId, Vec3* position, Vec3u* rotation, Vec3* scale);

    Effect effect;      // 10
    u32 _50;            // 50
    u32 _54;            // 54
    EffectWrapper* _58; // 58
    u32 _5C;            // 5C
    s32 effectId;       // 60
    u8 _64;             // 64
};

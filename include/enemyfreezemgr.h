#pragma once

#include "util/vec3.h"

class Actor;
class Enemy;

class EnemyFreezeMgr
{
public:
    struct Info
    {
        u32 settings;   // 0    Bits: 0: Horizontally Large, 1: Vertically Large
        Vec3 position;  // 4
        Vec3 scale;     // 10
        u32 _1C;        // 1C
    };

    struct Flags
    {
        u8 breakTime;           // 0    Stored in _34
        u8 _1;                  // 1    Stored in _35
        u8 _2;                  // 2    Stored in _36
    };

public:
    EnemyFreezeMgr(Enemy* owner);

    bool freeze(const Info& info, u32 count);

    void setFlags(const Flags& flags);

    u8 iceActorCount;       // 0
    u32 iceActorIds[12];    // 4
    u8 breakTime;           // 34
    u8 _35;                 // 35   gravity related
    u8 _36;                 // 36   ^
    u32 _38;                // 38
    Enemy* owner;           // 3C
    s16 _40;                // 40
    u16 _42;                // 42
    u16 _44;                // 44
    u16 _46;                // 46
    u8 _48;                 // 48
    u8 _49;                 // 49
    u8 _4A;                 // 4A
    u8 _4B;                 // 4B
    u8 _4C;                 // 4C
};
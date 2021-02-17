#pragma once

#include "util/vec2.h"

class TileCheck
{
public:
    struct Result
    {
        u8 _0;
        f32 _4;
        f32 _8;
        u32 _C;
        u32 _10;
        u32 _14;
        u32 _18;
        u32 _1C;
        u32 _20;
    };

    struct Param
    {
        u8 _0;
        u8 _1;
        u8 _2;
        u8 _3;
        u32 _4;
        u32 _8;
    };

public:
    TileCheck(const Param& parm);
    bool check(Result* result, const Vec2& pos1, const Vec2& pos2, u32 unk);

    u8 _0;
    u8 _1;
    u8 _2;
    u8 _3;
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    u32 _1C;
    u32 _20;
    u32 _24;
    u32 _28;
    u32 _2C;
    u32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
    u32 _40;
    u32 _44;
    u32 _48;
};
